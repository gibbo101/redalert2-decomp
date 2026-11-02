// bool TActionClass::unknown_func_6b22b0(...) (0x006B22B0)
// Clears +0x13A of the house of type Data.Value (none for -1); always true.
#include "shared/taction.hpp"
#include "shared/house.hpp"

bool TActionClass::unknown_func_6b22b0(HouseClass *house, ObjectClass *object, TriggerClass *trigger, Cell *cell)
{
    if (Data.Value != -1) {
        HouseClass::As_Pointer(Data.Value)->unknown_13a = false;
    }
    return true;
}


