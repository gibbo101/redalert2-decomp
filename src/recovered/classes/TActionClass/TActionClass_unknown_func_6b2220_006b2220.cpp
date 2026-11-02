// bool TActionClass::unknown_func_6b2220(...) (0x006B2220)
// Sets the rules AmbientChangeStep to the float Data.Value; always true.
#include "shared/taction.hpp"
#include "shared/rules.hpp"

bool TActionClass::unknown_func_6b2220(HouseClass *house, ObjectClass *object, TriggerClass *trigger, Cell *cell)
{
    float change_step = Data.Float;
    Rules->AmbientChangeStep = change_step;
    return true;
}


