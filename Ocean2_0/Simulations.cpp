#include "Entities/Ocean.hpp"
#include <iostream>
#include <chrono>
#include <thread>
#include "constants.hpp"


void clearConsole(){
    #if defined _WIN32
        system("cls");
    #elif defined (__LINUX__) || defined(__gnu_linux__) || defined(__linux__)
        system("clear"); 
    #elif defined (__APPLE__)
        system("clear");
    #endif
}


int main(){
    Ocean ocean(10, 10);
    //ocean.print();
    //clearConsole();
    for(int i = 0;;i++){
        clearConsole();
        ocean.print();
        ocean.tick();
        std::this_thread::sleep_for(std::chrono::seconds(constants::SPEED_S));
    }
    std::cout<<"FINISH";
    return 0;
}