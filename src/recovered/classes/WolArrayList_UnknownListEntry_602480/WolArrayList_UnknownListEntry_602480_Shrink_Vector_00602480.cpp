// bool WolArrayList<UnknownListEntry_602480>::Shrink_Vector() (0x00602480)
// ownrdraw.cpp's wlib array lists (shared/wol_array_list.hpp, WolArrayList: Count, Capacity, Items): the
// out-of-line growVector/shrinkVector instances of its three element types (explicit specializations of
// Grow_Vector/Shrink_Vector). Element types are hypotheses: two 4-byte lists (int, HWND; identical code at
// two addresses) and one 20-byte record list.
#include "shared/wol_array_list.hpp"

// A 20-byte list element of ownrdraw.cpp (layout unknown).
struct UnknownListEntry_602480 { int unknown_00[5]; };

template<> bool WolArrayList<UnknownListEntry_602480>::Shrink_Vector()
{
    return Shrink();
}
