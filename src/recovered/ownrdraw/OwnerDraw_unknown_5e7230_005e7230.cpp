// @ref __imp__GetWindowLongA@8=0079a48c
// @ref ?OwnerDraw_Control_Test_005e6860@@YI_NIPAUHWND__@@@Z=005e6860
#include "shared/win32_api.hpp"
#include "shared/owner_draw_dialog_control.hpp"

namespace OwnerDraw {

bool __fastcall unknown_5e7230(unsigned int key, HWND window)
{
    if ((GetWindowLongA(window, GWL_STYLE) & BS_OWNERDRAW) != BS_OWNERDRAW) {
        return false;
    }
    UnknownControlRecord *record = unknown_registry_a73640.Find((unsigned int)window);
    if (record && record->unknown_68 == 0) {
        return ::OwnerDraw_Control_Test_005e6860(key, window);
    }
    return false;
}

}
