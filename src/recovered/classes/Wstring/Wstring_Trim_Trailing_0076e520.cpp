// void Wstring::Trim_Trailing(Wstring const &characters) (0x0076E520)
// Deletes trailing characters found in `characters`.
// @ref _strncpy=007823d0
// @ref _strchr=00784130
// @ref ??_C@_00A@?$AA@=0083c55c
#include "shared/wstring.hpp"

void Wstring::Trim_Trailing(Wstring const &characters)
{
    unsigned index = Length();
    while (index-- && strchr(characters.Peek_Buffer(), Buffer[index])) {
    }
    index++;
    char const *source = "";
    if (Buffer) {
        source = Buffer;
    }
    Wstring result;
    result.Buffer = new char[index + 1];
    result.Buffer[0] = '\0';
    if (source) {
        strncpy(result.Buffer, source, index);
    }
    result.Buffer[index] = '\0';
    *this = result.Peek_Buffer();
}
