// void __fastcall unknown_context_help_7368a0(HWND window) (0x007368A0)
// @ref ??_C@_07FMM@SUN?4HLP?$AA@=007fd094
#include "shared/win_util.hpp"

void __fastcall unknown_context_help_7368a0(HWND window)
{
    DWORD ids[4] = {0, 0, 0, 0};
    ids[0] = GetWindowLongA(window, -12);           // GWL_ID
    ids[1] = GetWindowContextHelpId(window);
    WinHelpA(window, "SUN.HLP", 0x0A, (DWORD)ids);   // HELP_CONTEXTMENU
}
