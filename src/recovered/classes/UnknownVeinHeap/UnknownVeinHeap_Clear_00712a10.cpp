// Empty the heap's occupied pointer slots, including sentinel slot zero.
// Its out-of-line copy is33body bytes and15 independently frozen NOPs.
#define RA2_VEIN_HEAP_CLEAR_SOURCE
#include "shared/vein_heap_core.hpp"

void UnknownVeinHeap::Clear()
{
    for (int index=0;index<=Count;++index) {
        Array[index]=0;
    }
    Count=0;
}
