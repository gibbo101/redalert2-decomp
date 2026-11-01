// Wstring __fastcall Wide_To_7_Bit(WideString const &wide) (0x007715D0)
#include "shared/wide_string.hpp"
#include "shared/wstring.hpp"
#include "shared/bit_codec.hpp"
// @ref _wcslen=00783605
// @ref ??2@YAPAXI@Z=00782017
// @ref ??3@YAXPAX@Z=00781d3b
// @ref ?Bit_Expand_7@@YIHPBEPAEI@Z=00430da0

Wstring __fastcall Wide_To_7_Bit(WideString const &wide)
{
    int bits = (wide.Length() + 1) * 16;
    unsigned char *buffer = new unsigned char[(bits + 6) / 7];
    Bit_Expand_7((unsigned char const *)(unsigned short const *)wide, buffer, bits);
    Wstring encoded((char const *)buffer);
    delete buffer;
    return encoded;
}
