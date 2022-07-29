//
// Created by vitec on 25.04.2022.
//

#include "PoolAllocator.h"

PoolAllocator::PoolAllocator(std::size_t heap_memory, std::size_t chunk_size) : chunk_size(chunk_size),heap_memory(heap_memory){
    if(this->heap_memory == 0){
        throw std :: runtime_error("Can't create empty allocator\n");
    }
    if(this->chunk_size == 0){
        throw std :: runtime_error("Can't create allocator with empty chunks\n");
    }
    if(heap_memory % chunk_size != 0){ // To avoid memory fragmentation
        throw std :: runtime_error("Chunk size isn't a multiple of main memory size\n");
    }
    base_pointer = malloc(this->heap_memory);
    end_pointer = reinterpret_cast<char*>(base_pointer) + this->heap_memory;
    root_of_free_chunks = new ListNode;
    root_of_free_chunks->next = nullptr;
    root_of_free_chunks->free_ptr = base_pointer;
    value_of_free_chunks++;
    ListNode *current = root_of_free_chunks;
    for(int i = 1;i < this->heap_memory/this->chunk_size;i++){
        ListNode *new_ptr = new ListNode;
        new_ptr->next = nullptr;
        new_ptr->free_ptr = reinterpret_cast<char*>(base_pointer) + sizeof(char) * chunk_size * i;
        current->next = new_ptr;
        current = current->next;
        value_of_free_chunks++;
    }
}



void PoolAllocator :: PrintFreeChunks(){
    //Printing places of free chunks
    if(value_of_free_chunks == 0){
        std :: cout << "There is no free chunks" << std :: endl;
        return;
    }
    else {
        std :: cout << "Value of free chunks:" << value_of_free_chunks << std :: endl;
        ListNode *current = root_of_free_chunks;
        while (current->next != nullptr) {
            std::cout << (void *) current->free_ptr << "\t";
            current = current->next;
        }
        std::cout << (void *) current->free_ptr << "\t";
        std::cout << "\n";
    }
}

PoolAllocator::~PoolAllocator() {
    ListNode *current = root_of_free_chunks;
    if(current != nullptr) {
        while (current->next != nullptr) {
            ListNode *temp = current;
            current = current->next;
            delete temp;
        }
    }
    delete current;
    free(base_pointer);

}
void PoolAllocator :: Deallocate(void *chunk_ptr){ //Free separate chunk
    if(root_of_free_chunks != nullptr) {
        ListNode *current = root_of_free_chunks;
        while (current->next != nullptr) {
            current = current->next;
        }
        ListNode *deallocated_chunk = new ListNode;
        current->next = deallocated_chunk;
        deallocated_chunk->next = nullptr;
        deallocated_chunk->free_ptr = chunk_ptr;
    }else{
        root_of_free_chunks = new ListNode;
        root_of_free_chunks->next = nullptr;
        root_of_free_chunks->free_ptr = chunk_ptr;
    }
    value_of_free_chunks++;
}
void *PoolAllocator::Allocate() {
    if(value_of_free_chunks != 0) {
        void *returning_chunk = reinterpret_cast<void*>(root_of_free_chunks->free_ptr);
        ListNode *temp = root_of_free_chunks;
        if (root_of_free_chunks->next != nullptr) {
            root_of_free_chunks = root_of_free_chunks->next;
        } else {
            root_of_free_chunks = nullptr;
        }
        delete temp;
        if(value_of_free_chunks != 0){
            value_of_free_chunks--;
        }
        std :: cout << "Allocated:" << returning_chunk << std :: endl;
        return returning_chunk;
    }
    else{
        std :: cout << "There is no free chunks,can't allocate more\n";
        return nullptr;
    }
}
