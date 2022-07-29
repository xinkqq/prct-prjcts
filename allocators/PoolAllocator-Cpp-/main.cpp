
#include "PoolAllocator.h"


int main(){//Testing allocator
    PoolAllocator allocator(16,sizeof(char) * 2);
    allocator.PrintFreeChunks();
    char *str1 = reinterpret_cast<char*>(allocator.Allocate());
    allocator.PrintFreeChunks();
    char *str2 = reinterpret_cast<char*>(allocator.Allocate());
    allocator.PrintFreeChunks();
    allocator.Deallocate(str1);
    allocator.PrintFreeChunks();
    allocator.Deallocate(str2);
    allocator.PrintFreeChunks();
    char *str3 = reinterpret_cast<char*>(allocator.Allocate());
    allocator.PrintFreeChunks();
    char *str4 = reinterpret_cast<char*>(allocator.Allocate());
    allocator.PrintFreeChunks();
    char *str5 = reinterpret_cast<char*>(allocator.Allocate());
    allocator.PrintFreeChunks();
    char *str6 = reinterpret_cast<char*>(allocator.Allocate());
    allocator.PrintFreeChunks();
}
