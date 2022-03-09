PLAT = linux
CPP = g++

LAPACK_LIB   = -llapack
BLAS_LIB     = -lblas

CPP_WARNINGS = -ansi -pedantic-errors
CPP_OPTIM    = -O3

CPP_FLAGS    = -std=c++14 -D$(PLAT)  $(CPP_WARNINGS) $(CPP_OPTIM)
ALL_LIBS     = $(LAPACK_LIB) $(BLAS_LIB) -lfftw3 

DEPS = system_lattice.h monte_carlo.h data_collection.h 

main: main.o monte_carlo.o system_lattice.o data_collection.o 
	$(CPP) $(CPP_FLAGS) -o main main.o monte_carlo.o system_lattice.o data_collection.o $(ALL_LIBS)

%.o: %.cc %.h $(DEPS)
	$(CPP) $(CPP_FLAGS) -c $<
	
.PHONY: clean
clean:
	rm -f *~ *.o core main



