// bool TActionClass::unknown_player_4e7ee0(...) (0x006AFD30)
// Calls HouseClass::Flag_To_Win(true) on the player's house; always true.
#include "shared/taction.hpp"
#include "shared/house.hpp"

bool TActionClass::unknown_player_4e7ee0(HouseClass *house, ObjectClass *object, TriggerClass *trigger, Cell *cell)
{
    unknown_player_a35db4->Flag_To_Win(true);
    return true;
}
