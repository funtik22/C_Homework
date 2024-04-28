#include "NoAction.hpp"
#include "../Entities/Ocean.hpp"


bool NoAction::apply(Ocean& ocean) const{
    return true;
}


NoAction::ptrNoAction NoAction::Create(Object& obj_) {
    return ptrNoAction(new NoAction(obj_));
}