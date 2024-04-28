#pragma once
#ifndef _NEIGHBOURHOOD_HPP_

#include <set>
#include <memory>
#include <map>
#include <string>

class Cell;
class Ocean;
class Object;

class Neighbourhood{
    using ptrCell = std::shared_ptr<Cell>;
    public:
        ptrCell getFirstNeighbour(std::string nameObject);
        std::set<ptrCell> getNeighbours(std::string nameObject);
        bool searchNearbyObjects(int i, int j, std::string nameObject);
        Neighbourhood(int i, int j, Object& obj , Ocean& ocean);
    private:
        int i;
        int j;
        Ocean& ocean;
        std::map<std::string, std::set<ptrCell>> neighbours;
        Object& obj;
        void generate_neighbourhood(int i, int j, int radious);
};

#endif