#include <iostream>

using namespace std;

int main()
{
    
    
    int row = 5;
    for(size_t i = row - 1; i >= 0; i--){
        std::cout << i << std::endl;   
    }
    
    row = 1;
    for(size_t i = row - 1; i >= 0; i--){
        std::cout << i << std::endl;   
    }
    
    return 0;
}