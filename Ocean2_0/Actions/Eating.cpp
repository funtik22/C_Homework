#include "Eating.hpp"
#include "Action.hpp"
#include "..\Entities\Ocean.hpp" 
#include "..\Entities\Object.hpp"
#include "..\Entities\Cell.hpp"
#include "..\Entities\Prey.hpp"
#include "..\Entities\Predator.hpp"
#include "..\Entities\ApexPredator.hpp"

Eating::Eating(Coordinate obj1C_, Coordinate obj2C_,  Object& obj1_, Object& obj2_): 
                Action(obj1_), obj1C(obj1C_), obj2C(obj2C_), obj2(obj2_){} 

Eating::ptrEating Eating::create(Coordinate obj1C_, Coordinate obj2C_, Object& obj1_, Object& obj2_){
                return ptrEating(new Eating(obj1C_, obj2C_, obj1_, obj2_));
               }

bool Eating::apply(Ocean& ocean) const {
    
    Cell *cellObj1 = ocean.getCell(obj1C.first, obj1C.second).get();
    Cell *cellObj2 = ocean.getCell(obj2C.first, obj2C.second).get();

    if( !cellObj1->isEmpty() && !cellObj2->isEmpty() &&
            obj.getId() == cellObj1->getObj()->getId() &&
            obj2.getId() == cellObj2->getObj()->getId()){
            cellObj2->setObj(cellObj1->getObj());
            cellObj1->setObj(nullptr);
            std::cout<<"EATING "<<obj1C.first<<" "<<obj1C.second<<" "<<obj2C.first<<" "<<obj2C.second<<std::endl;
            return true;
        }
    return false;
}