// int __fastcall Is_Accepted_Slot_005ca3b0(int slot) (0x005CA3B0)
#include "shared/lobby.hpp"

int __fastcall Is_Accepted_Slot_005ca3b0(int slot)
{
    NodeNameType *entry = unknown_player_slots_a3fa98[slot];
    int accepted = 0;
    if ((entry != 0 && (entry == unknown_easy_ai_entry_a72d34 || entry == unknown_medium_ai_entry_a72d38
                        || entry == unknown_hard_ai_entry_a72d3c))
        || entry->unknown_67 == 1) {
        accepted = 1;
    }
    return accepted;
}
