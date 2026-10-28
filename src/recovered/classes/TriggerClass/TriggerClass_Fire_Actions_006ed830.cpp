// bool TriggerClass::Fire_Actions(ObjectClass *object, Cell cell) (0x006ED830)
// Unless disabled or already sprung, performs every action of the type in the type's house;
// true when any of them acted.
#include "shared/trigger.hpp"
#include "shared/house.hpp"
#include "shared/taction.hpp"
// @ref ?Execute@TActionClass@@QAE_NPAVHouseClass@@PAVObjectClass@@PAVTriggerClass@@PAVCell@@@Z=006adae0

bool TriggerClass::Fire_Actions(ObjectClass *object, Cell cell)
{
    if (!IsEnabled || unknown_2c) {
        return false;
    }
    bool acted = false;
    for (TActionClass *action = Class->Actions; action != 0; action = action->Next) {
        if (action->Execute(HouseClass::As_Pointer(Class->unknown_a4->ArrayIndex), object, this, &cell)) {
            acted = true;
        }
    }
    return acted;
}
