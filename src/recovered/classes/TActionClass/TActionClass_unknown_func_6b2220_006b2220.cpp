// bool TActionClass::unknown_func_6b2220(...) (0x006B2220)
// Sets the rules AmbientChangeStep to the float Data; always true.
#include "shared/taction.hpp"
#include "shared/rules.hpp"

bool TActionClass::unknown_func_6b2220(HouseClass *house, ObjectClass *object, TriggerClass *trigger, Cell *cell)
{
    Rules->AmbientChangeStep = DataFloat;
    return true;
}
