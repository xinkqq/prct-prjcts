//
// Created by vitec on 12.05.2022.
//

#include <stdio.h>
#include <malloc.h>
#include <stdint.h>
#include <assert.h>
#include <string.h>

#ifndef MY_MALLOC_ALLOCATOR_H
#define MY_MALLOC_ALLOCATOR_H

typedef struct ListNode{ //list struct
    void *chunk_ptr;
    struct ListNode *next;
}ListNode_t;

typedef struct allocator{ //allocator struct
    size_t chunk_size;
    size_t allocator_size;
    uint16_t value_of_free_chunks;
    void *base_ptr; //ptr to memory in heap
    void *end_ptr; // ptr on the end of the memory
    ListNode_t *free_chunks_list; // root of free chunks
}allocator_t;

allocator_t create_allocator(size_t allocator_size,size_t chunk_size); //creating new allocator
void *allocate(allocator_t*); //allocate one chunk of allocator
void *deallocate(allocator_t*,void *ptr); // deallocate chunk
void delete_allocator(allocator_t); // free all allocator memory

void PrintFreeChunks(allocator_t);

#endif //MY_MALLOC_ALLOCATOR_H
