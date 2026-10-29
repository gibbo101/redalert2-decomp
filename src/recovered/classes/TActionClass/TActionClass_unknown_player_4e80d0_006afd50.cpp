// bool TActionClass::unknown_player_4e80d0(...) (0x006AFD50)
// Calls HouseClass::unknown_func_4e80d0(1) on the player's house; always true.
#include "shared/taction.hpp"
#include "shared/house.hpp"
// @ref ?unknown_func_4e80d0@HouseClass@@QAEXH@Z=004e80d0

bool TActionClass::unknown_player_4e80d0(HouseClass *house, ObjectClass *object, TriggerClass *trigger, Cell *cell)
{
    unknown_player_a35db4->unknown_func_4e80d0(1);
    return true;
}
