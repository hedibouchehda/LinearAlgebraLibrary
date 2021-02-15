#include "SparseMatrix.h" 

bool operator== (StructCOO s1, StructCOO s2)
{
    bool result = false; 
    if (s1.columnIndex == s2.columnIndex && s1.value == s2.value)
        result = true; 
    return result;
}

bool operator==(StructCSR s1, StructCSR s2)
{
    bool result = false; 
    if (s1.lineIndex == s2.lineIndex && s1.value == s2.value)
        result = true;
    return result;
}

void SparseMatrix::add(int line, int column, double value)
{
    Triplet triplet = Triplet(line,column,value);
    m_listOfTriplets.push_back(triplet); 
}

//sort the elements the list containing the triplets 
//in order to get build the three list of COO format 
//(here a list and list of structures)
void SparseMatrix::rangingCOO() 
{
    int i,j ; 
    Triplet triplet = Triplet(0,0,0.0);

    for (i=0; i<m_listOfTriplets.size()-1; i++)
    {
        for (j=i+1; j<m_listOfTriplets.size(); j++)
        {
            if (m_listOfTriplets[j].lineIndex < m_listOfTriplets[i].lineIndex)
            {
                triplet.reset(m_listOfTriplets[i]); 
                m_listOfTriplets[i].reset(m_listOfTriplets[j]); 
                m_listOfTriplets[j].reset(triplet); 
            }
        }
    }
}

//same case as the function above but for CSR format
void SparseMatrix::rangingCSR()
{
    int i,j ; 
    Triplet triplet(0,0,0);
    for (i=0; i<m_listOfTriplets.size()-1; i++)
    {
        for (j=i+1; j<m_listOfTriplets.size(); j++)
        {
            if (m_listOfTriplets[j].columnIndex < m_listOfTriplets[i].columnIndex)
            {
                triplet.reset(m_listOfTriplets[i]); 
                m_listOfTriplets[i].reset(m_listOfTriplets[j]); 
                m_listOfTriplets[j].reset(triplet); 
            }
        }
    }
}

//build the COO format
void SparseMatrix::setCOO() 
{
    m_linesCOO = (int*) malloc((m_numLines+1)*sizeof(int));
    m_columnValue = (StructCOO*) malloc(m_listOfTriplets.size()*sizeof(StructCOO));

    rangingCOO();

    int line(0); 
    int sameLineIndex(0);
    int numOfElements(0);

    while (line<m_numLines)
    {
        while (m_listOfTriplets[sameLineIndex].lineIndex == line)
        {
            numOfElements++; 
            sameLineIndex++; 
        }
        m_linesCOO[line+1] = numOfElements;
        line++;   
    }

    int i; 
    for (i=0; i<m_listOfTriplets.size(); i++) 
    {
        m_columnValue[i].columnIndex = m_listOfTriplets[i].columnIndex; 
        m_columnValue[i].value       = m_listOfTriplets[i].value; 
    }
}

//build the CSR format
void SparseMatrix::setCSR()
{
    m_columnsCSR = (int*) malloc((m_numCols+1)*sizeof(int));
    m_lineValue = (StructCSR*) malloc(m_listOfTriplets.size()*sizeof(StructCSR)); 

    rangingCSR();

    int column(0); 
    int sameColumnIndex(0);
    int numOfElements(0);

    while (column<m_numCols)
    {
        while (m_listOfTriplets[sameColumnIndex].columnIndex == column)
        {
            numOfElements++; 
            sameColumnIndex++; 
        }
        m_columnsCSR[column+1] = numOfElements;
        column++;
    }

    int i; 
    for (i=0; i<m_listOfTriplets.size(); i++)
    {
        m_lineValue[i].lineIndex =  m_listOfTriplets[i].lineIndex;
        m_lineValue[i].value     =  m_listOfTriplets[i].value; 
    }      
}

void SparseMatrix::setBegEndOnLine() 
{
    m_begEndOnLine = (ColumnBegEndInLine*) malloc(getNumLines()*sizeof(ColumnBegEndInLine)); 
    int i;
    int beg(0),end(0);
    int nonZerosOnLine; 
    for (i=1; i<getNumLines()+1; i++ )
    {
        nonZerosOnLine = m_linesCOO[i] - m_linesCOO[i-1];
        end = beg + nonZerosOnLine - 1;
        m_begEndOnLine[i-1].beg = beg; 
        m_begEndOnLine[i-1].end = end; 
        beg += nonZerosOnLine;
    }
}
//setting both of formats
void SparseMatrix::set()
{
    m_numOfNonZeros = m_listOfTriplets.size(); 
    setCOO(); 
    setCSR(); 
    m_listOfTriplets.clear(); 
}

void SparseMatrix::printDense()
{
    std::vector<double> denseMatrix; 
    denseMatrix.resize(m_numCols*m_numLines); 

    int i,j;
    int nonZerosOnLine(0);
    int columnIndex(0);   
    
    for (i=1; i<m_numOfNonZeros; i++)
    {
        nonZerosOnLine = m_linesCOO[i]-m_linesCOO[i-1];
        
        for (j=0; j<nonZerosOnLine; j++)
        {
            
            denseMatrix[m_columnValue[columnIndex].columnIndex+m_numCols*(i-1)] = m_columnValue[columnIndex].value;
            columnIndex++; 
        }
        std::cout<<std::endl;
    }
    
    for (i=0; i<m_numLines; i++)
    {
        for (j=0; j<m_numCols; j++)
        {
            std::cout<<denseMatrix[j+m_numCols*i]<<" ";
        }
        std::cout<<std::endl; 
    }
}
