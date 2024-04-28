#include "Predator.hpp"
#include "../constants.hpp"
#include "../Actions/NoAction.hpp"
#include "../Actions/Evalution.hpp"
#include "../Actions/Death.hpp"
#include "../Actions/Move.hpp"
#include "Cell.hpp"
#include "Neighbourhood.hpp"

std::string Predator::NAME = "Predator";

Predator::Predator(){
    id = Object::NUMBER_OBJECTS;
    Object::NUMBER_OBJECTS++;
    radius = 1;
    name = NAME;
    icon = 'R';
    evalutionTime = constants::N_PREDATOR + (rand()%constants::N_PREDATOR)/2;
    deathTime = constants::M_PREDATOR + (rand()%constants::M_PREDATOR)/2;
    hungryTime = evalutionTime / 2;
}

Predator::PredatorPtr Predator::create(){
    return Predator::PredatorPtr(new Predator());
}

Predator::~Predator(){};

Predator::ptrAction Predator::tick(int i, int j, Neighbourhood& n){
    
    liveTime++;
    hungryTime--;
    if(hungryTime == 0){
        hungryLevel++;
        hungryTime = evalutionTime/2;
        radius = 2;
    }
    if(evalutionTime == liveTime){
        adult = true;
    }
    if (deathTime == liveTime || hungryLevel>=2){
        std::cout<<"DEATH";
        return Death::Create(i, j, *this);
    }
 
    ptrCell pCell = n.getFirstNeighbour("empty");
   
    if(pCell != nullptr){
        Cell *cell = pCell.get();
        std::pair<int, int> destination{cell->get_i(), cell->get_j()};
        return Move::Create(i, j, destination, *this);
    } 
    return NoAction::Create(*this);
}