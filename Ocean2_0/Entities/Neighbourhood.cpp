#include "Neighbourhood.hpp"
#include "Ocean.hpp"
#include "Object.hpp"
#include "Cell.hpp"

Neighbourhood::Neighbourhood(int i_, int j_, Object& obj_, Ocean& ocean_):
                                            i(i_), j(j_), obj(obj_), ocean(ocean_){
    generate_neighbourhood(i, j, obj.getRadius());
};


void Neighbourhood::generate_neighbourhood(int i, int j, int radious){
    std::vector<std::pair<int, int>> move{  {i, j+1}, {i+1, j+1}, 
                                    {i+1, j}, {i+1, j-1}, {i, j-1},
                                    {i-1, j-1}, {i-1, j}, {i-1, j+1}};
    if(radious == 0){
        return;
    }
    for(std::pair<int, int> p: move){
             Cell* cell = ocean.getCell(p.first, p.second).get();
             if(p.first == i && p.second == j){
                continue;
             }
             if(cell->isEmpty()){
                neighbours["empty"].insert(ocean.getCell(p.first, p.second));
             }
             else{
                std::string nameObj = cell->getObj().get()->getName();
                neighbours[nameObj].insert(ocean.getCell(p.first, p.second));
             }
             generate_neighbourhood(p.first, p.second, radious-1); 
          }
};


bool Neighbourhood::searchNearbyObjects(int i, int j, std::string nameObject){
     std::vector<std::pair<int, int>> move{  {i, j+1}, {i+1, j+1}, 
                                            {i+1, j}, {i+1, j-1}, {i, j-1},
                                            {i-1, j-1}, {i-1, j}, {i-1, j+1}};
    
     for(std::pair<int, int> p: move){
        Cell* cell = ocean.getCell(p.first, p.second).get();
        if(cell->getObj() == nullptr){
            if(nameObject == "empty"){
                return true;
            }
            else{
                continue;
            }
        }
        std::string nameObj = cell->getObj().get()->getName();
        if(nameObj == nameObject){
            return true;
        }
    }
    return false;
}

Neighbourhood::ptrCell Neighbourhood::getFirstNeighbour(std::string nameObject) 
    {   
        if(neighbours[nameObject].size()<=0){
            return nullptr;
        }
        return *(neighbours[nameObject].begin());
    }

std::set<Neighbourhood::ptrCell> Neighbourhood::getNeighbours(std::string nameObject){
    return neighbours[nameObject];
};