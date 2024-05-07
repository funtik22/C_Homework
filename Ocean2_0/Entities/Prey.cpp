#include "Prey.hpp"
#include "../constants.hpp"
#include "../Actions/NoAction.hpp"
#include "../Actions/Evalution.hpp"
#include "../Actions/Death.hpp"
#include "../Actions/Move.hpp"
#include "../Actions/Mating.hpp"
#include "Cell.hpp"
#include "Neighbourhood.hpp"

std::string Prey::NAME = "Prey";

Prey::Prey(){
    id = Object::NUMBER_OBJECTS;
    Object::NUMBER_OBJECTS++;
    radius = 1;
    name = NAME;
    icon = 'P';
    evalutionTime = constants::N_PREY + (rand()%constants::N_PREY)/2;
    deathTime = constants::M_PREY + (rand()%constants::M_PREY)/2;
}

Prey::Prey(int parentTime1, int parentTime2){
    id = Object::NUMBER_OBJECTS;
    Object::NUMBER_OBJECTS++;
    radius = 1;
    name = NAME;
    icon = 'P';
    evalutionTime = (parentTime1+parentTime2)/1.8 + (rand()%constants::N_PREY)/2;
    deathTime = (parentTime1+parentTime2)/1.5 + (rand()%constants::M_PREY)/2;
}



Prey::PreyPtr Prey::create(){
    return Prey::PreyPtr(new Prey());
}

Prey::PreyPtr Prey::create(int parentTime1, int parentTime2){
    return Prey::PreyPtr(new Prey(parentTime1, parentTime2));
}


Prey::~Prey(){};

Prey::ptrAction Prey::tick(int i, int j, Neighbourhood& n){
    liveTime++;
    deathTime--;
    if(evalutionTime == liveTime){
        adult = true;
    }
    if (deathTime == liveTime){
        return Death::Create(i, j, *this);
    }
    if(adult == true && n.getFirstNeighbour("Prey")!=nullptr
                 && n.getFirstNeighbour("ApexPredator")==nullptr &&
                 n.getFirstNeighbour("Predator") == nullptr && 
                 n.getFirstNeighbour("empty")!= nullptr){
         ptrCell obj2Cell = n.getFirstNeighbour("Prey");      
         ptrCell emptyCell = n.getFirstNeighbour("empty");
         ptrObject obj2 = obj2Cell.get()->getObj();
         return Mating::create(Coordinate{i, j},
            Coordinate{obj2Cell.get()->get_i(), obj2Cell.get()->get_j()},
            Coordinate{emptyCell.get()->get_i(), emptyCell.get()->get_j()},
            *this, *(obj2Cell.get()->getObj().get()));
  
    }
    for(ptrCell pCell:n.getNeighbours("empty")){
        Cell *cell = pCell.get();
        if(!(n.searchNearbyObjects(cell->get_i(), cell->get_j(), "Predator")) &&
                    !(n.searchNearbyObjects(cell->get_i(), cell->get_j(), "ApexPredator"))){
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