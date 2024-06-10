#include <iostream>
#include "MemPool.hpp"
#include "MixinPool.hpp"


class Point : MixinPool<Point> {
private:
    int x;
    int y;
public:
    using MixinPool<Point>::operator new;
    using MixinPool<Point>::operator delete;
    Point(int x_, int y_) :x(x_), y(y_) { std::cout << "Point Constructor!" << std::endl; }
    Point() {}
    ~Point() { std::cout << "Point Destructor!" << std::endl; }
    int getX() { return x; }
    int getY() { return y; }
};