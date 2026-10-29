// void __fastcall Lock_Slots_005c9da0(HWND dialog, int slot) (0x005C9DA0)
#include "shared/lobby.hpp"
// @ref ?Unknown_005c9b90@@YIXPAUHWND__@@H_N@Z=005c9b90

void __fastcall Lock_Slots_005c9da0(HWND dialog, int slot)
{
    for (int i = 0; i < 8; i++) {
        HWND control = GetDlgItem(dialog, Slot_Control_Id_005c97a0(i));
        EnableWindow(control, FALSE);
        Unknown_005c9b90(dialog, i, 0);
    }
    HWND control = GetDlgItem(dialog, Slot_Control_Id_005c97a0(slot));
    EnableWindow(control, TRUE);
    Unknown_005c9b90(dialog, slot, 1);
}
