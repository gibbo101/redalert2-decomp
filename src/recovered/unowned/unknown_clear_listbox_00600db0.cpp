// int __fastcall unknown_clear_listbox(HWND listbox) -- 0x00600DB0
// Purpose: deletes every item of a list box, last first (LB_GETCOUNT,
// LB_DELETESTRING); returns 0.
// Assumptions: name hypothesis (the combo-box twin is 0x006007F0).
#include "shared/win32_api.hpp"
// @ref __imp__SendMessageA@16=0079a4a0

int __fastcall unknown_clear_listbox(HWND listbox)
{
    int index = SendMessageA(listbox, 0x18B, 0, 0);
    while (index--) {
        SendMessageA(listbox, 0x182, index, 0);
    }
    return 0;
}
