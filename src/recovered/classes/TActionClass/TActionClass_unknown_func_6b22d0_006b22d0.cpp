// bool TActionClass::unknown_func_6b22d0(...) (0x006B22D0)
// Every techno of the house of type Data.Value (none for -1) cheers; always true.
#include "shared/taction.hpp"
#include "shared/house.hpp"

bool TActionClass::unknown_func_6b22d0(HouseClass *house, ObjectClass *object, TriggerClass *trigger, Cell *cell)
{
    if (Data.Value != -1) {
        HouseClass::As_Pointer(Data.Value)->Cheer();
    }
    return true;
}


