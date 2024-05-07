#include "Death.hpp"
#include "../entities/Ocean.hpp"
#include "../entities/Object.hpp"
#include "../entities/Cell.hpp"
#include "../entities/Prey.hpp"
#include <iostream>

Death::ptrDeath Death::Create(int i_, int j_, Object& obj_){
    return ptrDeath(new Death(i_, j_, obj_));
}

bool Death::apply(Ocean& ocean) const{
        Cell *cell = ocean.getCell(i, j).get();
        if(cell->isEmpty()) {
            return false;
        }
        cell->setObj(nullptr);
        std::cout<<"DEATH "<<i<<" "<<j<<std::endl;
        return true;
}