// bool TActionClass::unknown_action_006b22f0(...) (0x006B22F0)
#include "shared/taction.hpp"
#include "shared/house.hpp"
bool TActionClass::unknown_action_006b22f0(HouseClass *house, ObjectClass *object, TriggerClass *trigger, Cell *cell)
{
    if (house != 0) house->unknown_554c = Data.Value;
    return true;
}


