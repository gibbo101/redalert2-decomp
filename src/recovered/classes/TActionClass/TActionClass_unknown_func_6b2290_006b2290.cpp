// bool TActionClass::unknown_func_6b2290(...) (0x006B2290)
// Sets +0x13A of the house of type Data (none for -1); always true.
#include "shared/taction.hpp"
#include "shared/house.hpp"

bool TActionClass::unknown_func_6b2290(HouseClass *house, ObjectClass *object, TriggerClass *trigger, Cell *cell)
{
    if (Data != -1) {
        HouseClass::As_Pointer(Data)->unknown_13a = true;
    }
    return true;
}
