#include "Entities/Ocean.hpp"

#include <iostream>
#include <chrono>
#include <thread>


int main(){
    std::system("cls");
    Ocean ocean(10, 10);
    for(int i = 0; i<150; i++){
        ocean.print();
        ocean.tick();
        std::this_thread::sleep_for(std::chrono::seconds(1));
        std::system("cls");
    }
    std::cout<<"FINISH";
    return 0;
}