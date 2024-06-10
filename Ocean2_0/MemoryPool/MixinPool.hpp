#pragma once
#ifndef _MIXINPOOL_HPP_
#define _MIXINPOOL_HPP_

#include "MemPool.hpp"

template <typename T>
class MixinPool {
private:
    static inline MemPool<T> memPool = MemPool<T>(1000);
public:

    template<class... Args>
    static void* operator new(size_t count, Args&&... args) {
        return memPool.get(args...);
    }

    static void operator delete(void* ptr) {
        bool z = memPool.put(static_cast<T*>(ptr));
    }

    template<class... Args>
    static std::shared_ptr<T> get_shared(Args&&... args){
        return memPool.shared(args...);
    }
};


#endif