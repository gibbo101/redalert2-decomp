// bool TActionClass::unknown_func_6b2240(...) (0x006B2240)
// Sets the rules AmbientChangeRate to the float Data; always true.
#include "shared/taction.hpp"
#include "shared/rules.hpp"

bool TActionClass::unknown_func_6b2240(HouseClass *house, ObjectClass *object, TriggerClass *trigger, Cell *cell)
{
    Rules->AmbientChangeRate = DataFloat;
    return true;
}
