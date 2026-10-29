#include "shared/wol_sink.hpp"
bool WolServerArray::Grow_00768110()
{
    if (Count < Capacity) return false;
    int capacity = Count * 2;
    if (capacity < 10) capacity = 10;
    WOL::Server *items = (WOL::Server *)operator new(capacity * sizeof(WOL::Server));
    memset(items, 0, capacity * sizeof(WOL::Server));
    if (Items) memcpy(items, Items, Count * sizeof(WOL::Server));
    operator delete(Items);
    Items = items;
    Capacity = capacity;
    return true;
}
