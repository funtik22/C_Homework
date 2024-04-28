#include "ApexPredator.hpp"
#include "../constants.hpp"
#include "../Actions/NoAction.hpp"
#include "../Actions/Evalution.hpp"
#include "../Actions/Death.hpp"
#include "../Actions/Move.hpp"
#include "Cell.hpp"
#include "Neighbourhood.hpp"

std::string ApexPredator::NAME = "ApexPredator";

ApexPredator::ApexPredator(){
    id = Object::NUMBER_OBJECTS;
    Object::NUMBER_OBJECTS++;
    radius = 1;
    name = NAME;
    icon = 'A';
    evalutionTime = constants::N_APEXPREDATOR + (rand()%constants::N_APEXPREDATOR)/2;
    deathTime = constants::M_APEXPREDATOR + (rand()%constants::M_APEXPREDATOR)/2;
    hungryTime = evalutionTime / 2;
}

ApexPredator::ApexPredatorPtr ApexPredator::create(){
    return ApexPredator::ApexPredatorPtr(new ApexPredator());
}

ApexPredator::~ApexPredator(){};

ApexPredator::ptrAction ApexPredator::tick(int i, int j, Neighbourhood& n){
   
    liveTime++;
    hungryTime--;
    if(hungryTime == 0){
        hungryLevel++;
        hungryTime = evalutionTime/2;
        radius++;
    }
    if(evalutionTime == liveTime){
        adult = true;
    }
    if (deathTime == liveTime || hungryLevel>=4){
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