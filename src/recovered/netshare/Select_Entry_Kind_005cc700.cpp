// void __fastcall Select_Entry_Kind_005cc700(HWND dialog, int id, int kind) (0x005CC700)
// Selects the fixed lobby entry of a kind (2 open .. 7 observer, as Entry_Kind_005c9650 numbers them) in a
// slot combo box and refreshes the slot with it.
#include "shared/lobby.hpp"

void __fastcall Select_Entry_Kind_005cc700(HWND dialog, int id, int kind)
{
    NodeNameType *entry;
    if (kind == 2) {
        entry = unknown_open_entry_a72d2c;
    } else if (kind == 3) {
        entry = unknown_closed_entry_a72d30;
    } else if (kind == 4) {
        entry = unknown_easy_ai_entry_a72d34;
    } else if (kind == 5) {
        entry = unknown_medium_ai_entry_a72d38;
    } else if (kind == 6) {
        entry = unknown_hard_ai_entry_a72d3c;
    } else {
        entry = kind == 7 ? unknown_player_a72d44 : 0;
    }
    unknown_combo_select_by_data_005c9950(dialog, id, (int)entry);
    Unknown_005cbf20(dialog, id, entry, 0);
}
