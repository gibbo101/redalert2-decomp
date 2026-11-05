// @ref ?Remove@UnknownControlIndex@OwnerDraw@@QAE_NABIAAUUnknownControlRecord@2@@Z=00601c50
// @ref ?Unknown_Remove_Modeless_Dialog_00522b80@@YIXPAUHWND__@@@Z=00522b80
// @ref ?unknown_window_table_a73400@@3V?$WolDictionary@PAUHWND__@@P6GJPAU1@IIJ@Z@@A=00a73400
// @ref ?Shrink_Table@?$WolDictionary@PAUHWND__@@P6GJPAU1@IIJ@Z@@QAEXXZ=00602730
#include "shared/win32_api.hpp"
#include "shared/wide_string.hpp"
#include "shared/wol_dictionary.hpp"
#include "shared/owner_draw_dialog_control.hpp"

namespace OwnerDraw {

// EnumChildWindows callback of 0x005EDB20 (TibSun ODRemoveFromDict): drops one window from the registries.
BOOL __stdcall unknown_restore_child_5edd30(HWND window, LPARAM lparam)
{
    unknown_window_procs_a73688.Remove(window);
    unknown_registry_a73640.Remove((unsigned int const &)window);
    unknown_window_table_a73400.Remove(window);
    void *data = (void *)GetWindowLongA(window, -21);
    if (data != 0) {
        operator delete(data);
    }
    SetWindowLongA(window, -21, 0);
    Unknown_Remove_Modeless_Dialog_00522b80(window);
    return 1;
}

}
