#pragma once
#ifndef _MEMORYPOOL_HPP_
#define _MEMORYPOOL_HPP_
#include <vector>

template<typename ElemT>
class MemPool {
    public:
        // Default constructor, does not allocate any memory
        MemPool(){}

        // Allocates memory for given number of objects
        MemPool(size_t _capacity):capacity(_capacity){
            memory.resize(capacity);
        }

        // Allocates memory for given number of objects and initializes them with `_default_value`
        MemPool(size_t _capacity, const ElemT& _default_value){
            memory.resize(capacity);
            for(size_t i = 0; i<memory.size(); i++){
                memory[i] = _default_value;
            }
        }

        // Re-allocates memory to fit new capacity
        void resize(size_t new_cap){
            capacity = new_cap;
            memory.resize(new_cap);
        }

        // Creates object inside memory pool and provides pointer to it
        // can return nullptr in case if memory cannot be allocated.
        template<class... Args>
        ElemT* get(Args&&... args){
            if(lastElem == capacity){
                return nullptr;
            }
            memory[lastEtem] = ElemT(... Args);
            lastEtem++;
            return &memory[lastElem-1]
        }

        // Returns object to pool, calls destructor.
        // Returns bool to indicate error (maybe object is not from this pool?)
        bool put(ElemT* elem);

        // Creates object in memory pool and provides unique pointer to it
        template<class... Args>
        std::unique_ptr<ElemT, Deleter> unique(Args&&... args);

        // Creates object in memory pool and provides shared pointer to it
        template<class... Args>
        std::shared_ptr<ElemT> shared(Args&&... args);

    private:
        std::vector<ElemT> memory;
        size_t lastEtem;
        size_t capacity;
};

#endif