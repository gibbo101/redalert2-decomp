// bool TActionClass::unknown_action_006b0540(...) (0x006B0540)
#include "shared/taction.hpp"
#include "shared/house.hpp"
bool TActionClass::unknown_action_006b0540(HouseClass *house, ObjectClass *object, TriggerClass *trigger, Cell *cell)
{
    if (house != 0) house->unknown_541c = Data.Value;
    return true;
}


