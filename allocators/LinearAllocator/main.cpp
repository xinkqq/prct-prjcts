
#include "Allocator.h"
#include <cstring>

struct some_struct{
    int x,y,z;

};

int main() {
    Allocator allocator(512);
    auto *str1 = reinterpret_cast<some_struct*>(allocator.Allocate(sizeof(some_struct)));
    auto *str2 = reinterpret_cast<some_struct*>(allocator.Allocate(sizeof(some_struct)));
    auto *str3 = reinterpret_cast<some_struct*>(allocator.Allocate(sizeof(some_struct)));
    auto *str4 = reinterpret_cast<char*>(allocator.Allocate(sizeof(char)));
    auto *str5 = reinterpret_cast<some_struct*>(allocator.Allocate(sizeof(some_struct)));
    auto *str6 = reinterpret_cast<int*>(allocator.Allocate(sizeof(int)));
    str1->z = 5;
    str2->x = 16;
    str3->x = 17;
    *str4 = 'a';
    str5->x = 19;
    *str6 = 500;
    allocator.PrintListPtr();
    std :: cout << " " <<str1->x << " " << str2->x << " " << str3->x << " " << *str4<< " " << str5->x << " " << *str6 << std :: endl;
    allocator.Free();
    return 0;
}
