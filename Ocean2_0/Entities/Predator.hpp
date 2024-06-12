#pragma once
#ifndef _PREDATOR_HPP_

#include "Prey.hpp"
#include "../MemoryPool/MixinPool.hpp"
class Predator: public Prey, protected MixinPool<Predator>{
    private:
        using PredatorPtr = std::shared_ptr<Predator>;
    public:
        using MixinPool<Predator>::operator new;
        using MixinPool<Predator>::operator delete;
        static std::string NAME;
        Predator();
        Predator(int parentTime1, int parentTime2);
        ptrAction tick(int i, int j, Neighbourhood& n) override;
        static PredatorPtr create();
        static PredatorPtr create(int parentTime1, int parentTime2);
        int isHungry() {return hungryLevel;}
    protected:
        int hungryLevel = 0;
        int hungryTime;

};

#endif