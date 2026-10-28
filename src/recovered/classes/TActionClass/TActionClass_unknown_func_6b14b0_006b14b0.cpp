// bool TActionClass::unknown_func_6b14b0(...) (0x006B14B0)
// Sends every unit of the house of type Data to hunt (IHouse::All_To_Hunt); always true.
#include "shared/taction.hpp"
#include "shared/house.hpp"

bool TActionClass::unknown_func_6b14b0(HouseClass *house, ObjectClass *object, TriggerClass *trigger, Cell *cell)
{
    HouseClass::As_Pointer(Data)->All_To_Hunt();
    return true;
}
