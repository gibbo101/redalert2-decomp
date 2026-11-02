// void WolArrayList<UnknownListEntry_6017c0>::Clear_Vector() (0x00601490): wlib clear() out of line for the
// 24-byte element list (destroys each element's two WideStrings, then empties the list).
#include "shared/wide_string.hpp"
#include "shared/wol_array_list.hpp"

// A 24-byte list element of ownrdraw.cpp: two WideStrings (0x00601490 destroys them, 0x006025A0 assigns them);
// the default constructor sets 0, -1, 0, -1 (0x006025A0's temporary). Field names are hypotheses.
struct UnknownListEntry_6017c0 {
    int unknown_00;
    WideString unknown_04;
    WideString unknown_08;
    int unknown_0c;
    int unknown_10;
    int unknown_14;
    UnknownListEntry_6017c0() { unknown_00 = 0; unknown_0c = -1; unknown_10 = 0; unknown_14 = -1; }
    // Member-wise copy, out of line (0x00601780).
    UnknownListEntry_6017c0(UnknownListEntry_6017c0 const &other);
};

template<> void WolArrayList<UnknownListEntry_6017c0>::Clear_Vector()
{
    Clear();
}
