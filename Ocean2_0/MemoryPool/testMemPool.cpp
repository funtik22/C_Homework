#include <iostream>
#include "MemPool.hpp"
#include "Point.cpp"
#include <memory>


int main(){
    std::cout<<"Start"<<std::endl;


{
    MemPool<Point> mp(3);
    Point *p = mp.get();
    Point *p1 = mp.get();

    if(mp.put(p)){
        std::cout<<"Push complete"<<std::endl;
    }
}


{
    Point *p = new Point(2, 3);
    std::cout<<p->getX()<<std::endl;
    delete p;
}


MemPool<Point> mp(3);
{
    auto shPtr = mp.shared(3, 1);
    std::cout<<shPtr.get()->getX()<<" "<<shPtr.get()->getY()<<std::endl;
}

{
    auto shPtr = mp.unique(3, 1);
    std::cout<<shPtr.get()->getX()<<" "<<shPtr.get()->getY()<<std::endl;
}


    std::cout<<"finish"<<std::endl;

}