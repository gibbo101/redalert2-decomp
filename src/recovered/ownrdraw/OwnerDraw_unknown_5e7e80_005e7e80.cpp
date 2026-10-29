// @ref __imp__EnumChildWindows@12=0079a4dc
// @ref ?unknown_visible_count_a763b4@OwnerDraw@@3HA=00a763b4
// @ref ?unknown_5e7dd0@OwnerDraw@@YGHPAUHWND__@@J@Z=005e7dd0
#include "shared/win32_api.hpp"
#include "shared/owner_draw_dialog_control.hpp"

namespace OwnerDraw {

bool __fastcall unknown_5e7e80(HWND dialog)
{
    unknown_visible_count_a763b4 = 0;
    EnumChildWindows(dialog, unknown_5e7dd0, 0);
    return unknown_visible_count_a763b4 >= 1;
}

}
