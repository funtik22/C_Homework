#pragma once
#ifndef _PREY_HPP_

#include "Object.hpp"

class Prey : public Object{
    private:
        using PreyPtr = std::shared_ptr<Prey>;
    public:
        bool isAdult() const {return adult;}
        static std::string NAME;
        Prey();
        Prey(int parentTime1, int parentTime2);
        ~Prey() override;
        ptrAction tick(int i, int j, Neighbourhood& n) override;
        static PreyPtr create();
        static PreyPtr create(int parentTime1, int parentTime2);
    protected:
        bool adult = false;
        using Coordinate = std::pair<int, int>;
};

#endif