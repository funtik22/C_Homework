#pragma once
#ifndef _REEF_HPP_
#define _REEF_HPP_

#include "Object.hpp"
#include <string>
#include "../MemoryPool/MixinPool.hpp"

class Reef : public Object, protected MixinPool<Reef>{
    private:
        using ReefPtr = std::shared_ptr<Reef>;
    public:
        using MixinPool<Reef>::operator new;
        using MixinPool<Reef>::operator delete;
        static std::string NAME;
        Reef();
        //~Reef(){}
        static ReefPtr create();
        ptrAction tick(int i, int j, Neighbourhood& n) override;
};

#endif