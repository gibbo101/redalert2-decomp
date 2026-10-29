// int Find_First_Player_Slot_005c8c70() (0x005C8C70)
#include "shared/lobby.hpp"

int Find_First_Player_Slot_005c8c70()
{
    if (unknown_players_a3fa7c.Count() == 0) {
        return -1;
    }
    return Find_Slot_By_Name_005c8c30(unknown_players_a3fa7c[0]->Name);
}
