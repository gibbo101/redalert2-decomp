// void __fastcall Change_Slot_Count_005cb300(HWND dialog, int old_count, int new_count, UnknownSessionA3D29C *mode) (0x005CB300)
#include "shared/lobby.hpp"
#include "shared/multiplayer_game_mode.hpp"
// @ref ?Unknown_005cae00@@YIXPAUHWND__@@HH@Z=005cae00
// @ref ?Unknown_005cafd0@@YIXPAUHWND__@@@Z=005cafd0

void __fastcall Change_Slot_Count_005cb300(HWND dialog, int old_count, int new_count, UnknownSessionA3D29C *mode)
{
    if (unknown_session_a3d29c != 0 && !unknown_session_a3d29c->unknown_slot12() && !unknown_73c370()) {
        int limit = Lobby_Slot_Limit_005c6520();
        if (old_count > limit) {
            old_count = limit;
        }
    }
    if ((mode != 0 && !mode->unknown_slot12()) || unknown_73c370()) {
        int limit = Lobby_Slot_Limit_005c6520();
        if (new_count > limit) {
            new_count = limit;
        }
    }
    int added = new_count - old_count;
    if (added > 0) {
        Unknown_005cae00(dialog, old_count, added);
        Unknown_005cafd0(dialog);
    } else {
        if (added < 0) {
            Unknown_005cb170(dialog, new_count);
        }
        Unknown_005cafd0(dialog);
    }
}
