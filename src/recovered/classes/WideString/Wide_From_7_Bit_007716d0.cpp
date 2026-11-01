// WideString __fastcall Wide_From_7_Bit(Wstring const &string) (0x007716D0)
#include "shared/wide_string.hpp"
#include "shared/wstring.hpp"
#include "shared/bit_codec.hpp"
// @ref _wcslen=00783605
// @ref _wcscpy=00783689
// @ref ??2@YAPAXI@Z=00782017
// @ref ??3@YAXPAX@Z=00781d3b
// @ref ??_C@_00A@?$AA@=0083c55c
// @ref ?Bit_Compress_7_String@@YIIPBEPAGI@Z=00430f30

WideString __fastcall Wide_From_7_Bit(Wstring const &string)
{
    int bytes = (string.Length() + 1) * 7 / 8;
    int count = (bytes + 1) / 2;
    unsigned short *buffer = new unsigned short[count + 1];
    Bit_Compress_7_String((unsigned char const *)((string.Buffer == 0) ? "" : string.Buffer), buffer, count);
    WideString decoded(buffer);
    delete buffer;
    return decoded;
}
