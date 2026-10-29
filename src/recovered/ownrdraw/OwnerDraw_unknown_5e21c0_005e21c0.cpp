// @ref __imp__SendMessageA@16=0079a4a0
#include "shared/win32_api.hpp"
#include "shared/owner_draw_dialog_control.hpp"

namespace OwnerDraw {

WideString __fastcall unknown_5e21c0(HWND window, HWND item, int x, int y)
{
    int index = SendMessageA(item, 0x4e8, 0, (unsigned short)x | ((unsigned long)(unsigned short)y << 16));
    WideString text = unknown_5e2100(window, (int)item, index);
    return text;
}

}
