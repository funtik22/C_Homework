#pragma once
#ifndef _EATING_HPP_
#define _EATING_HPP_

#include "Action.hpp"

class Eating: public Action{
    using ptrEating = std::shared_ptr<Eating>;
    using Coordinate = std::pair<int, int>;
    public:
        Eating(Coordinate obj1C_, Coordinate obj2C_, Object& obj1_, Object& obj2_); 
        static ptrEating create(Coordinate obj1C_, Coordinate obj2C_, Object& obj1_, Object& obj2_);
        bool apply(Ocean& ocean) const override;
        ~Eating(){}
        private:
            Coordinate obj1C;
            Coordinate obj2C;
            Object& obj2;
};


#endif