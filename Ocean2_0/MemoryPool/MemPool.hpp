#pragma once
#ifndef _MEMORYPOOL_HPP_
#define _MEMORYPOOL_HPP_
#include <vector>
#include <stack>
#include <memory>
#include <algorithm>

template<typename ElemT>
class MemPool {
public:

    // Default constructor, does not allocate any memory
    MemPool() {}

    // Allocates memory for given number of objects
    MemPool(size_t _capacity) :capacity(_capacity) {
        memory.resize(capacity);
        for (auto&& elem : memory) {
            free.push(&elem);
        }
    }


    // Creates object inside memory pool and provides pointer to it
    // can return nullptr in case if memory cannot be allocated.
    template<class... Args>
    ElemT* get(Args&&... args) {
        if (free.size() == 0) {
            return nullptr;
        }
        ElemT* elem = free.top();
        free.pop();
        *elem = ElemT(args...);
        return elem;
    }

    // Returns object to pool, calls destructor.
    // Returns bool to indicate error (maybe object is not from this pool?)
    bool put(ElemT* elem) {
        if(&(*memory.begin()) <= elem && elem < &(*memory.end())){
            elem->~ElemT();
            free.push(elem);
            return true;
        }
        return false;
    }


    class Deleter {
        private:
            std::stack<ElemT*> &free;
        public:
            Deleter(std::stack<ElemT*> &free_):free(free_){}
            void operator()(ElemT* elem) {
                elem->~ElemT();
                free.push(elem);
                }
        };

    // Creates object in memory pool and provides unique pointer to it
    template<class... Args>
    std::unique_ptr<ElemT, Deleter> unique(Args&&... args) {
        if (free.size() == 0) {
            return std::unique_ptr<ElemT, Deleter>(nullptr, Deleter(free));
        }
        ElemT* elem = free.top();
        free.pop();
        *elem = ElemT(args...);
        return std::unique_ptr<ElemT, Deleter>(elem, Deleter(free));
    }

    // Creates object in memory pool and provides shared pointer to it
    template<class... Args>
    std::shared_ptr<ElemT> shared(Args&&... args) {
        if (free.size() == 0) {
            return nullptr;
        }
        ElemT* elem = free.top();
        free.pop();
        *elem = ElemT(args...);
        return std::shared_ptr<ElemT>(elem, Deleter(free));
    }


private:
    std::vector<ElemT> memory;
    std::stack<ElemT*> free;
    size_t capacity;
};


#endif