// bool No_Observer_Slot_005c9490() (0x005C9490)
#include "shared/lobby.hpp"

bool No_Observer_Slot_005c9490()
{
    for (int i = 0; i < 8; i++) {
        if (unknown_player_slots_a3fa98[i] == unknown_player_a72d44) {
            return false;
        }
    }
    return true;
}
