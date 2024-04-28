#pragma once
#ifndef NO_ACTION_HPP_
#include "Action.hpp"

class Ocean;

class NoAction:public Action{
    using ptrNoAction = std::shared_ptr<NoAction>; 
    public:
        NoAction(Object& obj_):Action(obj_){}
        static ptrNoAction Create(Object& obj_);
        bool apply(Ocean& ocean) const override;
        ~NoAction(){}
};


#endif