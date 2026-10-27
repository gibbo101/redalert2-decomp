// bool TActionClass::unknown_set_house_198(...) (0x006B13E0)
// Sets HouseClass +0x198 of the house of type Data to 4; always true.
#include "shared/taction.hpp"
#include "shared/house.hpp"
// @ref ?As_Pointer@HouseClass@@SIPAV1@H@Z=004ed760

bool TActionClass::unknown_set_house_198(HouseClass *house, ObjectClass *object, TriggerClass *trigger, Cell *cell)
{
    if (Data != -1) {
        HouseClass::As_Pointer(Data)->unknown_198 = 4;
    }
    return true;
}
