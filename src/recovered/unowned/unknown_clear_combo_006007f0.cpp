// int __fastcall unknown_clear_combo(HWND combo) -- 0x006007F0
// Purpose: deletes every item of a combo box, last first (CB_GETCOUNT,
// CB_DELETESTRING); returns 0.
// Assumptions: name hypothesis.
#include "shared/win32_api.hpp"
// @ref __imp__SendMessageA@16=0079a4a0

int __fastcall unknown_clear_combo(HWND combo)
{
    int index = SendMessageA(combo, 0x146, 0, 0);
    while (index--) {
        SendMessageA(combo, 0x144, index, 0);
    }
    return 0;
}
