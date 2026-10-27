// bool UnknownStringList_7662c0::Get(Wstring &string, int index) -- 0x007662C0
// Purpose: copies the Wstring at index of the array at +0x08 (count at
// +0x00) into string (Wstring::operator=); false when index is out of
// range. The Wstring counterpart of 0x00768260.
// Assumptions: owner unidentified (no direct callers); names are
// placeholders.
#include "shared/wstring.hpp"
// @ref ??4Wstring@@QAEAAV0@ABV0@@Z=0076dc30

class UnknownStringList_7662c0 {
public:
    bool Get(Wstring &string, int index);

    int Count;                  // +0x00
    int unknown_04;
    Wstring *Items;             // +0x08
};

bool UnknownStringList_7662c0::Get(Wstring &string, int index)
{
    if (index >= 0 && index < Count) {
        string = Items[index];
        return true;
    }
    return false;
}
