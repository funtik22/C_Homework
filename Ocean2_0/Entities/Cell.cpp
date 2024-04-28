#include "Cell.hpp"


Cell::ptrCell Cell::create(ptrObj obj_, size_t i_, size_t j_){
    return ptrCell(new Cell(obj_, i_, j_));
}

bool Cell::operator<(const Cell& other){
    if(i==other.i){
        return j<other.j;
    }
    return i<other.i;
}

void Cell::setObj(ptrObj obj_){
    obj = obj_;
}