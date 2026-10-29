// @ref __imp__GetParent@4=0079a500
// @ref __imp__SendMessageA@16=0079a4a0
#include "shared/win32_api.hpp"
#include "shared/owner_draw_dialog_control.hpp"

bool __fastcall OwnerDraw_Control_Test_005e0760(unsigned int key, HWND window);

namespace OwnerDraw {

BOOL __stdcall unknown_5e86d0(HWND window, LPARAM)
{
    HWND parent = GetParent(window);
    if (OwnerDraw_Control_Test_005e0760((unsigned int)parent, window)) {
        SendMessageA(window, 0x4ee, 0, 0);
    }
    return TRUE;
}

}
