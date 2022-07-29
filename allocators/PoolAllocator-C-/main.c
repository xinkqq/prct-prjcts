#include "allocator.h"



int main(int argc,char **argv) {//tests
    allocator_t allocator = create_allocator(4,1);
    PrintFreeChunks(allocator);
    char *new_ptr = (char*)allocate(&allocator);
    char *new_ptr2 = (char*)allocate(&allocator);
    char *new_ptr3 = (char*)allocate(&allocator);
    char *new_ptr4 = (char*)allocate(&allocator);
    PrintFreeChunks(allocator);
    deallocate(&allocator,(void*)new_ptr2);
    deallocate(&allocator,(void*)new_ptr3);
    deallocate(&allocator,(void*)new_ptr);
    deallocate(&allocator,(void*)new_ptr4);
    PrintFreeChunks(allocator);
    return 0;
}
