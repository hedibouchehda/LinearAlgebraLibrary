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

bool operator== (StructCOO,StructCOO); 

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

bool operator==(StructCSR,StructCSR); 

struct LineCOO
{
    StructCOO* nonZerosOnLine; 
    int sizeOfStructure; 

    void allocate(int size)
    {
        sizeOfStructure = size;
        nonZerosOnLine = (StructCOO*) malloc(size*sizeof(StructCOO)); 
    }

    void add(StructCOO element, int position)
    {
        nonZerosOnLine[position] = element; 
    }
};

struct LineCSR 
{
    StructCSR* nonZerosOnColumn; 
    int sizeOfStructure; 

    void allocate(int size)
    {
        sizeOfStructure = size;
        nonZerosOnColumn = (StructCSR*) malloc(size*sizeof(StructCSR)); 
    }

    void add(StructCSR element, int position)
    {
        nonZerosOnColumn[position] = element; 
    }
};

struct ColumnBegEndInLine
{
    int beg; 
    int end;
} ;

class SparseMatrix 
{
    private: 
        int                         m_numCols, m_numLines;
        int                         m_numOfNonZeros; 

    public: 

        std::vector<Triplet>        m_listOfTriplets; 
        int*                        m_linesCOO; 
        StructCOO*                  m_columnValue;  //associated to COO format   
        int*                        m_columnsCSR; 
        StructCSR*                  m_lineValue;    //associated to CSR format
        ColumnBegEndInLine*         m_begEndOnLine;


        SparseMatrix(int numLines, int numCols) : m_numCols(numCols), m_numLines(numLines){};
        void add(int,int,double); 
        void setBegEndOnLine();
        void set(); 
        void printDense();
        void rangingCOO(); 
        void rangingCSR();
        void setCSR(); 
        void setCOO(); 
        void printCOORanged();
        void printCSRRanged();
        int getNumCols(){return m_numCols;}; 
        int getNumLines(){return m_numLines;};
        int getNumOfNonZeros(){return m_numOfNonZeros;}; 
        
};

class Vector
{
    public: 
        int m_size; 
        double* vect; 

        Vector(int size)
        {
            m_size = size;
            vect = (double*) malloc(size*sizeof(double)); 
        }; 

        Vector(){};

        void add_value(int position, double value)
        {
            if (position >= m_size)
                std::cout<<"sizing problem in vector"<<std::endl; 
            else
                vect[position] = value; 
        };   
};