// bool TActionClass::unknown_player_4e82c0(...) (0x006AFD70)
// Calls HouseClass::unknown_func_4e82c0() on the player's house; always true.
#include "shared/taction.hpp"
#include "shared/house.hpp"

bool TActionClass::unknown_player_4e82c0(HouseClass *house, ObjectClass *object, TriggerClass *trigger, Cell *cell)
{
    unknown_player_a35db4->unknown_func_4e82c0();
    return true;
}
