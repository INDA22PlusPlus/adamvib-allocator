#include "poolAllocator.h"
#include <stdio.h>
#include <stdlib.h>

void *PoolAllocator::allocate(size_t size) {
    if (mAlloc == nullptr)
    {
        mAlloc = allocatePool(size);
    }
    
    Part *freePart = mAlloc;
    mAlloc = mAlloc->next;

    return freePart;
}

Part *PoolAllocator::allocatePool(size_t partSize) {
    size_t poolSize = mPartsPerPool * partSize;
    Part *poolBegin = reinterpret_cast<Part *>(malloc(poolSize));
    Part *part = poolBegin;

    for (int i = 0; i < mPartsPerPool-1; i++)
    {
        part->next = reinterpret_cast<Part *>(reinterpret_cast<char *>(part) + partSize);
        part = part->next;
    }
    
    part->next = nullptr;

    return poolBegin;
}

void PoolAllocator::deallocate(void *part, size_t size) {
    reinterpret_cast<Part *>(part)->next = nullptr;
    mAlloc = reinterpret_cast<Part *>(part);
}