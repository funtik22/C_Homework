#include <iostream>
#include "MemPool.hpp"
class Point : public MemPool<Point>{
    private:
        int x;
        int y;
    public:
        using MemPool<Point>::operator new;
        using MemPool<Point>::operator delete;
        Point(int x_, int y_):x(x_), y(y_){std::cout<<"Point Constructor!"<<std::endl;}
        Point(){}
        ~Point(){std::cout<<"Point Destructor!"<<std::endl;}
        int getX() { return x;}
        int getY() { return y;}
};