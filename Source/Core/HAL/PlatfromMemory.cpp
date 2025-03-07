#include "PlatfromMemory.h"


std::atomic<uint64> FPlatformMemory::TotalAllocationBytes = 0;
std::atomic<uint64> FPlatformMemory::TotalAllocationCount = 0;

void FPlatformMemory::IncrementStats(size_t Size)
{
    // TotalAllocationBytes += Size;
    // ++TotalAllocationCount;

    // 멀티스레드 대비
    TotalAllocationBytes.fetch_add(Size, std::memory_order_relaxed);
    TotalAllocationCount.fetch_add(1, std::memory_order_relaxed);
}

void FPlatformMemory::DecrementStats(size_t Size)
{
    // TotalAllocationBytes -= Size;
    // --TotalAllocationCount;

    // 멀티스레드 대비
    TotalAllocationBytes.fetch_sub(Size, std::memory_order_relaxed);
    TotalAllocationCount.fetch_sub(1, std::memory_order_relaxed);
}

uint64 FPlatformMemory::GetTotalAllocationBytes()
{
    return TotalAllocationBytes;
}

uint64 FPlatformMemory::GetTotalAllocationCount()
{
    return TotalAllocationCount;
}
