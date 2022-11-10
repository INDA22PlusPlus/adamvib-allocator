#include "poolAllocator.h"
#include <stdio.h>
#include <stdlib.h>

void *PoolAllocator::allocate(size_t size) {
    if (freeAddr.empty())
    {
        mAlloc = allocatePool(size);
    }
    
    Part *freePart = freeAddr.back();
    freeAddr.pop_back();

    return freePart;
}

void PoolAllocator::deallocate(void *part, size_t size) {
    freeAddr.push_back(reinterpret_cast<Part *>(part));
    reinterpret_cast<Part *>(part)->next = nullptr;
    mAlloc = reinterpret_cast<Part *>(part);
}

Part *PoolAllocator::allocatePool(size_t partSize) {
    size_t poolSize = mPartsPerPool * partSize;
    Part *poolBegin = reinterpret_cast<Part *>(malloc(poolSize));
    Part *part = poolBegin;

    for (int i = 0; i < mPartsPerPool-1; i++)
    {
        freeAddr.push_back(part);
        part->next = reinterpret_cast<Part *>(reinterpret_cast<char *>(part) + partSize);
        part = part->next;
    }
    
    part->next = nullptr;

    return poolBegin;
}

void PoolAllocator::freePool(void *ptr) {
    free(ptr);
}