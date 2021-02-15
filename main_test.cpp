#include "seqMatVect.h" 


int main()
{
    SparseMatrix* sp = new SparseMatrix(4,4); 
    sp->add(0,3,1); 
    sp->add(2,1,1.); 
    sp->add(1,2,3.);
    sp->add(0,0,2); 
    sp->add(0,1,3); 
    sp->add(1,3,3); 
    sp->add(2,2,3.); 
    sp->add(3,0,1.);
    sp->set();

    sp->setBegEndOnLine(); 
    

    int i; 
    for(i=0; i<4; i++)
    {
        std::cout<<sp->m_begEndOnLine[i].beg<<" "<<sp->m_begEndOnLine[i].end<<std::endl;
    }

    std::cout<<std::endl<<std::endl<<std::endl;
    Vector vect(4);  
    for (i=0; i<5; i++)
    {
        vect.vect[i] = 1.; 
    }

    Vector result; 
    result = seqMatVectMult(sp,vect);

    for (i=0; i<4; i++)
    {
        std::cout<<result.vect[i]<<std::endl;
    }

    
    /*
    std::cout<<std::endl;
    std::cout<<std::endl;
    std::cout<<std::endl; 
    std::cout<<"***********"<<std::endl;
    sp->printCOORanged();*/           
}