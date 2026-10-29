// void __fastcall Refresh_Slots_005c9cf0(HWND dialog, int slot) (0x005C9CF0)
#include "shared/lobby.hpp"
// @ref ?Unknown_005c9b90@@YIXPAUHWND__@@H_N@Z=005c9b90

void __fastcall Refresh_Slots_005c9cf0(HWND dialog, int slot)
{
    for (int i = 0; i < 8; i++) {
        HWND control = GetDlgItem(dialog, Slot_Control_Id_005c97a0(i));
        EnableWindow(control, TRUE);
        Unknown_005c9b90(dialog, i, 0);
    }
    Unknown_005c9b90(dialog, slot, 1);
}
