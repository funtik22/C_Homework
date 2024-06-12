#include "Evalution.hpp"
#include "../entities/Ocean.hpp"
#include "../entities/Object.hpp"
#include "../entities/Stone.hpp"
#include "../entities/Cell.hpp"
#include "../entities/Reef.hpp"
#include "../entities/Prey.hpp"
#include <iostream>

Evalution::ptrEvalution Evalution::Create(int i_, int j_, Object& obj_){
    return ptrEvalution(new Evalution(i_, j_, obj_));
}

bool Evalution::apply(Ocean& ocean) const{
        Cell *cell = ocean.getCell(i, j).get();
        if(cell->isEmpty()){
            return false;
        }
        if(obj.getName() == Stone::NAME){
            cell->setObj(Reef::create());
        }
        if(obj.getName() == Reef::NAME){
            cell->setObj(Stone::create());
        }
        if(obj.getName() == Prey::NAME){
        }
        #ifdef PRINT_ACTIONS
        std::cout<<"EVOLUTION "<<i<<" "<<j<<std::endl;
        #endif
        return true;
}