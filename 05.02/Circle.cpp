#include "Circle.hpp"
#include <cmath>


void Circle::set_radious(double radious){
    this->radious = radious;
    this->ference = 2*M_PI*radious;
    this->area = M_PI*radious*radious;
}

void Circle::set_ference(double ference){
    this->ference = ference;
    this->radious = ference/(2*M_PI);
    this->area = M_PI*this->radious*this->radious;
}

void Circle::set_area(double area){
    this->area = area;
    this->radious =sqrt(area / M_PI);
    this->ference = 2*M_PI*this->radious;
}

double Circle::get_radious() const{
    return this->radious;
}

double Circle::get_ference() const{
    return this->ference;
}

double Circle::get_area() const{
    return this->area;
}