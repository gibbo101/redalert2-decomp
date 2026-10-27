#include "shared/wol_sink.hpp"
bool WolChannelArray::Shrink_00766dc0()
{
    if (Count * 3 > Capacity) return false;
    int capacity = Capacity / 2;
    if (capacity < 10) capacity = 10;
    if (capacity >= Capacity) return false;
    WOL::Channel *items = (WOL::Channel *)operator new(capacity * sizeof(WOL::Channel));
    if (Items) memcpy(items, Items, Count * sizeof(WOL::Channel));
    operator delete(Items);
    Items = items;
    Capacity = capacity;
    return true;
}
