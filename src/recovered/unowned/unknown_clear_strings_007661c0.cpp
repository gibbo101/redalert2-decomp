// void UnknownStringList_007661C0::unknown_clear() -- 0x007661C0
// Purpose: destroys the Count (+0x00) strings of the array at +0x08 and
// sets Count to 0 (the storage is kept).
// Assumptions: owner unidentified; +0x04 is not touched.
#include "shared/wstring.hpp"

struct UnknownStringList_007661c0 {
    int Count;                              // +0x00
    int unknown_04;
    Wstring *Items;                         // +0x08
    void unknown_clear();
};

void UnknownStringList_007661c0::unknown_clear()
{
    for (int index = 0; index < Count; index++) {
        Items[index].~Wstring();
    }
    Count = 0;
}
