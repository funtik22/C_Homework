#pragma once
#ifndef _APEXPREDATOR_HPP_

#include "Predator.hpp"

class ApexPredator:public Predator{
    private:
        using ApexPredatorPtr = std::shared_ptr<ApexPredator>;
    public:
        static std::string NAME;
        ApexPredator();
        ~ApexPredator();
        ptrAction tick(int i, int j, Neighbourhood& n) override;
        static ApexPredatorPtr create();
};

#endif