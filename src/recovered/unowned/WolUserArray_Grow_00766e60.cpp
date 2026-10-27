#include "shared/wol_sink.hpp"
bool WolUserArray::Grow_00766e60()
{
    if (Count < Capacity) return false;
    int capacity = Count * 2;
    if (capacity < 10) capacity = 10;
    WOL::User *items = (WOL::User *)operator new(capacity * sizeof(WOL::User));
    memset(items, 0, capacity * sizeof(WOL::User));
    if (Items) memcpy(items, Items, Count * sizeof(WOL::User));
    operator delete(Items);
    Items = items;
    Capacity = capacity;
    return true;
}
