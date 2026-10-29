#include "shared/wol_sink.hpp"
bool WolUserArray::Shrink_00766f00()
{
    if (Count * 3 > Capacity) return false;
    int capacity = Capacity / 2;
    if (capacity < 10) capacity = 10;
    if (capacity >= Capacity) return false;
    WOL::User *items = (WOL::User *)operator new(capacity * sizeof(WOL::User));
    if (Items) memcpy(items, Items, Count * sizeof(WOL::User));
    operator delete(Items);
    Items = items;
    Capacity = capacity;
    return true;
}
