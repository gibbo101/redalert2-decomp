#include "shared/wol_sink.hpp"
template<> bool WolArrayList<Wstring>::Shrink_00767b20()
{
    if (Count * 3 > Capacity) return false;
    int capacity = Capacity / 2;
    if (capacity < 10) capacity = 10;
    if (capacity >= Capacity) return false;
    Wstring *items = (Wstring *)operator new(capacity * sizeof(Wstring));
    if (Items) memcpy(items, Items, Count * sizeof(Wstring));
    operator delete(Items);
    Items = items;
    Capacity = capacity;
    return true;
}
