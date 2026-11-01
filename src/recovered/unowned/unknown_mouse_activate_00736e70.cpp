// void __fastcall unknown_mouse_activate_736e70(HWND window, short active) (0x00736E70)
#include "shared/win_util.hpp"
#include "shared/mouse.hpp"

void __fastcall unknown_mouse_activate_736e70(HWND window, short active)
{
    if (WWMouse != 0) {
        if (active == 0) {
            WWMouse->Capture_Mouse();
            return;
        }
        WWMouse->Release_Mouse();
        RedrawWindow(window, 0, 0, 0x587);
    }
}
