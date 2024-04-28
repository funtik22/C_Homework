#pragma once
#ifndef _CELL_HPP_
#define _CELL_HPP_

#include <memory>
#include <iostream>

class Object;

class Cell{
    private:
        using ptrObj = std::shared_ptr<Object>;
        using ptrCell = std::shared_ptr<Cell>;
        ptrObj obj;
        size_t i;
        size_t j;
    public:
        static ptrCell create(ptrObj obj_, size_t i_, size_t j_);
        Cell(ptrObj obj_, size_t i_, size_t j_):obj(obj_), i(i_), j(j_){};
        ptrObj getObj() const {return obj;};
        void setObj(ptrObj obj_);
        bool operator<(const Cell& other);
        size_t get_i() const{return i;}
        size_t get_j() const{return j;}
        bool isEmpty() const{return obj.get()==nullptr;}
};

#endif