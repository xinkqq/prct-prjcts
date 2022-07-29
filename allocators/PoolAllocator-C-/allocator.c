//
// Created by vitec on 12.05.2022.
//

#include "allocator.h"

allocator_t create_allocator(size_t allocator_size,size_t chunk_size) {
    assert(allocator_size);
    assert(chunk_size);
    if(allocator_size % chunk_size != 0){
        assert(0);
    };
    allocator_t new_allocator;
    new_allocator.allocator_size = allocator_size;
    new_allocator.chunk_size = chunk_size;
    new_allocator.base_ptr = malloc(allocator_size);
    new_allocator.end_ptr = new_allocator.base_ptr + allocator_size - 1;
    printf("Base pointer:0x%p End pointer:0x%p\n",(void*)new_allocator.base_ptr,(void*)new_allocator.end_ptr);
    new_allocator.value_of_free_chunks = allocator_size/chunk_size;
    new_allocator.free_chunks_list = (ListNode_t*)malloc(sizeof(ListNode_t));
    new_allocator.free_chunks_list->chunk_ptr = new_allocator.base_ptr;
    new_allocator.free_chunks_list->next = NULL;
    ListNode_t *current = new_allocator.free_chunks_list;
    for(int i = 1;i < new_allocator.value_of_free_chunks;i++){
        ListNode_t *new_list_node = malloc(sizeof(ListNode_t));
        new_list_node->chunk_ptr = current->chunk_ptr + chunk_size;
        new_list_node->next = NULL;
        current->next = new_list_node;
        current = current->next;
    }
    return new_allocator;
}

void *allocate(allocator_t *allocator){
    if(allocator->value_of_free_chunks == 0){
        printf("There is no free chunks\n");
        return NULL;
    }
    else{
        void* chunk = allocator->free_chunks_list->chunk_ptr;
        ListNode_t *temp = allocator->free_chunks_list;
        if(allocator->free_chunks_list->next != NULL) {
            allocator->free_chunks_list = allocator->free_chunks_list->next;
        }else{
            allocator->free_chunks_list = NULL;
        }
        free(temp);
        allocator->value_of_free_chunks = allocator->value_of_free_chunks - 1;
        return chunk;
    }
}

void *deallocate(allocator_t* allocator,void *ptr){
    if(allocator->value_of_free_chunks + 1 > allocator->allocator_size/allocator->chunk_size){
        printf("Can't deallocate non existing memory");
        assert(0);
    }else {
        if (allocator->free_chunks_list != NULL) {
            ListNode_t *current = allocator->free_chunks_list;
            while (current->next != NULL) {
                current = current->next;
            }
            ListNode_t *deallocated_chunk = (ListNode_t *) malloc(sizeof(ListNode_t));
            current->next = deallocated_chunk;
            deallocated_chunk->next = NULL;
            deallocated_chunk->chunk_ptr = ptr;
        } else {
            allocator->free_chunks_list = (ListNode_t *) malloc(sizeof(ListNode_t));
            allocator->free_chunks_list->next = NULL;
            allocator->free_chunks_list->chunk_ptr = ptr;
        }
        allocator->value_of_free_chunks = allocator->value_of_free_chunks + 1;
    }
};

void delete_allocator(allocator_t allocator){
    ListNode_t *current = allocator.free_chunks_list;
    if(current != NULL) {
        while (current->next != NULL) {
            ListNode_t *temp = current;
            current = current->next;
            free(temp);
        }
        free(current);
    }
    free(allocator.base_ptr);
}
void PrintFreeChunks(allocator_t allocator){
    ListNode_t *current = allocator.free_chunks_list;
    printf("There is %d free chunks\n",allocator.value_of_free_chunks);
    for(int i = 0;i < allocator.value_of_free_chunks;i++){
        printf("%d pointer:0x%p\t",i,(void*)current->chunk_ptr);
        current = current->next;
    }
    printf("\n");
}