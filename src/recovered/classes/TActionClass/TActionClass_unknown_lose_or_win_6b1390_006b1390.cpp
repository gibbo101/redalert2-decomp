// bool TActionClass::unknown_lose_or_win_6b1390(...) (0x006B1390)
// The player loses when its house type is Data, else wins; always true.
#include "shared/taction.hpp"
#include "shared/house.hpp"
#include "shared/house_type.hpp"

bool TActionClass::unknown_lose_or_win_6b1390(HouseClass *house, ObjectClass *object, TriggerClass *trigger, Cell *cell)
{
    if (Data != unknown_player_a35db4->Type->House) {
        unknown_player_a35db4->Flag_To_Win(false);
        return true;
    }
    unknown_player_a35db4->Flag_To_Lose(false);
    return true;
}
