// int __fastcall Find_Slot_By_Name_005c8c30(wchar_t const *name) (0x005C8C30)
#include "shared/lobby.hpp"
#include "shared/ipx_manager.hpp"

int __fastcall Find_Slot_By_Name_005c8c30(wchar_t const *name)
{
    for (int i = 0; i < 8; i++) {
        if (unknown_player_slots_a3fa98[i] != 0 && _wcsicmp(name, unknown_player_slots_a3fa98[i]->Name) == 0) {
            return i;
        }
    }
    return -1;
}
