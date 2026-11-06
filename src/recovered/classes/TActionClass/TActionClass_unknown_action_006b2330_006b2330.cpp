// bool TActionClass::unknown_action_006b2330(...) (0x006B2330)
#include "shared/taction.hpp"
#include "shared/house.hpp"
bool TActionClass::unknown_action_006b2330(HouseClass *house, ObjectClass *object, TriggerClass *trigger, Cell *cell)
{
    if (house != 0) house->unknown_5554 = Data.Value;
    return true;
}


