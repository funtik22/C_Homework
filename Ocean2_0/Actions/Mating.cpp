#include "Mating.hpp"
#include "Action.hpp"
#include "..\Entities\Ocean.hpp" 
#include "..\Entities\Object.hpp"
#include "..\Entities\Cell.hpp"
#include "..\Entities\Prey.hpp"
#include "..\Entities\Predator.hpp"
#include "..\Entities\ApexPredator.hpp"

Mating::Mating(Coordinate obj1C_, Coordinate obj2C_, Coordinate newObjC_, 
                Object& obj1_, Object& obj2_): Action(obj1_), obj1C(obj1C_), 
                obj2C(obj2C_), newObjC(newObjC_), 
                obj2(obj2_){} 

Mating::ptrMating Mating::create(Coordinate obj1C_, Coordinate obj2C_, 
               Coordinate newObjC_, Object& obj1_, Object& obj2_){
                return ptrMating(new Mating(obj1C_, obj2C_, newObjC_, obj1_, obj2_));
               }

bool Mating::apply(Ocean& ocean) const {
    
    Cell *cellObj1 = ocean.getCell(obj1C.first, obj1C.second).get();
    Cell *cellObj2 = ocean.getCell(obj2C.first, obj2C.second).get();
    Cell *cellNewObj = ocean.getCell(newObjC.first, newObjC.second).get();
    
    if( !cellObj1->isEmpty() && !cellObj2->isEmpty() &&
        obj.getId() == cellObj1->getObj()->getId() &&
       obj2.getId() == cellObj2->getObj()->getId() &&
       cellNewObj->isEmpty()
       ){   
            if(obj.getName() == Prey::NAME){
                cellNewObj->setObj(Prey::create(obj.getDeathTime(), obj2.getDeathTime()));
                 #ifdef PRINT_ACTIONS
                 std::cout<<"NEW PREY "<<newObjC.first<<" "<<newObjC.second<<std::endl;
                 #endif
            }
            if(obj.getName() == Predator::NAME){
                cellNewObj->setObj(Predator::create(obj.getDeathTime(), obj2.getDeathTime()));
                 #ifdef PRINT_ACTIONS
                 std::cout<<"NEW PREDATOR "<<newObjC.first<<" "<<newObjC.second<<std::endl;
                 #endif
            }
            if(obj.getName() == ApexPredator::NAME){
                cellNewObj->setObj(ApexPredator::create());
                 #ifdef PRINT_ACTIONS
                 std::cout<<"NEW APEXPREDATOR "<<newObjC.first<<" "<<newObjC.second<<std::endl;
                 #endif
            }

          
            return true;
        }
    return false;
}