#ifndef POOLALLOCATOR_H
#define POOLALLOCATOR_H
#include <stdio.h>
#include <list>
#include <queue>
struct Part
{
    Part *next;
};

class PoolAllocator
{
    public:
        PoolAllocator(size_t partsPerPool) : mPartsPerPool(partsPerPool) {}

        void *allocate(size_t size);
        void deallocate(void *ptr, size_t size);
        void freePools();

        struct PoolObject;

    private:
        size_t mPartsPerPool;
        Part *mAlloc = nullptr;
        void allocatePool(size_t size);
        std::queue<Part*> freeAddr;
        std::list<void*> PoolBeginings;
};

#endif