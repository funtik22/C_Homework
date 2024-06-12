#pragma once
#pragma once
#ifndef _ACTION_HPP_
#define _ACTION_HPP_

#include <memory>

class Cell;
class Object;
class Ocean;

class Action{
    private:
    protected:
        using ptrCell = std::shared_ptr<Cell>;
        using ptrObject = std::shared_ptr<Object>;
        using ptrAction = std::shared_ptr<Action>;
        Object& obj;
    public:
      static ptrAction Create(Object& obj_);
      Action(Object& obj_):obj(obj_){}
      virtual ~Action() = default;
      virtual bool apply(Ocean& ocean) const = 0;

};

#endif