// bool TActionClass::unknown_player_4e80d0(...) (0x006AFD50)
// Calls HouseClass::Flag_To_Lose(true) on the player's house; always true.
#include "shared/taction.hpp"
#include "shared/house.hpp"
// @ref ?Flag_To_Lose@HouseClass@@QAE_N_N@Z=004e80d0

bool TActionClass::unknown_player_4e80d0(HouseClass *house, ObjectClass *object, TriggerClass *trigger, Cell *cell)
{
    unknown_player_a35db4->Flag_To_Lose(true);
    return true;
}
