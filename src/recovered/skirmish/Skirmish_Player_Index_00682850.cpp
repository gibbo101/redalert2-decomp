// int __fastcall Skirmish_Player_Index(int id) (0x00682850)
// The index (player - 1) of a player-type combo box, or -1.
#include "shared/skirmish.hpp"

int __fastcall Skirmish_Player_Index(int id)
{
    if (id == 0x50B) {
        return 0;
    }
    if (id == 0x50E) {
        return 1;
    }
    if (id == 0x516) {
        return 2;
    }
    if (id == 0x51A) {
        return 3;
    }
    if (id == 0x51B) {
        return 4;
    }
    if (id == 0x51C) {
        return 5;
    }
    return id == 0x51D ? 6 : -1;
}
