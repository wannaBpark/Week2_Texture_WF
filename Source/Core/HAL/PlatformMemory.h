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

    static void IncrementStats(size_t Size);
    static void DecrementStats(size_t Size);

    /* 추적하는 클래스 목록 */
    template <typename T, int IndexSize>
    friend struct TContainerAllocator;

    friend class FObjectFactory;

public:
    static uint64 GetTotalAllocationBytes();
    static uint64 GetTotalAllocationCount();


};
