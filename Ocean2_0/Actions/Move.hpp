#pragma once
#ifndef _MOVE_HPP_
#define _MOVE_HPP_

#include "Action.hpp"

class Ocean;


class Move: public Action {
    using ptrMove = std::shared_ptr<Move>; 
    public:
        Move(int i_, int j_, std::pair<int, int> destination_,  Object& obj_):
        i(i_),  j(j_), destination(destination_), Action(obj_){}
        static ptrMove Create(int i_,  int j_,std::pair<int, int> destination_, Object& obj_);
        bool apply(Ocean& ocean) const override;
        ~Move(){}
    private:
        int i;
        int j;
        std::pair<int, int> destination;
};


#endif