#include "Prey.hpp"
#include "../constants.hpp"
#include "../Actions/NoAction.hpp"
#include "../Actions/Evalution.hpp"
#include "../Actions/Death.hpp"
#include "../Actions/Move.hpp"
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

Prey::PreyPtr Prey::create(){
    return Prey::PreyPtr(new Prey());
}

Prey::~Prey(){};

Prey::ptrAction Prey::tick(int i, int j, Neighbourhood& n){
    liveTime++;
    deathTime--;
    if(evalutionTime == liveTime){
        adult = true;
    }
    if (deathTime == liveTime){
        std::cout<<"DEATH";
        return Death::Create(i, j, *this);
    }

    // if(adult == true && n.getFirstNeighbour("Prey")!=nullptr
    //             || n.getFirstNeighbour("ApexPredator")==nullptr ||
    //             n.getFirstNeighbour("Predator") == nullptr || 
    //             n.getFirstNeighbour("empty")!= nullptr){
    //     ptrCell pCell = n.getFirstNeighbour("empty")
        
    // }

    for(ptrCell pCell:n.getNeighbours("empty")){
        
        Cell *cell = pCell.get();
        if(!(n.searchNearbyObjects(cell->get_i(), cell->get_j(), "Predator")) &&
                    !(n.searchNearbyObjects(cell->get_i(), cell->get_j(), "ApexPredator"))){
            
            std::pair<int, int> destination{cell->get_i(), cell->get_j()};
            //std::cout<<std::endl<<"SUPERMOVE "<<i<<" "<<j<<" "<<destination.first<<" "<<destination.second<<std::endl;
            return Move::Create(i, j, destination, *this); 
        }
    }
    ptrCell pCell = n.getFirstNeighbour("empty");
    
    if(pCell != nullptr){
        Cell *cell = pCell.get();
        std::pair<int, int> destination{cell->get_i(), cell->get_j()};
        //std::cout<<std::endl<<"RANDOMMOVE "<<i<<" "<<j<<" "<<destination.first<<" "<<destination.second<<std::endl;
        return Move::Create(i, j, destination, *this);
    } 
    return NoAction::Create(*this);
}