#pragma once
#ifndef _STONE_HPP_
#define _STONE_HPP_

#include "Object.hpp"
#include <iostream>
#include "../MemoryPool/MixinPool.hpp"

class Stone: public Object, protected MixinPool<Stone>{
    private:
        using stonePtr = std::shared_ptr<Stone>;
    public:
        using MixinPool<Stone>::operator new;
        using MixinPool<Stone>::operator delete;
        static std::string NAME;
        static stonePtr create();
        Stone();
        //~Stone(){}
        Stone(const Stone &other);
        ptrAction tick(int i, int j, Neighbourhood& n) override;
};

#endif