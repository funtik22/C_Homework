#include ".\Ocean\entities\Object.cpp"
#include <memory>



class Action{
    using objectPtr = str::shared_ptr<Object>;
    public:
        Action(objectPtr obj_):obj(obj_){}
        virtual ~Action() = default;
    protected:
        objectPtr obj;
    private:
        virtual bool apply(Ocean& ocean) const = 0;
};