// bool TActionClass::unknown_action_006b2350(...) (0x006B2350)
#include "shared/taction.hpp"
#include "shared/house.hpp"
bool TActionClass::unknown_action_006b2350(HouseClass *house, ObjectClass *object, TriggerClass *trigger, Cell *cell)
{
    if (house != 0) house->unknown_5558 = Data.Value;
    return true;
}


