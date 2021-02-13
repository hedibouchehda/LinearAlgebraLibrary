#include <vector> 
#include <iostream> 


//this structre permits adding the non-zeros elements 
//to the SparseMatrix class under the form {line index, column index, value}
struct Triplet
{
    int columnIndex; 
    int lineIndex; 
    double value; 

    Triplet(int line, int column, double nonZeroValue) 
    {
        columnIndex = column; 
        lineIndex   = line; 
        value       = nonZeroValue;
    };

    void reset(Triplet triplet)
    {
        columnIndex = triplet.columnIndex; 
        lineIndex   = triplet.lineIndex; 
        value       = triplet.value;
    };
};

//this structure will contain pairs (numCOl,value) for the COO format 
struct StructCOO
{
    int columnIndex; 
    double value; 

   /* StructCOO(int column, double nonZeroValue) 
    {
        columnIndex = column; 
        value       = nonZeroValue;
    };*/ 
};

//this structure will contain pairs (numline,value) for the CSR format
struct StructCSR
{
    int lineIndex; 
    double value; 

   /* StructCSR(int line, double nonZeroValue) 
    {
        lineIndex = line; 
        value     = nonZeroValue; 
    };*/     
};

class SparseMatrix 
{
    private: 
        int                         m_numCols, m_numLines;
        std::vector<Triplet>        m_listOfTriplets; 
        std::vector<int>            m_linesCOO; 
        std::vector<StructCOO>      m_columnValue;     
        std::vector<int>            m_columnsCSR; 
        std::vector<StructCSR>      m_lineValue;

  
    public: 
        SparseMatrix(int numLines, int numCols) : m_numCols(numCols), m_numLines(numLines){};
        void add(int,int,double); 
        void set(); 
        void printDense();
        void rangingCOO(); 
        void rangingCSR();
        void setCSR(); 
        void setCOO(); 
        void printCOORanged();
        void printCSRRanged();
 
};