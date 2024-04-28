#pragma once
#ifndef _MATING_HPP_

#include "Action.hpp"


class Mating: public Action{
    using ptrMating = std::shared_ptr<Mating>;
    using Coordinate = std::pair<int, int>;
    public:
        Mating(Coordinate obj1C_, Coordinate obj2C_, 
               Coordinate newObjC_, Object& obj1_, Object& obj2_) : 
               Action(obj1_), obj1C(obj1C_), obj2C(obj2C_), newObjC(newObjC_),
               obj2(obj2_){}
        static ptrMating create(Coordinate obj1C_, Coordinate obj2C_, 
               Coordinate newObjC_, Object& obj1_, Object& obj2_);
        bool apply(Ocean& ocean) const override;
        ~Mating(){}
        private:
            Coordinate obj1C;
            Coordinate obj2C;
            Coordinate newObjC;
            Object& obj2;
};

#endif