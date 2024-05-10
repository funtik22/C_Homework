#pragma once
#ifndef _OCEAN_HPP_
#define _OCEAN_HPP_


#include <memory>
#include <vector>
#include <set>
#include <map>

class Cell;
class Action;
class Object;


class Ocean{
    private:        
        using ptrCell = std::shared_ptr<Cell>;
        using ptrAction = std::shared_ptr<Action>;
        using ptrObject = std::shared_ptr<Object>;
        size_t rows;
        size_t cols;
        std::vector<ptrCell> data;
        std::map<std::string, int> numberEntities;
        
    public:
        Ocean(size_t rows_, size_t cols_);
        ptrCell getCell(int i, int j);
        void tick();
        void print();
};

#endif