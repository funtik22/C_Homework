#include "Move.hpp"
#include "../entities/Ocean.hpp"
#include "../entities/Object.hpp"
#include "../entities/Cell.hpp"
#include "../entities/Prey.hpp"
#include <iostream>

Move::ptrMove Move::Create(int i_, int j_, std::pair<int, int> destination_ , Object& obj_){
    return ptrMove(new Move(i_, j_, destination_, obj_));
}

bool Move::apply(Ocean& ocean) const{
        Cell *cell = ocean.getCell(i, j).get();
        Cell *dCell = ocean.getCell(destination.first, destination.second).get();
        if(dCell->isEmpty() && cell->getObj()->getId() == obj.getId()){
            dCell->setObj(cell->getObj());
            cell->setObj(nullptr);
            return true;
        }
        return false;
}