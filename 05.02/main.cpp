#include <iostream>
#include "Circle.cpp"
#include "DateTime.cpp"

#define COST_METER_BETON 1000
#define COST_METER_FENCE 2000
#define EARTH_RADIOUS 6378.1

int main(){
    std::cout << "TASK 1:" << std::endl;
    std::cout << "\t1.1.Earth and rope" << std::endl;
    Circle Earth;
    Earth.set_radious(EARTH_RADIOUS);
    Earth.set_ference(Earth.get_ference()+1);
    std::cout << "\t\tThe gap: " << (Earth.get_radious()-EARTH_RADIOUS) << " m" << std::endl;
    std::cout << "\t1.2.Swimming pool" << std::endl;
    Circle smallCircle, bigCircle;
    smallCircle.set_radious(3);
    bigCircle.set_radious(4);
    double trackArea = bigCircle.get_area() - smallCircle.get_area();
    double costBeton = COST_METER_BETON * trackArea;
    double costFence = COST_METER_FENCE * bigCircle.get_ference();
    std::cout << "\t\tThe cost of beton: " << costBeton << " rub" << std::endl;
    std::cout << "\t\tThe cost of fence: " << costFence << " rub" << std::endl;
    std::cout << "\t\tThe total cost: " << costBeton + costFence << " rub" << std::endl;


    std::cout << "TASK 2:" << std::endl;
    DateTime date1(1, 2, 2022);
    DateTime date2("22 january 2024, monday");
    DateTime date3;
    DateTime date4(date1);
    std::cout << "\tdate1: " << date1.get_today() << std::endl;
    std::cout << "\tdate2: " << date2.get_today() << std::endl;
    std::cout << "\tdate3: " << date3.get_today() << std::endl;
    std::cout << "\tdate4: " << date4.get_today() << std::endl;
    std::cout << "\tyesterday date3: " << date3.get_yesterday() << std::endl;
    std::cout << "\ttommorow date3: " << date3.get_tommorow() << std::endl;
    std::cout << "\tfuture 300 days date3: " << date3.get_future(300) << std::endl;
    std::cout << "\tpast 300 days date3: " << date3.get_past(300) << std::endl;
    std::cout << "\tdifference between date2 and date3: " << date2.get_difference(date3) << std::endl;
}
