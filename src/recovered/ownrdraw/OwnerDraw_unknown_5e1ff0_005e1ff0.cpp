// @ref __imp__SendMessageA@16=0079a4a0
#include "shared/win32_api.hpp"
#include "shared/owner_draw_dialog_control.hpp"

namespace OwnerDraw {

// Whether the control answers message 0x4E7 (0x005E1FF0).
bool __fastcall unknown_5e1ff0(HWND window)
{
    return SendMessageA(window, 0x4e7, 0, 0) ? true : false;
}

}
