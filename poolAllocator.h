#ifndef POOLALLOCATOR_H
#define POOLALLOCATOR_H
#include <stdio.h>
#include <list>
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

        struct PoolObject;

    private:
        size_t mPartsPerPool;
        Part *mAlloc = nullptr;
        Part *allocatePool(size_t size);
        void freePool(void *ptr);
        std::list<Part*> freeAddr;
};

#endif