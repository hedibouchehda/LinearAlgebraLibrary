#include <iostream> 

int main()
{
    int* N ;
    N = (int*) malloc(sizeof(int));
    N[0] = 11; 
    std::cout<<N[0]<<std::endl;
    return 0; 
}