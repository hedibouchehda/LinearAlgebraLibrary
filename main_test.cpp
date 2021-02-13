#include "SparseMatrix.h" 


int main()
{
    SparseMatrix* sp = new SparseMatrix(4,4); 
    sp->add(0,3,1); 
    sp->add(2,1,1.); 
    sp->add(1,2,0.5);
    sp->add(0,0,2); 
    sp->add(0,1,3); 
    sp->add(1,3,3); 
    sp->add(2,2,3.); 
    sp->set();
    sp->printDense();
    /*
    std::cout<<std::endl;
    std::cout<<std::endl;
    std::cout<<std::endl; 
    std::cout<<"***********"<<std::endl;
    sp->printCOORanged();*/           
}