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
        cell->setObj(nullptr);
        return true;
}