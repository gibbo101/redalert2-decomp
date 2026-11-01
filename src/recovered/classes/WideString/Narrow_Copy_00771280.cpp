// Wstring __fastcall Narrow_Copy_00771280(WideString const &wide) (0x00771280)
#include "shared/wide_string.hpp"
#include "shared/wstring.hpp"
// @ref _wcslen=00783605
// @ref ??2@YAPAXI@Z=00782017
// @ref ??3@YAXPAX@Z=00781d3b
// @ref ?Unknown_006FA0F0@@YIXPADPBGH@Z=006fa0f0
void __fastcall Unknown_006FA0F0(char *dst, unsigned short const *src, int limit);

Wstring __fastcall Narrow_Copy_00771280(WideString const &wide)
{
    int length = wide.Length();
    char *buffer = new char[length + 1];
    Unknown_006FA0F0(buffer, wide, length);
    Wstring narrow(buffer);
    delete buffer;
    return narrow;
}
