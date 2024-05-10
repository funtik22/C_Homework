#include "../constants.hpp"
#include <iostream>
#include "../Actions/Evalution.hpp"
#include "../Actions/NoAction.hpp"
#include "Stone.hpp"

std::string Stone::NAME = "stone";

Stone::Stone(){
    id = Object::NUMBER_OBJECTS;
    Object::NUMBER_OBJECTS++;
    name = NAME;
    icon = '*';
    evalutionTime = constants::N_STONE + (rand()%constants::N_STONE)/2;
}

Stone::stonePtr Stone::create(){
    return Stone::stonePtr(new Stone());
}

Stone::ptrAction Stone::tick(int i, int j, Neighbourhood& n){
    liveTime++;
    if(evalutionTime == liveTime){
        return Evalution::Create(i, j, *this);
    }
    return NoAction::Create(*this);
}

Stone::~Stone(){};


Stone::Stone(const Stone &other){
    radius = other.radius;
    icon = other.icon;
    evalutionTime = other.evalutionTime;   
}