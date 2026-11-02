// bool WolArrayList<UnknownListEntry_6017c0>::Grow_Vector() (0x006017C0): a 24-byte element list (0x006025A0
// copies one).
// ownrdraw.cpp's wlib array lists (shared/wol_array_list.hpp, WolArrayList: Count, Capacity, Items): the
// out-of-line growVector/shrinkVector instances of its element types (explicit specializations of
// Grow_Vector/Shrink_Vector). Element types are hypotheses.
#include "shared/wol_array_list.hpp"

// UnknownListEntry_6017c0: defined beside 0x00601490 in this unit.

template<> bool WolArrayList<UnknownListEntry_6017c0>::Grow_Vector()
{
    return Grow();
}
