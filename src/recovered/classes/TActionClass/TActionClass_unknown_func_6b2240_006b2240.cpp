// bool TActionClass::unknown_func_6b2240(...) (0x006B2240)
// Sets the rules AmbientChangeRate to the float Data.Value; always true.
#include "shared/taction.hpp"
#include "shared/rules.hpp"

bool TActionClass::unknown_func_6b2240(HouseClass *house, ObjectClass *object, TriggerClass *trigger, Cell *cell)
{
    float change_rate = Data.Float;
    Rules->AmbientChangeRate = change_rate;
    return true;
}


