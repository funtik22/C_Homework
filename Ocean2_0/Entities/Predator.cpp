#include "Predator.hpp"
#include "../constants.hpp"
#include "../Actions/NoAction.hpp"
#include "../Actions/Evalution.hpp"
#include "../Actions/Death.hpp"
#include "../Actions/Move.hpp"
#include "../Actions/Mating.hpp"
#include "../Actions/Eating.hpp"

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


Predator::Predator(int parentTime1, int parentTime2){
  id = Object::NUMBER_OBJECTS;
    Object::NUMBER_OBJECTS++;
    radius = 1;
    name = NAME;
    icon = 'R';
    evalutionTime = (parentTime1+parentTime2)/1.8 + (rand()%constants::N_PREDATOR)/2;
    deathTime = (parentTime1+parentTime2)/1.5 + (rand()%constants::N_PREDATOR/2);
}

Predator::PredatorPtr Predator::create(){
    return Predator::PredatorPtr(new Predator());
}

Predator::PredatorPtr Predator::create(int parentTime1, int parentTime2){
    return Predator::PredatorPtr(new Predator(parentTime1, parentTime2));
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
        return Death::Create(i, j, *this);
    }


    //EATING
    ptrCell preyCell = n.getFirstNeighbour("Prey");
    if(hungryLevel>=1 && preyCell!=nullptr && !n.searchNearbyObjects(preyCell.get()->get_i(), preyCell.get()->get_j(), "Reef")){
        hungryLevel = 0;
        hungryTime = evalutionTime/2;

        return Eating::create(Coordinate{i, j}, Coordinate{preyCell.get()->get_i(), preyCell.get()->get_j()},
                        *this, *(preyCell.get()->getObj().get()));
    }


    //MATING
    if(adult == true && n.getFirstNeighbour("Predator")!=nullptr
             && n.getFirstNeighbour("ApexPredator")==nullptr &&
             n.getFirstNeighbour("empty")!= nullptr){
     
     ptrCell obj2Cell = n.getFirstNeighbour("Predator");      
     ptrCell emptyCell = n.getFirstNeighbour("empty");
     ptrObject obj2 = obj2Cell.get()->getObj();
     return Mating::create(Coordinate{i, j},
        Coordinate{obj2Cell.get()->get_i(), obj2Cell.get()->get_j()},
        Coordinate{emptyCell.get()->get_i(), emptyCell.get()->get_j()},
        *this, *(obj2Cell.get()->getObj().get()));

    }


    //MOVING
    for(ptrCell pCell:n.getNeighbours("empty")){
        Cell *cell = pCell.get();
        if(!(n.searchNearbyObjects(cell->get_i(), cell->get_j(), "ApexPredator"))){
            std::pair<int, int> destination{cell->get_i(), cell->get_j()};
            return Move::Create(i, j, destination, *this); 
        }
    }
    ptrCell pCell = n.getFirstNeighbour("empty");
    
    if(pCell != nullptr){
        Cell *cell = pCell.get();
        std::pair<int, int> destination{cell->get_i(), cell->get_j()};
        return Move::Create(i, j, destination, *this);
    }



    return NoAction::Create(*this);
}