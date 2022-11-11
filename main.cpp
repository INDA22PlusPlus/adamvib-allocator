#include "poolAllocator.cpp"
#include <iostream>

struct PoolObject {
    // example data
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

// Number of parts per pool
PoolAllocator PoolObject::poolAllocator{4};

void testPoolAllocator() {
    // Number of pointers to store
    int objectSize = 10;
 
    PoolObject *objects[objectSize];
    
    for (int i = 0; i < objectSize; ++i) {
        objects[i] = new PoolObject();
        std::cout << objects[i] << "\n";
    }

    for (int i = objectSize; i >= 0; --i) {
        delete objects[i];
    }
}

int main() {
    testPoolAllocator();

    // Deallocate all pools
    PoolObject::poolAllocator.freePools();

    return 0;
}