// @ref __imp__GetParent@4=0079a500
// @ref __imp__IsWindowVisible@4=0079a4d8
// @ref ?unknown_visible_count_a737e4@OwnerDraw@@3HA=00a737e4
#include "shared/win32_api.hpp"
#include "shared/owner_draw_dialog_control.hpp"

namespace OwnerDraw {

BOOL __stdcall unknown_5e7d00(HWND window, LPARAM)
{
    HWND parent = GetParent(window);
    if (unknown_5e7230((unsigned int)parent, window) && IsWindowVisible(window)) {
        unknown_visible_count_a737e4++;
    }
    return TRUE;
}

}
