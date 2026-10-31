// void __fastcall Unknown_005cb3f0(HWND dialog, int first, int count) (0x005CB3F0)
#include "shared/lobby.hpp"
// @ref ?Unknown_005bbdc0@@YIXXZ=005bbdc0
// @ref ?Unknown_005cae00@@YIXPAUHWND__@@HH@Z=005cae00
// @ref ?Unknown_005cbf20@@YIXPAUHWND__@@HPAUNodeNameType@@H@Z=005cbf20
// @ref ?unknown_closed_entry_a72d30@@3PAUNodeNameType@@A=00a72d30
// @ref ?unknown_open_entry_a72d2c@@3PAUNodeNameType@@A=00a72d2c
// @ref ?unknown_waiting_entry_a72d40@@3PAUNodeNameType@@A=00a72d40

void __fastcall Unknown_005cb3f0(HWND dialog, int first, int count)
{
    int end = first + count;
    int limit = Lobby_Slot_Limit_005c6520();
    for (int i = first; i < end; i++) {
        int id = Slot_Control_Id_005c97a0(i);
        int index = SendDlgItemMessageA(dialog, id, 0x147, 0, 0);
        NodeNameType *entry = (NodeNameType *)SendDlgItemMessageA(dialog, id, 0x150, index, 0);
        if (entry != (NodeNameType *)-1 && Is_Seated_Entry(entry)) {
            Unknown_005cbf20(dialog, id, entry, 0);
        } else if (i != unknown_lobby_flag_7e6d90) {
            if (i < limit) {
                Unknown_005cbf20(dialog, id, unknown_open_entry_a72d2c, 0);
            } else {
                Unknown_005cbf20(dialog, id, unknown_closed_entry_a72d30, 0);
            }
        }
    }
    Unknown_005cae00(dialog, first, count);
    Unknown_005bbdc0();
    Unknown_005c3810(true, false);
}
