#include "poolAllocator.h"
#include <stdio.h>
#include <stdlib.h>
#include "iostream"

void *PoolAllocator::allocate(size_t size) {
    if (freeAddr.empty())
    {
        std::cout << "New pool\n";
        allocatePool(size);
    }
    
    // Reserve part from pool
    Part *freePart = freeAddr.front();
    freeAddr.pop();

    return freePart;
}

void PoolAllocator::deallocate(void *part, size_t size) {
    freeAddr.push(reinterpret_cast<Part *>(part));
    reinterpret_cast<Part *>(part)->next = nullptr;
    mAlloc = reinterpret_cast<Part *>(part);
}

void PoolAllocator::allocatePool(size_t partSize) {
    size_t poolSize = mPartsPerPool * partSize;
    Part *poolBegin = reinterpret_cast<Part *>(malloc(poolSize));
    Part *part = poolBegin;

    for (int i = 0; i < mPartsPerPool-1; i++)
    {
        freeAddr.push(part);
        part->next = reinterpret_cast<Part *>(reinterpret_cast<char *>(part) + partSize);
        part = part->next;
    }
    
    part->next = nullptr;

    PoolBeginings.push_front(poolBegin);
}

void PoolAllocator::freePools() {
    for (auto const& i : PoolBeginings) {
        free(i);
    }
}