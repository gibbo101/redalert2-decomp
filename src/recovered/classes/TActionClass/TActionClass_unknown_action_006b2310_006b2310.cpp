// bool TActionClass::unknown_action_006b2310(...) (0x006B2310)
#include "shared/taction.hpp"
#include "shared/house.hpp"
bool TActionClass::unknown_action_006b2310(HouseClass *house, ObjectClass *object, TriggerClass *trigger, Cell *cell)
{
    if (house != 0) house->unknown_5550 = Data.Value;
    return true;
}


