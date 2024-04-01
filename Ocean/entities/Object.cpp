#include ".\Ocean\Actions\Action.cpp"

class Object{
    virtual ~Object() = default;
    virtual Action* tick(const Neighbourhood &n) = 0;
};