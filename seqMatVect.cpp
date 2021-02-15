#include "seqMatVect.h" 

#define typeOfImplementation "seq"

Vector seqMatVectMult(SparseMatrix* spMat, 
                                    Vector& vector)
{    
    Vector result(spMat->getNumLines());  

    double* vect = vector.vect; 
    if (vector.m_size != spMat->getNumCols())
        std::cout<<"sizing problem : can't implement the multplication"<<std::endl; 

    else 
    {
        int i,j; 
        int nonZerosOnLine(0); 
        int columnIndex(0); 
        for (i=1; i<spMat->getNumLines()+1; i++)
        {
            nonZerosOnLine = spMat->m_linesCOO[i] - spMat->m_linesCOO[i-1]; 

            for (j=0; j<nonZerosOnLine; j++)
            {
                result.vect[i-1] += spMat->m_columnValue[columnIndex].value * vect[spMat->m_columnValue[columnIndex].columnIndex]; 
                columnIndex++; 
            }
        }
    }
    return result; 
}

Vector operator*(SparseMatrix* spMat, Vector& vect)
{
    if (typeOfImplementation == "seq")
        return seqMatVectMult(spMat,vect); 
}

