#pragma once
#include <atomic>
#include "Core/HAL/PlatformType.h"


/**
 * 엔진의 Heap 메모리의 할당량을 추적하는 클래스
 *
 * @note new로 생성한 객체는 추적하지 않습니다.
 */
struct FPlatformMemory
{
private:
    static std::atomic<uint64> TotalAllocationBytes;
    static std::atomic<uint64> TotalAllocationCount;

    static void IncrementStats(size_t Size)
    {
        // TotalAllocationBytes += Size;
        // ++TotalAllocationCount;

        // 멀티스레드 대비
        TotalAllocationBytes.fetch_add(Size, std::memory_order_relaxed);
        TotalAllocationCount.fetch_add(1, std::memory_order_relaxed);
    }

    static void DecrementStats(size_t Size)
    {
        // TotalAllocationBytes -= Size;
        // --TotalAllocationCount;

        // 멀티스레드 대비
        TotalAllocationBytes.fetch_sub(Size, std::memory_order_relaxed);
        TotalAllocationCount.fetch_sub(1, std::memory_order_relaxed);
    }

public:
    static uint64 GetTotalAllocationBytes()
    {
        return TotalAllocationBytes;
    }

    static uint64 GetTotalAllocationCount()
    {
        return TotalAllocationCount;
    }

    static void* Malloc(size_t Size);
    static void* AlignedMalloc(size_t Size, size_t Alignment);
    static void Free(void* Address, size_t Size);
};
