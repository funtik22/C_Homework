#include "ApexPredator.hpp"
#include "../constants.hpp"
#include "../Actions/NoAction.hpp"
#include "../Actions/Evalution.hpp"
#include "../Actions/Death.hpp"
#include "../Actions/Move.hpp"
#include "../Actions/Mating.hpp"
#include "../Actions/Eating.hpp"
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

ApexPredator::ApexPredator(int parentTime1, int parentTime2){
    id = Object::NUMBER_OBJECTS;
    Object::NUMBER_OBJECTS++;
    radius = 1;
    name = NAME;
    icon = 'A';
    evalutionTime = (parentTime1+parentTime2)/1.8 + (rand()%constants::N_APEXPREDATOR)/2;
    deathTime = (parentTime1+parentTime2)/1.8 + (rand()%constants::N_APEXPREDATOR)/2;
    hungryTime = evalutionTime / 2;
}

ApexPredator::ApexPredatorPtr ApexPredator::create(){
    return ApexPredator::ApexPredatorPtr(new ApexPredator());
}

ApexPredator::ApexPredatorPtr ApexPredator::create(int parentTime1, int parentTime2){
    return ApexPredator::ApexPredatorPtr(new ApexPredator(parentTime1, parentTime2));
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
    if (deathTime == liveTime || hungryLevel>=3){
        return Death::Create(i, j, *this);
    }


    //EATING
    ptrCell preyCell = n.getFirstNeighbour("Prey");
    ptrCell predatorCell = n.getFirstNeighbour("Predator");
    if(hungryLevel >=1 && preyCell!=nullptr && !n.searchNearbyObjects(preyCell.get()->get_i(), preyCell.get()->get_j(), "Reef")){
        hungryLevel = 0;
        hungryTime = evalutionTime/2;
        radius = 1;
        return Eating::create(Coordinate{i, j}, Coordinate{preyCell.get()->get_i(), preyCell.get()->get_j()},
                        *this, *(preyCell.get()->getObj().get()));
                        
    }
    if(predatorCell!=nullptr && hungryLevel == 2){
        hungryLevel = 0;
        hungryTime = evalutionTime/2;
        radius = 1;
        return Eating::create(Coordinate{i, j}, Coordinate{predatorCell.get()->get_i(), predatorCell.get()->get_j()},
                        *this, *(predatorCell.get()->getObj().get()));
    }
     

    //MATING
    if(adult == true && n.getFirstNeighbour("ApexPredator")!=nullptr && n.getFirstNeighbour("empty")!= nullptr){
     ptrCell obj2Cell = n.getFirstNeighbour("ApexPredator");      
     ptrCell emptyCell = n.getFirstNeighbour("empty");
     ptrObject obj2 = obj2Cell.get()->getObj();
     return Mating::create(Coordinate{i, j},
        Coordinate{obj2Cell.get()->get_i(), obj2Cell.get()->get_j()},
        Coordinate{emptyCell.get()->get_i(), emptyCell.get()->get_j()},
        *this, *(obj2Cell.get()->getObj().get()));

    }


    //MOVING
    ptrCell pCell = n.getFirstNeighbour("empty");
    if(pCell != nullptr){
        Cell *cell = pCell.get();
        std::pair<int, int> destination{cell->get_i(), cell->get_j()};
        return Move::Create(i, j, destination, *this);
    }
    return NoAction::Create(*this);
}