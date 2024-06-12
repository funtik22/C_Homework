#pragma once
#ifndef _PREY_HPP_
#define _PREY_HPP_

#include "Object.hpp"
#include "../MemoryPool/MixinPool.hpp"

class Prey : public Object, protected MixinPool<Prey>{
    private:
        using PreyPtr = std::shared_ptr<Prey>;
    public:
        using MixinPool<Prey>::operator new;
        using MixinPool<Prey>::operator delete;
        bool isAdult() const {return adult;}
        static std::string NAME;
        Prey();
        //~Prey(){}
        Prey(int parentTime1, int parentTime2);
        ptrAction tick(int i, int j, Neighbourhood& n) override;
        static PreyPtr create();
        static PreyPtr create(int parentTime1, int parentTime2);
    protected:
        bool adult = false;
        using Coordinate = std::pair<int, int>;
};

#endif