
#objects = hash.o rs.o rthcolsums.o rthdist.o rthgini.o rthhist.o rthkendall.o rthma.o rthmean.o rthnorm.o rthorder.o rthpdist.o rthpearson.o rthrnorm.o rthrunif.o rthsort.o rthtable.o rthxpos.o rthxposnv.o threads.o

##objects = hash.o rs.o             rthdist.o rthgini.o rthhist.o                      rthmean.o rthnorm.o rthorder.o rthpdist.o rthpearson.o rthrnorm.o            rthsort.o rthtable.o rthxpos.o rthxposnv.o threads.o

objects = hash.o rs.o rthcolsums.o  rthdist.o rthgini.o rthhist.o                      rthmean.o rthnorm.o rthorder.o rthpdist.o rthpearson.o rthrnorm.o            rthsort.o rthtable.o rthxpos.o rthxposnv.o threads.o

#inc = -I/usr/share/R/include -I/home/smathews/thrust-1.8.1 -I/usr/local/cuda/include  -I/usr/lib/R/site-library/Rcpp/include

inc = -I/usr/share/R/include -I/usr/local/cuda/include -I/usr/lib/R/site-library/Rcpp/include

#debug = -g 

CUDA_ARCH="arch=compute_35,code=sm_35"

link_cuda = nvcc
linkflags_cuda = $(debug) -gencode $(CUDA_ARCH) 
def_cudalink =  -L/usr/local/cuda/lib64 -lcuda -lcudart 
cuda_link = $(link_cuda) $(linkflags_cuda) $(def_cudalink)

comp_cuda = nvcc
def_cuda = -DTHRUST_DEVICE_SYSTEM=THRUST_DEVICE_BACKEND_CUDA -DGPU
flags_cuda = $(debug) --std=c++11 --x cu -gencode $(CUDA_ARCH)  -Xcompiler "-fpic" 
cuda_comp = $(comp_cuda) $(flags_cuda) $(def_cuda)

comp_gcc = g++
def_gcc = -fopenmp -DTHRUST_DEVICE_SYSTEM=THRUST_DEVICE_BACKEND_OMP
flag_gcc = $(debug) --std=c++11 -fPIC
gcc_comp = $(comp_gcc) $(flags_gcc) $(def_gcc)

comp_cudac = nvcc
def_cudac =  -DTHRUST_DEVICE_SYSTEM=THRUST_DEVICE_BACKEND_CUDA -DGPU
flags_cudac = $(debug) --x cu -gencode $(CUDA_ARCH)  -Xcompiler "-fpic" 
cudac_comp = $(comp_cudac) $(flags_cudac) $(def_cudac)


all: Rth.so

Rth.so: $(objects)
	mkdir -p ../libs/; $(cuda_link) -o ../libs/Rth.so --shared $(objects)


rs.o : rs.cpp
	$(cuda_comp) -c rs.cpp $(inc) $(def)

hash.o : hash.c
	$(cudac_comp) -c hash.c $(inc) $(def)

rthcolsums.o : rthcolsums.cpp
	$(cuda_comp) -c rthcolsums.cpp $(inc) $(def)

rthdist.o : rthdist.cpp
	$(cuda_comp) -c rthdist.cpp $(inc) $(def)

rthgini.o : rthgini.cpp
	$(cuda_comp) -c rthgini.cpp $(inc) $(def)

rthhist.o : rthhist.cpp
	$(cuda_comp) -c rthhist.cpp $(inc) $(def)

#rthkendall.o : rthkendall.cpp
#	$(gcc_comp) -c rthkendall.cpp $(inc) $(def)

#rthma.o : rthma.cpp
#	$(gcc_comp) -c rthma.cpp $(inc) $(def)

rthmean.o : rthmean.cpp
	$(cuda_comp) -c rthmean.cpp $(inc) $(def)

rthnorm.o : rthnorm.cpp
	$(cuda_comp) -c rthnorm.cpp $(inc) $(def)

rthorder.o : rthorder.cpp
	$(cuda_comp) -c rthorder.cpp $(inc) $(def)

rthpdist.o : rthpdist.cpp
	$(cuda_comp) -c rthpdist.cpp $(inc) $(def)

rthpearson.o : rthpearson.cpp
	$(cuda_comp) -c rthpearson.cpp $(inc) $(def)

rthrnorm.o : rthrnorm.cpp
	$(cuda_comp) -c rthrnorm.cpp $(inc) $(def)

#rthrunif.o : rthrunif.cpp
#	$(gcc_comp) -c rthrunif.cpp $(inc) $(def)

rthsort.o : rthsort.cpp
	$(cuda_comp) -c rthsort.cpp $(inc) $(def)

rthtable.o : rthtable.cpp
	$(cuda_comp) -c rthtable.cpp $(inc) $(def)

rthxpos.o : rthxpos.cpp
	$(cuda_comp) -c rthxpos.cpp $(inc) $(def)

rthxposnv.o : rthxposnv.cpp
	$(cuda_comp) -c rthxposnv.cpp $(inc) $(def)

threads.o : threads.cpp
	$(cuda_comp) -c threads.cpp $(inc) $(def)

clean:
	rm -rf *.o ../libs/Rth.so 

package:
	cd ../../; mkdir -p ./Rth/libs; rm ./Rth/libs/Rth.so; tar -czvf Rth.1.0.1.gz ./Rth/libs ./Rth/INSTALL ./Rth/NAMESPACE ./Rth/DESCRIPTION ./Rth/demo ./Rth/man ./Rth/R ./Rth/test  ./Rth/src/*.c* ./Rth/src/*.h




