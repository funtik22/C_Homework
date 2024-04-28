#pragma once
#ifndef _STONE_HPP_
#define _STONE_HPP_

#include "Object.hpp"
#include <iostream>

class Stone: public Object{
    private:
        using stonePtr = std::shared_ptr<Stone>;
    public:
        static std::string NAME;
        static stonePtr create();
        Stone();
        Stone(const Stone &other);
        ~Stone() override;
        ptrAction tick(int i, int j, Neighbourhood& n) override;
};

#endif