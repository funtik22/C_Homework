#pragma once
#ifndef _EVALUTION_HPP_
#define _EVALUTION_HPP_

#include "Action.hpp"

class Ocean;


class Evalution: public Action {
    using ptrEvalution = std::shared_ptr<Evalution>; 
    public:
        Evalution(int i_, int j_, Object& obj_):i(i_), j(j_), Action(obj_){}
        static ptrEvalution Create(int i_, int j_, Object& obj_);
        bool apply(Ocean& ocean) const override;
        ~Evalution(){}
    private:
        int i;
        int j;
};


#endif