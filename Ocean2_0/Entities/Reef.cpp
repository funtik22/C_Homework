#include "Reef.hpp"
#include "../constants.hpp"
#include "../Actions/NoAction.hpp"
#include "../Actions/Evalution.hpp"

std::string Reef::NAME = "Reef";

Reef::Reef(){
    id = Object::NUMBER_OBJECTS;
    Object::NUMBER_OBJECTS++;
    name = NAME;
    icon = '-';
    evalutionTime = constants::N_REEF + (rand()%constants::N_REEF)/2;
}

Reef::ReefPtr Reef::create(){
    return Reef::ReefPtr(new Reef());
}

Reef::~Reef(){};


Reef::ptrAction Reef::tick(int i, int j, Neighbourhood& n){
    liveTime++;
    if(evalutionTime == liveTime){
        return Evalution::Create(i, j, *this);
    }
    return NoAction::Create(*this);
}