#include "Ocean.hpp"
#include <iostream>
#include <vector>
#include "Cell.hpp"
#include "Stone.hpp"
#include "Object.hpp"
#include "Reef.hpp"
#include "Prey.hpp"
#include "../Actions/Action.hpp"
#include <iomanip>
#include "Neighbourhood.hpp"
#include "Predator.hpp"
#include "ApexPredator.hpp"


Ocean::Ocean(size_t rows_, size_t cols_):rows(rows_), cols(cols_){
    for(size_t i = 0; i<rows; i++){
        for(size_t j = 0; j<cols; j++){
            ptrObject obj = nullptr;
            int random = rand()%15;
            if(random <= 2) {
                obj = Stone::create();
            }
            else if(random <= 4){
                obj = Reef::create();
            }
             else if(random <= 6){
                obj = Prey::create();
            }
            else if(random <= 9){
                obj = Predator::create();
               
            }
            else if(random <= 10){
                obj = ApexPredator::create();
    
            }
            else{
            }
            data.push_back(Cell::create(obj, i, j));
        }
    }
};


Ocean::ptrCell Ocean::getCell(int i, int j){
      if(i<0){
          i = rows + i;
      }
      if(j<0){
          j = cols + j;
      }
      i%=rows;
      j%=cols;
      return data[i*cols+j];
};


void Ocean::print(){
            for(size_t i = 0; i<rows; i++){
                for(size_t j = 0; j<cols; j++){
                    if(data[i*cols+j].get()->isEmpty()){
                        std::cout<<std::setw(3)<<" ";
                    }
                    else{
                        Cell *cell = data[i*cols+j].get();
                        Object *obj = cell->getObj().get();
                        std::cout<<std::setw(3)<<obj->getIcon();
                    }
                }
                std::cout<<std::endl;
            }
        }


void Ocean::tick(){
    std::vector<std::string> entities = {"empty", Predator::NAME, Prey::NAME, ApexPredator::NAME, 
                                                                        Stone::NAME, Reef::NAME};
    for(auto &&entity:entities){
        numberEntities[entity] = 0; 
    } 
    std::vector<ptrAction> actions;
    for(size_t i = 0; i<rows; i++){
            for(size_t j = 0; j<cols; j++){
                if(data[i*cols+j].get()->isEmpty()){
                    continue;
                }    
                Cell *cell = data[i*cols+j].get();
                Object *obj = cell->getObj().get();
                numberEntities[obj->getName()]++;
                Neighbourhood n(i, j, *obj, *this);
                actions.push_back(obj->tick(i, j, n));
            }
            
    }
    for(ptrAction action: actions){
        Action *act = action.get();
        bool z = act->apply(*this); 
    }
    if(numberEntities[Prey::NAME]+numberEntities[Predator::NAME] == 0
        || numberEntities[ApexPredator::NAME] + numberEntities[Predator::NAME] == 0
        || numberEntities[ApexPredator::NAME] + numberEntities[Prey::NAME] == 0){
            std::cout<<"FINISH";
            exit(0);
        }
}