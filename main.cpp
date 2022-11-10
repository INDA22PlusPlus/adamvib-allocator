#include "poolAllocator.cpp"
#include <iostream>

struct PoolObject {
    int data[5];
    bool aBool;

    static PoolAllocator poolAllocator;

    static void *operator new(size_t size) {
        return poolAllocator.allocate(size);
    }

    static void operator delete(void *ptr, size_t size) {
        poolAllocator.deallocate(ptr, size);
    }
};

PoolAllocator PoolObject::poolAllocator{8};

void usePoolAllocator() {
    // Number of pointers to store
    int objectSize = 10;
 
    PoolObject *objects[objectSize];
    
    for (int i = 0; i < objectSize; ++i) {
        objects[i] = new PoolObject();
    }
        
    for (int i = objectSize; i >= 0; --i) {
        delete objects[i];
    }
}

int main() {
    usePoolAllocator();

    return 0;
}