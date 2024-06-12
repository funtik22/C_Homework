#pragma once
#ifndef _DEATH_HPP_
#define _DEATH_HPP_

#include "Action.hpp"

class Ocean;


class Death: public Action {
    using ptrDeath = std::shared_ptr<Death>; 
    public:
        Death(int i_, int j_, Object& obj_):i(i_), j(j_), Action(obj_){}
        static ptrDeath Create(int i_, int j_, Object& obj_);
        bool apply(Ocean& ocean) const override;
        ~Death(){}
    private:
        int i;
        int j;
};


#endif