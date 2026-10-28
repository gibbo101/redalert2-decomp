// int __fastcall Skirmish_Player_Combo_ID(int index) (0x006827F0)
// The player-type combo box of player index + 1, or -1.
#include "shared/skirmish.hpp"

int __fastcall Skirmish_Player_Combo_ID(int index)
{
    if (index == 0) {
        return 0x50B;
    }
    if (index == 1) {
        return 0x50E;
    }
    if (index == 2) {
        return 0x516;
    }
    if (index == 3) {
        return 0x51A;
    }
    if (index == 4) {
        return 0x51B;
    }
    if (index == 5) {
        return 0x51C;
    }
    return index == 6 ? 0x51D : -1;
}
