#pragma once
#ifndef _MEMORYPOOL_HPP_
#define _MEMORYPOOL_HPP_
#include <vector>
#include <stack>
#include <memory>


template<typename ElemT>
class MemPool {
    public:
        //void* operator new(size_t size){};
        //void operator delete(void *ptr){};
        // Default constructor, does not allocate any memory
        MemPool(){}

        // Allocates memory for given number of objects
        MemPool(size_t _capacity):capacity(_capacity){
            std::cout<<"MemPool Constructor"<<std::endl;
            memory.resize(capacity);
            for(auto &&elem : memory){
                free.push(&elem);
            }
        }

        // Allocates memory for given number of objects and initializes them with `_default_value`
        // MemPool(size_t _capacity, const ElemT& _default_value){
        //     memory.resize(capacity);
        //     for(int i = 0; i<n; i++){
        //         memory[i] = _default_value;
        //     }
        // }

        // Re-allocates memory to fit new capacity
        void resize(size_t new_cap){
            capacity = new_cap;
            memory.resize(new_cap);
        }

        // Creates object inside memory pool and provides pointer to it
        // can return nullptr in case if memory cannot be allocated.
        template<class... Args>
        ElemT* get(Args&&... args){
            if(free.size()==0){
                return nullptr;
            }
            
            ElemT* elem = free.top();
            std::cout<<elem<<std::endl;
            free.pop();
            *elem = ElemT(args...);
            std::cout<<elem<<std::endl;
            return elem;
        }

        // Returns object to pool, calls destructor.
        // Returns bool to indicate error (maybe object is not from this pool?)
        bool put(ElemT* elem){
            elem->~ElemT();
            free.push(elem);
            return true;
        }
        
        // Creates object in memory pool and provides unique pointer to it
        template<class... Args>
        std::unique_ptr<ElemT, void(*)(ElemT*)> unique(Args&&... args){
            std::cout<<"MemPool unique"<<std::endl;
            if(free.size()==0){
                return std::unique_ptr<ElemT, void(*)(ElemT*)>(nullptr, [](ElemT *elem) {});
            }
            ElemT* elem = free.top();
            free.pop();
            *elem = ElemT(args...);
            return std::unique_ptr<ElemT, void(*)(ElemT*)>(elem, [](ElemT *elem) {
                            std::cout<<"deleter"<<std::endl;
                            elem->~ElemT();});
         }
        // Creates object in memory pool and provides shared pointer to it
        template<class... Args>
        std::shared_ptr<ElemT> shared(Args&&... args){
            std::cout<<"MemPool shared"<<std::endl;
            if(free.size()==0){
                return nullptr;
            }
            ElemT* elem = free.top();
            free.pop();
            *elem = ElemT(args...);
            return std::shared_ptr<ElemT>(elem, [](ElemT *elem) {
                            std::cout<<"deleter"<<std::endl;
                            elem->~ElemT();});
        }


        void* operator new(size_t size){
          std::cout<<"NEW"<<std::endl;
        }


        void operator delete(void *ptr){
          
        }

 

    private:
        std::vector<ElemT> memory;
        std::stack<ElemT*> free;
        size_t capacity;
};

#endif