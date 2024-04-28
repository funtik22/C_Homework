#pragma once
#ifndef _REEF_HPP_
#define _REEF_HPP_

#include "Object.hpp"
#include <string>

class Reef : public Object{
    private:
        using ReefPtr = std::shared_ptr<Reef>;
    public:
        static std::string NAME;
        Reef();
        ~Reef() override;
        static ReefPtr create();
        ptrAction tick(int i, int j, Neighbourhood& n) override;
};

#endif