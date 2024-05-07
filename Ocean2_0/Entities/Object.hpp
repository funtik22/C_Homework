#pragma once
#ifndef _OBJECT_HPP_
#define _OBJECT_HPP_

#include <memory>
#include <set>
#include <iostream>
#include <string>

class Action;
class Cell;
class Neighbourhood;

class Object{
    protected:
        long long id;
        std::string name;
        int radius = 0;
        char icon;
        int evalutionTime;
        int liveTime = 0;
        int deathTime;
        using ptrCell = std::shared_ptr<Cell>;
        using ptrAction = std::shared_ptr<Action>;
        using ptrObject = std::shared_ptr<Object>;
    public:
        static long long NUMBER_OBJECTS;
        virtual ~Object() = default;
        virtual ptrAction tick(int i, int j, Neighbourhood& n) = 0;
        int getRadius() const {return radius;};
        char getIcon() const {return icon;};
        std::string getName() const{return name;}
        int getEvalutionTime() const {return evalutionTime;};
        void setEvalutionTime(int _time) {evalutionTime = _time;}
        long long getId() const {return id;}
        int getLiveTime() const {return liveTime;}
        int getDeathTime() const {return deathTime;}
};


#endif