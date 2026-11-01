// void __fastcall unknown_center_on_owner_737060(HWND window) (0x00737060)
// @ref ?unknown_center_window_737080@@YIXPAUHWND__@@0@Z=00737080
#include "shared/win_util.hpp"

void __fastcall unknown_center_on_owner_737060(HWND window)
{
    HWND owner = (HWND)GetWindowLongA(window, -8);   // GWL_HWNDPARENT
    if (owner != 0) {
        unknown_center_window_737080(window, owner);
    }
}
