
#include <vector>
#include <thrust/device_vector.h>
#include <thrust/sort.h>
#include <thrust/execution_policy.h>
#include <memory>

#include "Rth.h"
#include "Rth.dbg.h"


extern "C" SEXP rthsort2_double(SEXP a, SEXP decreasing, SEXP inplace,
  SEXP nthreads)
{
  SEXP b;
  
  RTH_GEN_NTHREADS(nthreads);
  int len = LENGTH(a);

  log_init( "/home/smathews/rlog.txt" )
  
  thrust::device_vector<double> dx;
  thrust::host_vector<double> hm;
  //double *hm = new double[len];  // Host memory
  //std::unique_ptr<double[]> hm{new double[len]};
  
  
  log_num( len );
  
  hm.assign( ((double*)REAL(a)), ((double*)REAL(a))+len );
  
  std::vector<int> chunks;
  
  
  int parts = len / 4;
  
  
  //for( int i=0; i<len; i+=10000000 )
  for( int i=0; i<len; i+=parts )
  {
    chunks.push_back(i);
    log_num( i );
  }
  chunks.push_back(len);
  log_num( len );
  
  log_sz( "Entering initial sort loop");
  
  for( int chunk=0; chunk < chunks.size()-1; chunk++ )
  {
    log_num3( chunk, chunks[chunk], chunks[chunk+1] );
    
    dx.assign( hm.begin() + chunks[chunk], hm.begin() + chunks[chunk+1] );
    
    // sort, then copy back to R vector
    if (INTEGER(decreasing)[0] )
    {
      thrust::sort( thrust::device, dx.begin(), dx.end(), thrust::greater<double>()  );
    }
    else
    {
      thrust::sort(  thrust::device, dx.begin(), dx.end()  );
    }
    
    thrust::copy( dx.begin(), dx.begin()+( chunks[chunk+1]-chunks[chunk] ), (double*)(&(hm[ chunks[chunk] ])) );
  }
  

  log_sz( "Entering split sort loop");
  
  for( int shift=0; shift < chunks.size()-1; shift++ )
  {
    dx.clear();

    log_sz( "Entering split chunk pull");
    log_num( shift );
    log_sz( "");
    
    
    
    for( int sweep=0; sweep < chunks.size()-1; sweep++ )
    {
      log_num( sweep );
      int cut_start = chunks[sweep];
      int cut_end = chunks[sweep+1];
      int cut = (cut_end-cut_start);
      int cut_offset = ( cut/chunks.size()-1 ) * shift;
      int slice = ( cut / (chunks.size() - 1 ) );
      int slice_start = slice; // * shift;
      int slice_end = slice_start + slice;
      int offset = (((cut_end - cut_start) / (chunks.size()-1)   ) * shift  );
      int offset_shift = (((cut_end - cut_start) / (chunks.size()-1)   ) * sweep  );
      int slice_shift = slice * shift;
      log_num3( (slice), (cut_offset), (offset) );
      log_num3( ( slice_start ), ( slice_end ), ( slice_shift ) );
      log_num3( (cut), ( cut_start), ( cut_end )  );
      log_num2(  ( cut_start + offset_shift ),  ( cut_start + offset_shift + slice )  );
      //dx.insert( dx.end(), hm.begin()+( cut_start ),  hm.begin()+( cut_start + slice + cut_offset )  );
      dx.insert( dx.end(), hm.begin()+( cut_start + offset_shift ),  hm.begin()+( cut_start + offset_shift + slice )  );
      log_sz_num( "dx.size()", dx.size() );
    }
    
    log_sz( "");
    log_sz( "Commencing split chunk sort" );
    if (INTEGER(decreasing)[0] )
    {
      thrust::sort( thrust::device, dx.begin(), dx.end(), thrust::greater<double>()  );
    }
    else
    {
      thrust::sort(  thrust::device, dx.begin(), dx.end()  );
    }
    
    log_sz( "");  log_sz( "Returning sorted chunks");

    for( int sweep=0; sweep < chunks.size()-1; sweep++ )
    {
      log_num( sweep );
      int cut_start = chunks[sweep];
      int cut_end = chunks[sweep+1];
      int cut = (cut_end-cut_start);
      int slice = ( cut / (chunks.size() - 1 ) );
      int slice_start = slice; // * shift;
      int slice_end = slice_start + slice;
      int offset = cut_start + (((cut_end - cut_start) / (chunks.size()-1)   ) * shift  );
      int slice_shift = slice * shift;
      log_num( cut );
      log_num2( ( cut_start), ( cut_end )  );
      log_num( offset );

      log_num( ( slice_start ) );
      log_num( ( slice ) );
      log_num( ( slice_start ) );
      log_num( ( slice_end ) );
      log_num( ( slice_shift ) );
      
      log_num3(  ( slice*sweep ) , ( slice*sweep + slice )  , ( offset )  )
      thrust::copy( 
        dx.begin() + ( slice*sweep ), 
        dx.begin() + ( slice*sweep + slice ), 
        hm.begin() + ( offset )  //+ slice*shift) // chunks[sweep]// + cut * sweep
      );
      
    }
    
    
    
    
  }
  

  log_sz( "Sorting complete");
  
  
  
  
  
    
  log_sz( "Returning results");
    
  
  if (INTEGER(inplace)[0]) {
    thrust::copy(dx.begin(), dx.end(), (double*)REAL(a));
    log_sz( "Done");
    log_close;
    return R_NilValue;
  }
  else
  {
    PROTECT(b = allocVector(REALSXP, len) );
    
    thrust::copy(hm.begin() , hm.end(), (double*)REAL(b));
    
    UNPROTECT(1);
    log_sz( "Done");
    log_close;
    return b;
  }
  
  

  
  
  
}

extern "C" SEXP rthsort2_int(SEXP a, SEXP decreasing, SEXP inplace,
   SEXP nthreads)
{
  SEXP b;
  
  #if RTH_OMP
  omp_set_num_threads(INT(nthreads));
  #elif RTH_TBB
  tbb::task_scheduler_init init(INT(nthreads));
  #endif
  
  thrust::device_vector<int> dx(INTEGER(a), INTEGER(a)+LENGTH(a));
  
  if (INTEGER(decreasing)[0])
    thrust::sort( thrust::device, dx.begin(), dx.end(), thrust::greater<int>());
  else
    thrust::sort( thrust::device, dx.begin(), dx.end());
  
  if (INTEGER(inplace)[0])
  {
    thrust::copy(dx.begin(), dx.end(), INTEGER(a));
    return R_NilValue;
  }
  else
  {
    PROTECT(b = allocVector(INTSXP, LENGTH(a)));
    thrust::copy(dx.begin(), dx.end(), INTEGER(b));
    
    UNPROTECT(1);
    return b;
  }
}

