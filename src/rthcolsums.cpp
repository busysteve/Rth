// adapted from
// https://github.com/thrust/thrust/blob/master/examples/sum_rows.cu but

#include <thrust/host_vector.h>
#include <thrust/device_vector.h>
#include <thrust/reduce.h>
#include <thrust/functional.h>
#include <thrust/execution_policy.h>
#include <stdio.h>

#include "Rth.h"


#ifdef GPU
#define flouble float
#else
#define flouble double
#endif

#if 0
static FILE* g_logfile;
#define log_init(F)	{ g_logfile = fopen( F , "w" ); }
#define log_close	{ fclose( g_logfile ); }
#define log_sz(X)	{ fprintf( g_logfile, "[%d] - %s\n", 0, X ); fflush(g_logfile); }
#define log_num(X)	{ fprintf( g_logfile, "[%d] - %d\n", 0, X ); fflush(g_logfile); }
#define log_num2(X ,Y)	{ fprintf( g_logfile, "[%d] - %d - %d\n", 0, X, Y ); fflush(g_logfile); }
#else
#define log_init(F)	
#define log_close	
#define log_sz(X)	
#define log_num(X)	
#define log_num2(X,Y)	
#endif

// note that R uses column-major order, and Rcpp vectors retain this
// ordering

// convert a linear index to a column index
struct lintocol: public thrust::unary_function<int,int>
{
  int nr; // number of rows
  
  __host__ __device__
  lintocol(int nr) : nr(nr) {  }
  
   __host__ __device__
  int operator()(int i)
  {
    //log_num2( i , nr );
    return i / nr;
  }
};

// matrix m with nr rows 
extern "C" SEXP rthcolsums(SEXP m, SEXP nthreads) {
  SEXP ret;
  int nr = nrows(m);
  int nc = ncols(m);
  
  RTH_GEN_NTHREADS(nthreads);
  
  thrust::device_vector<flouble> cp_d_data;
  cp_d_data.assign( ((double*)REAL(m)), ((double*)REAL(m)) + (nr*nc) );

  
  // colsums will be device vector for the column sums
  thrust::device_vector<flouble> colsums( nc );
  

  // reduce_by_key(), in the form here, takes input keys, in this 
  // case column numbers, and then does reductions based on their
  // unique values; data that have the same input keys will be 
  // reduced as a group (it's assumed that the data ordering is such 
  // that all data with the same input keys are contiguous)
  //
  // colindices will be the "output keys"
  thrust::device_vector<int> colindices(nr);

  //Creating reduce by key counting iterator
  auto th_it = thrust::make_transform_iterator(
                    thrust::counting_iterator<int>(0), 
                    lintocol(nr)
                );

  thrust::reduce_by_key
  (
	  thrust::device,

    // start of input key vector; we take the counting iterator, 
    // 0,1,2,..., and apply our index-conversion functor to it
    th_it, // thrust::make_transform_iterator(thrust::counting_iterator<int>(0), lintocol(nr)),
    // end of the input key vector, 
    th_it + (nr*nc), // thrust::make_transform_iterator(thrust::counting_iterator<int>(0), lintocol(nr)) + (nr*nc),

    // m is on host, so this won't work on CUDA, but even if copy to
    // device, still have odd problems on CUDA
    cp_d_data.begin(),  // data, in this case our input matrix
    
    // output keys, not used in this case, but deals with "empty rows"
    // in "ragged matrix" settings
    colindices.begin(),
    
    // at long last, our column sums
    colsums.begin()
  );

  // prepare to convert to R form
  PROTECT(ret = allocVector(REALSXP, nc)  );

  //Creating copy device_vector to ret
  thrust::copy( colsums.begin(), colsums.end(), REAL(ret)  );
  
  UNPROTECT(1);

  return ret;
}

