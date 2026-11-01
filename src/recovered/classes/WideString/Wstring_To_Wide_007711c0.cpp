// WideString __fastcall Wstring_To_Wide(Wstring const &string) (0x007711C0)
// The wide copy of a narrow string: the text is widened into a scratch buffer
// (0x006FA0C0), copied into the result and the buffer freed.
#include "shared/wide_string.hpp"
#include "shared/wstring.hpp"
// @ref _wcslen=00783605
// @ref _wcscpy=00783689
// @ref ??2@YAPAXI@Z=00782017
// @ref ??3@YAXPAX@Z=00781d3b
// @ref ??_C@_00A@?$AA@=0083c55c
// @ref ?Unknown_006FA0C0@@YIXPAGPBDH@Z=006fa0c0
// The same function and mangled name as shared/campaign.hpp (wchar_t there is unsigned short); this unit does not include it.
void __fastcall Unknown_006FA0C0(unsigned short *buffer, char const *text, int length);

WideString __fastcall Wstring_To_Wide(Wstring const &string)
{
    int length = (string.Buffer == 0) ? 0 : strlen(string.Buffer);
    unsigned short *buffer = new unsigned short[length + 1];
    Unknown_006FA0C0(buffer, (string.Buffer == 0) ? "" : string.Buffer, length);
    WideString wide(buffer);
    delete buffer;
    return wide;
}
