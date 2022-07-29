//
// Created by vitec on 25.04.2022.
//

#include <iostream>
#include <string>


#ifndef CLIENT_POOLALLOCATOR_H
#define CLIENT_POOLALLOCATOR_H


struct ListNode{
    void *free_ptr;
    ListNode *next;
};

class PoolAllocator {
private:
    void *base_pointer;
    void *end_pointer;
    ListNode *root_of_free_chunks;
    int value_of_free_chunks = 0;
    std :: size_t chunk_size;
    std :: size_t heap_memory;
public:
    PoolAllocator(std :: size_t heap_memory,std :: size_t chunk_size);
    PoolAllocator(const PoolAllocator &poolAllocator) = delete;
    PoolAllocator &operator = (const PoolAllocator &poolAllocator) = delete;
    void *Allocate();
    void Deallocate(void *chunk_ptr);
    void PrintFreeChunks();
    ~PoolAllocator();

};


#endif //CLIENT_POOLALLOCATOR_H
