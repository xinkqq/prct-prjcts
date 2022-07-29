//
// Created by xink on 25.04.22.
//

#ifndef LINKPRACTICE_ALLOCATOR_H
#define LINKPRACTICE_ALLOCATOR_H
#include <iostream>


struct ListNode{ // struct that consists of blocks pointers
    void *next_block_ptr;
    ListNode *next = nullptr;
};

class Allocator{
private:
    ListNode *root;
    void *base_pointer;
    void *pointer_of_next_chunk;
    std :: size_t memory_size = 0;
    std :: size_t available_memory = 0;

public:
    explicit Allocator(std :: size_t);
    ~Allocator();
    explicit Allocator(const Allocator &allocator) = delete;
    Allocator& operator = (const Allocator &allocator) = delete;
    explicit Allocator(Allocator &&allocator) noexcept;
    Allocator& operator = (Allocator &&allocator) noexcept;
    void *Allocate(std :: size_t);
    void Free();
    void PrintListPtr();
};

Allocator ::Allocator(std :: size_t allocator_size) : memory_size(allocator_size){
    if(memory_size == 0){
        throw std :: runtime_error("Can't allocate 0 bytes of memory\n");
    }
    else{
        root = new ListNode;
        available_memory = memory_size;
        base_pointer = malloc(memory_size);
        if(base_pointer == nullptr){
            throw std :: runtime_error("Memory hasn't been allocated\n");
        }
        else{
            pointer_of_next_chunk = base_pointer;
            root->next_block_ptr = pointer_of_next_chunk;
        }
    }
}

void *Allocator::Allocate(std::size_t memory_to_allocate) {
    if(memory_to_allocate > available_memory){
        throw std :: runtime_error("Not enough memory in allocator\n");
    }
    else{
        void *returning_chunk_of_memory = pointer_of_next_chunk;
        //casting to char, cause its size is 1 byte,so we can allocate 1 * memory_to_allocate bytes
        pointer_of_next_chunk = (char*)pointer_of_next_chunk + sizeof(char) * memory_to_allocate;
        //Adding new block ptr in list
        ListNode *next = new ListNode;
        ListNode *current = root;
        while(current->next != nullptr){
            current = current->next;
        }
        current->next = next;
        next->next = nullptr;
        next->next_block_ptr = pointer_of_next_chunk;
        //////////////////////////////////////////////
        available_memory = available_memory - memory_to_allocate;
        std :: cout << "Allocator info:" << memory_size << " " << available_memory  << " " << (void*)base_pointer << " "<< (void*)pointer_of_next_chunk << std :: endl;
        return returning_chunk_of_memory;
    }
}

Allocator ::Allocator(Allocator &&allocator) noexcept {
    this->base_pointer = allocator.base_pointer;
    this->pointer_of_next_chunk = allocator.pointer_of_next_chunk;
    this->available_memory = allocator.available_memory;
    allocator.base_pointer = nullptr;
    allocator.Free();
}


void Allocator::Free() {
    std :: cout << "Info before deallocate:" << memory_size << " " << available_memory;
    pointer_of_next_chunk = base_pointer;
    memory_size = 0;
    available_memory = 0;
}

Allocator :: ~Allocator() {
    ListNode *current = root;
    while(current->next != nullptr){
        ListNode *temp = current;
        current = current->next;
        delete temp;
    }
    delete current;
    free(base_pointer);
}

void Allocator :: PrintListPtr(){ //Printing list of pointers on allocated memory in allocator
    ListNode *current = root;
    while(current->next != nullptr){
        std :: cout << current->next_block_ptr << "\t";
        current = current->next;
    }
    std :: cout << "\n";
}

Allocator &Allocator::operator=(Allocator &&allocator) noexcept {
    if(this != &allocator){
        this->base_pointer = allocator.base_pointer;
        this->pointer_of_next_chunk = allocator.pointer_of_next_chunk;
        this->available_memory = allocator.available_memory;
        allocator.base_pointer = nullptr;
        allocator.Free();
    }
    else{
        return *this;
    }
}


#endif //LINKPRACTICE_ALLOCATOR_H
