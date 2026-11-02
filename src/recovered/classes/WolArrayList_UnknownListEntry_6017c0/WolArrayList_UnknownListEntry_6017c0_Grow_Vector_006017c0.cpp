// bool WolArrayList<UnknownListEntry_6017c0>::Grow_Vector() (0x006017C0): a 24-byte element list (0x006025A0
// copies one; its elements hold two WideStrings at +4 and +8).
// ownrdraw.cpp's wlib array lists (shared/wol_array_list.hpp, WolArrayList: Count, Capacity, Items): the
// out-of-line growVector/shrinkVector instances of its element types (explicit specializations of
// Grow_Vector/Shrink_Vector). Element types are hypotheses.
#include "shared/wol_array_list.hpp"

// A 24-byte list element of ownrdraw.cpp (layout unknown beyond the two WideStrings).
struct UnknownListEntry_6017c0 { int unknown_00[6]; };

template<> bool WolArrayList<UnknownListEntry_6017c0>::Grow_Vector()
{
    return Grow();
}
