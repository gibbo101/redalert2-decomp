// bool TActionClass::unknown_win_or_lose_6b1360(...) (0x006B1360)
// The player wins (quietly no) when its house type is Data, else loses; always true.
#include "shared/taction.hpp"
#include "shared/house.hpp"
#include "shared/house_type.hpp"

bool TActionClass::unknown_win_or_lose_6b1360(HouseClass *house, ObjectClass *object, TriggerClass *trigger, Cell *cell)
{
    if (Data == unknown_player_a35db4->Type->House) {
        unknown_player_a35db4->Flag_To_Win(false);
        return true;
    }
    unknown_player_a35db4->Flag_To_Lose(false);
    return true;
}
