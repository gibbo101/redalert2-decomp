// bool __fastcall Unknown_005cbdb0(HWND dialog, int count, bool unknown_1, bool unknown_2) (0x005CBDB0)
#include "shared/lobby.hpp"
// @ref ?unknown_closed_entry_a72d30@@3PAUNodeNameType@@A=00a72d30
// @ref ?unknown_easy_ai_entry_a72d34@@3PAUNodeNameType@@A=00a72d34
// @ref ?unknown_hard_ai_entry_a72d3c@@3PAUNodeNameType@@A=00a72d3c
// @ref ?unknown_medium_ai_entry_a72d38@@3PAUNodeNameType@@A=00a72d38
// @ref ?unknown_open_entry_a72d2c@@3PAUNodeNameType@@A=00a72d2c
// @ref ?unknown_waiting_entry_a72d40@@3PAUNodeNameType@@A=00a72d40

bool __fastcall Unknown_005cbdb0(HWND dialog, int count, bool unknown_1, bool unknown_2)
{
    if (unknown_lobby_flag_7e6d90 == 0) {
        count++;
    }
    for (int i = 0; i < 8; i++) {
        int id = Slot_Control_Id_005c97a0(i);
        int index = SendDlgItemMessageA(dialog, id, 0x147, 0, 0);
        int data = SendDlgItemMessageA(dialog, id, 0x150, index, 0);
        NodeNameType *entry;
        if (data == -1) {
            entry = 0;
        } else {
            entry = (NodeNameType *)data;
        }
        if (entry != 0 && (entry == unknown_easy_ai_entry_a72d34 || entry == unknown_medium_ai_entry_a72d38
                           || entry == unknown_hard_ai_entry_a72d3c)
            && unknown_session_a3d29c != 0 && !unknown_1) {
            return true;
        }
        if (i >= count) {
            bool player = entry != 0 && entry != unknown_open_entry_a72d2c && entry != unknown_closed_entry_a72d30
                && entry != unknown_player_a72d44 && entry != unknown_waiting_entry_a72d40;
            if (player && entry->unknown_66e290() != -3) {
                return true;
            }
            if (unknown_session_a3d29c != 0 && !unknown_2 && player && entry->unknown_66e290() == -3) {
                return true;
            }
        }
    }
    return false;
}
