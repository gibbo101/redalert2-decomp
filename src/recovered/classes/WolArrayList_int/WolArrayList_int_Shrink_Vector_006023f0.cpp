// bool WolArrayList<int>::Shrink_Vector() (0x006023F0): wlib's shrinkVector with new[]/delete[] (the class's
// inline Shrink, through operator new, schedules the stores differently for 4-byte elements).
// ownrdraw.cpp's wlib array lists (shared/wol_array_list.hpp, WolArrayList: Count, Capacity, Items): the
// out-of-line growVector/shrinkVector instances of its three element types (explicit specializations of
// Grow_Vector/Shrink_Vector). Element types are hypotheses: two 4-byte lists (int, HWND; identical code at
// two addresses) and one 20-byte record list.
#include "shared/wol_array_list.hpp"

template<> bool WolArrayList<int>::Shrink_Vector()
{
    if (Count * 3 > Capacity) return false;
    int capacity = Capacity / 2;
    if (capacity < 10) capacity = 10;
    if (capacity >= Capacity) return false;
    int *items = new int[capacity];
    if (Items) memcpy(items, Items, Count * sizeof(int));
    delete[] Items;
    Items = items;
    Capacity = capacity;
    return true;
}
