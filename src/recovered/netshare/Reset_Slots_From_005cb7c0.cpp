// void __fastcall Reset_Slots_From_005cb7c0(HWND dialog, int first) (0x005CB7C0)
#include "shared/lobby.hpp"
#include "shared/multiplayer_game_mode.hpp"
// @ref ?Unknown_005cbf20@@YIXPAUHWND__@@HPAUNodeNameType@@H@Z=005cbf20
// @ref ?Unknown_005bbdc0@@YIXXZ=005bbdc0
// @ref ?Unknown_005c3810@@YIX_N0@Z=005c3810
// @ref ?unknown_chat_a72cfc@@3PAUIChat@WOL@@A=00a72cfc
// @ref ?unknown_closed_entry_a72d30@@3PAUNodeNameType@@A=00a72d30
// @ref ?unknown_open_entry_a72d2c@@3PAUNodeNameType@@A=00a72d2c

void __fastcall Reset_Slots_From_005cb7c0(HWND dialog, int first)
{
    int limit = Lobby_Slot_Limit_005c6520();
    for (int i = first; i < 8; i++) {
        int id = Slot_Control_Id_005c97a0(i);
        if (i < limit) {
            if (i != unknown_lobby_flag_7e6d90) {
                Unknown_005cbf20(dialog, id, unknown_open_entry_a72d2c, 1);
            }
        } else if (i != unknown_lobby_flag_7e6d90) {
            Unknown_005cbf20(dialog, id, unknown_closed_entry_a72d30, 1);
        }
    }
    Unknown_005cb170(dialog, first);
    if (unknown_chat_a72cfc != 0) {
        unknown_call_73fee0_default();
    } else {
        Unknown_005bbdc0();
    }
    Unknown_005c3810(true, false);
}
