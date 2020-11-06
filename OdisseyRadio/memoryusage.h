#pragma once
#include <iostream>
#include <memory>


struct AllocationMetrics
{
    uint32_t TotalAllocated = 0;
    uint32_t TotalFreed = 0;
    uint32_t CurrentUsage(){return TotalAllocated - TotalFreed;}
};

static AllocationMetrics s_AllocationMetrics;

void* operator new(size_t size)
{
    s_AllocationMetrics.TotalAllocated += size;

    return malloc(size);
}


void operator delete(void* memory, size_t size)
{
    s_AllocationMetrics.TotalFreed += size;

    free(memory);
}

static void PrintMemoryUsage()
{
    std::cout<< "Memory Usage: " << s_AllocationMetrics.CurrentUsage() << " bytes\n";
}
