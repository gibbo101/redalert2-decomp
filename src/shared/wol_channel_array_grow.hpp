#ifndef RA2_WOL_CHANNEL_ARRAY_GROW_HPP
#define RA2_WOL_CHANNEL_ARRAY_GROW_HPP
#include "shared/wol_sink.hpp"
// The real capacity operation appears twice in original Insert 0x00766C20.
// No independent out-of-line helper address or kept copy is claimed.
inline bool WolChannelArray::Grow_When_Full()
{
    if (Count < Capacity) return false;
    int capacity = Count * 2;
    if (capacity < 10) capacity = 10;
    WOL::Channel *items = (WOL::Channel *)operator new(capacity * sizeof(WOL::Channel));
    memset(items, 0, capacity * sizeof(WOL::Channel));
    if (Items) memcpy(items, Items, Count * sizeof(WOL::Channel));
    operator delete(Items);
    Items = items;
    Capacity = capacity;
    return true;
}
#endif
