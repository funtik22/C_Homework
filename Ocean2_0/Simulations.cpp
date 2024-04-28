#include "Entities/Ocean.hpp"

#include <iostream>

int main(){
    Ocean ocean(10, 10);
    //ocean.tick();

    for(int i = 0; i<10; i++){
        ocean.print();
        ocean.tick();
        std::cout<<std::endl;
    }
    
    
    std::cout<<"finish";
    return 0;
}