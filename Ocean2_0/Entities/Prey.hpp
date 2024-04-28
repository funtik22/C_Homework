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
        ~Prey() override;
        ptrAction tick(int i, int j, Neighbourhood& n) override;
        static PreyPtr create();
    protected:
        bool adult = false;
        int deathTime; 


};

#endif