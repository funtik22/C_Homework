#pragma once
#ifndef _APEXPREDATOR_HPP_

#include "Predator.hpp"
#include "../MemoryPool/MixinPool.hpp"

class ApexPredator:public Predator, protected MixinPool<ApexPredator>{
    private:
        using ApexPredatorPtr = std::shared_ptr<ApexPredator>;
    public:
        using MixinPool<ApexPredator>::operator new;
        using MixinPool<ApexPredator>::operator delete;
        static std::string NAME;
        ApexPredator();
        ApexPredator(int parentTime1, int parentTime2);
        ptrAction tick(int i, int j, Neighbourhood& n) override;
        static ApexPredatorPtr create();
        static ApexPredatorPtr create(int parentTime1, int parentTime2);
};

#endif