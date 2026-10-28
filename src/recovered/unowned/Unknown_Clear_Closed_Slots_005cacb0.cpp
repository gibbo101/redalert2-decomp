// bool __fastcall Unknown_Clear_Closed_Slots_005cacb0(HWND dialog) (0x005CACB0)
// Walks the eight player slots' combo boxes (controls 0x411..0x418): a slot whose
// selected item data is the third, fourth or fifth fixed entry is reset to the
// first fixed entry within the slot limit (2, 4 or 8 by game mode) or to the second
// beyond it, with its three setting tables cleared. Answers whether any changed.
#include "shared/lobby.hpp"
#include "shared/win32_api.hpp"
// @ref __imp__SendDlgItemMessageA@20=0079a484
// @ref ?unknown_lobby_entries_a72d2c@@3PAPAUNodeNameType@@A=00a72d2c
// @ref ?unknown_player_slots_a3fa98@@3PAPAUNodeNameType@@A=00a3fa98
// @ref ?unknown_lobby_a3d2dc@@3PAHA=00a3d2dc
// @ref ?unknown_lobby_a3d2fc@@3PAHA=00a3d2fc
// @ref ?unknown_lobby_a3d31c@@3PAHA=00a3d31c
// @ref ?Unknown_005c9b90@@YIXPAUHWND__@@HH@Z=005c9b90
// @ref ?unknown_game_mode_a3d298@@3HA=00a3d298
// @ref ?unknown_73c370@@YA_NXZ=0073c370
// @ref ?unknown_73c3a0@@YA_NXZ=0073c3a0

bool __fastcall Unknown_Clear_Closed_Slots_005cacb0(HWND dialog)
{
    bool changed = false;
    int limit;
    if (unknown_game_mode_a3d298 == 4) {
        if (unknown_73c370() && !unknown_73c3a0()) {
            limit = 2;
        } else {
            limit = 4;
        }
    } else {
        limit = 8;
    }
    for (int i = 0; i < 8; i++) {
        int id;
        if (i == 0) {
            id = 0x411;
        } else if (i == 1) {
            id = 0x412;
        } else if (i == 2) {
            id = 0x413;
        } else if (i == 3) {
            id = 0x414;
        } else if (i == 4) {
            id = 0x415;
        } else if (i == 5) {
            id = 0x416;
        } else if (i == 6) {
            id = 0x417;
        } else {
            id = i == 7 ? 0x418 : -1;
        }
        WPARAM selected = SendDlgItemMessageA(dialog, id, 0x147, 0, 0);
        LRESULT data = SendDlgItemMessageA(dialog, id, 0x150, selected, 0);
        if (data != 0 && (data == (LRESULT)unknown_lobby_entries_a72d2c[2] ||
                          data == (LRESULT)unknown_lobby_entries_a72d2c[3] ||
                          data == (LRESULT)unknown_lobby_entries_a72d2c[4])) {
            if (i < limit) {
                unknown_player_slots_a3fa98[i] = unknown_lobby_entries_a72d2c[0];
            } else {
                unknown_player_slots_a3fa98[i] = unknown_lobby_entries_a72d2c[1];
            }
            Unknown_005c9b90(dialog, i, 0);
            unknown_lobby_a3d2dc[i] = -1;
            unknown_lobby_a3d2fc[i] = -1;
            unknown_lobby_a3d31c[i] = -1;
            changed = true;
        }
    }
    return changed;
}
