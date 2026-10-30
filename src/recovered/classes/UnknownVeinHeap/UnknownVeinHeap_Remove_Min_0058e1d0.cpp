#define RA2_VEIN_HEAP_REMOVE_MIN_IMPLEMENTATION
#include "shared/vein_heap.hpp"
UnknownVeinNode *UnknownVeinHeap::Remove_Min()
{
        if (Count == 0) {
            return 0;
        }
        UnknownVeinNode *top = Array[1];
        Array[1] = Array[Count];
        Array[Count] = 0;
        Count--;
        Sift_Down(1);
        return top;
    }
