#include "SparseMatrix.h" 

Vector seqMatVectMult(SparseMatrix*,Vector&); 
Vector mpiMatVEctMult(SparseMatrix*,Vector&); 
Vector cudaMatVEctMult(SparseMatrix*,Vector&); 

Vector operator*(SparseMatrix*,Vector&); 
