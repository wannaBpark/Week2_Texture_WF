#include "PlatformMemory.h"


std::atomic<uint64> FPlatformMemory::TotalAllocationBytes = 0;
std::atomic<uint64> FPlatformMemory::TotalAllocationCount = 0;


void* FPlatformMemory::Malloc(size_t Size)
{
    void* Ptr = std::malloc(Size);
    if (Ptr)
    {
        IncrementStats(Size);
    }
    return Ptr;
}

void* FPlatformMemory::AlignedMalloc(size_t Size, size_t Alignment)
{
    void* Ptr = _aligned_malloc(Size, Alignment);
    if (Ptr)
    {
        IncrementStats(Size);
    }
    return Ptr;
}

void FPlatformMemory::Free(void* Address, size_t Size)
{
    if (Address)
    {
        DecrementStats(Size);
        std::free(Address);
    }
}
