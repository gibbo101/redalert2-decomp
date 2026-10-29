// int __fastcall Assign_Slot_005c9170(NodeNameType *entry) (0x005C9170)
#include "shared/lobby.hpp"
// @ref ?unknown_open_entry_a72d2c@@3PAUNodeNameType@@A=00a72d2c

int __fastcall Assign_Slot_005c9170(NodeNameType *entry)
{
    for (int i = 0; i < 8; i++) {
        if ((unknown_player_slots_a3fa98[i] == unknown_open_entry_a72d2c && entry->Team != -1)
            || (unknown_player_slots_a3fa98[i] == unknown_player_a72d44 && entry->Team == -1)) {
            unknown_player_slots_a3fa98[i] = entry;
            return i;
        }
    }
    return -1;
}
