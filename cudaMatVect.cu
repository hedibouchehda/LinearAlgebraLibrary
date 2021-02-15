#include "SparseMatrix.h" 

#define threadsPerBlock 128 
#define blocksPerGrid 128 



__global__ void kernel(ColumnBegEndInLine* d_begEndLines, StructCOO* d_columnsValues, double* d_vect, double* d_result, int* d_N)
{
    int i = threadIdx.x + blockIdx.x*blockDim.x; 

    int columnIndex(0);
    int nonZerosOnLine(0); 

    while (i<d_N[0])
    {
        d_result[i] = 0;
        
        for (int j=d_begEndLines[i].beg; j<=d_begEndLines[i].end; j++)
        {
            d_result[i] +=  d_columnsValues[j].value * d_vect[d_columnsValues[j].columnIndex];       
        }
               
        i += blockDim.x*gridDim.x;
    }
   
}



Vector cudaMatVect(SparseMatrix* spMat, Vector& vect)
{   
    
    spMat->setBegEndOnLine(); 
    
    Vector result(spMat->getNumLines()); 
   
    int* N = (int*) malloc(sizeof(int)); 
    N[0] = sp->getNumLines();
      
    
    
    size_t ColumnBegEndInLineSize = spMat->getNumLines()*sizeof(ColumnBegEndInLine); 
    size_t inputSize = vect.m_size*sizeof(int); 
    size_t outputSize = (spMat->getNumLines())*sizeof(int); 
    size_t StructCOOSize = spMat->getNumOfNonZeros()*sizeof(StructCOO);

    //allocating variables on the device 
    ColumnBegEndInLine* d_begEndLines;
    StructCOO* d_columnsValues;
    double* d_vect; 
    double* d_result; 
    int* d_N; 
    
    cudaMalloc((void**)&d_begEndLines,ColumnBegEndInLineSize); 
    cudaMalloc((void**)&result,outputSize); 
    cudaMalloc((void**)&d_columnsValues,StructCOOSize); 
    cudaMalloc((void**)&d_vect,inputSize); 
    cudaMalloc((void**)&d_N,sizeof(int)); 

    //copyng to device
    cudaMemcpy(d_vect,vect.vect,inputSize,cudaMemcpyHostToDevice);
    cudaMemcpy(d_N,N,sizeof(int),cudaMemcpyHostToDevice); 
    cudaMemcpy(d_begEndLines,spMat->m_begEndOnLine,ColumnBegEndInLineSize,cudaMemcpyHostToDevice);
    cudaMemcpy(d_columnsValues,spMat->m_columnValue,StructCOOSize,cudaMemcpyHostToDevice); 

    kernel<<< blocksPerGrid,threadsPerBlock >>>(d_begEndLines,d_columnsValues,d_vect,d_result,d_N); 

    cudaMemcpy(result.vect,d_result,outputSize,cudaMemcpyDeviceToHost); 

    free(spMat->m_begEndOnLine);
    
    cudaFree(d_begEndLines);
    cudaFree(result);
    cudaFree(d_columnsValues);
    cudaFree(d_vect);
    cudaFree(d_N);
     
    return result;
}

int main()
{
    SparseMatrix* sp = new SparseMatrix(100,100); 
    std::vector<double> vect; 
    
    int i; 

    for (i=0; i<100; i++)
    {
        sp->add(i,i,1);
        vect.push_back(1.); 
    }

    sp->set(); 

    std::vector<double> result; 

    //result = cudaMatVect(sp,vect); 
    double* c_vect; 
    int* linesCOO;
    StructCOO* columnsValues;
    int* N;
    convertToCTypes(sp, vect, c_vect, linesCOO, columnsValues); 
    bool structArrayIsTrue(true), c_vectIsTrue(true), linesCOOIsTrue(true); 
      
    for (i=0; i<vect.size(); i++)
    {
        if (vect[i] != c_vect[i])
            c_vectIsTrue = false; 
    }
/*
    for (i=0; i<sp->m_linesCOO.size(); i++ )
    {
        if (sp->m_linesCOO[i]) 
            linesCOOIsTrue = false; 
    }

    for (i=0; i<sp->m_columnValue.size(); i++)
    {
        if (sp->m_columnValue[i] == columnsValues[i])
            structArrayIsTrue = false;           
    }
*/
    std::cout<<structArrayIsTrue<<" "<<linesCOOIsTrue<<" "<<c_vectIsTrue<<std::endl;
    return 0;
}