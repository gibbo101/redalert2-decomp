// void Wstring::Trim_Leading(Wstring const &characters) (0x0076E4C0)
// Deletes leading characters found in `characters`.
// @ref _strchr=00784130
// @ref ??_C@_00A@?$AA@=0083c55c
#include "shared/wstring.hpp"

void Wstring::Trim_Leading(Wstring const &characters)
{
    int count = 0;
    while (count < (int)Length() && strchr(characters.Get(), Buffer[count])) {
        count++;
    }
    if (count > 0) {
        Remove(0, count);
    }
}
