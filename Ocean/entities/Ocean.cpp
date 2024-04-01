#include <iostream>
#include <memory>
#include <vector>
#include "Neighbourhood.cpp"
#include "Object.cpp"
#include ".\Actions\Action.cpp"

class Ocean{
    using Cell = std::shared_ptr<Object>;
    private:
        size_t rows;
        size_t cols;
        std::vector<Cell> data;
    public:

        Ocean(size_t rows_, size_t cols_): rows(rows_), cols(cols_){
            for(int i = 0; i<cols*rows; i++){
                data.push_back(Cell(new Object()));
            }
        }

        Neighbourhood generate_neighbourhood(size_t i, size_t j, size_t speed){

        }

        void tick(){
            for(int i = 0; i<rows; i++){
                for(int j = 0; j<cols; j++){
                    Object *obj = data[i*cols+j].get();
                    Neighbourhood neighbors = generate_neighbourhood(i, j, obj->get_speed());
                    Action act* = obj->tick(neighbors);
                    act.apply()
                }
            }
        }


    

};