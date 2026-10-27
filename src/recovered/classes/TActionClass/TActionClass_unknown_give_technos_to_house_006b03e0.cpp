// bool TActionClass::unknown_give_technos_to_house(...) (0x006B03E0)
// Passes the house of type Data to TechnoClass slot 222 of every techno owned by the action's house; true when any was handled.
#include "shared/taction.hpp"
#include "shared/techno.hpp"
#include "shared/house.hpp"
// @ref ?As_Pointer@HouseClass@@SIPAV1@H@Z=004ed760
// @ref ?Technos@@3V?$DynamicVectorClass@PAVTechnoClass@@@@A=00a40c20

bool TActionClass::unknown_give_technos_to_house(HouseClass *house, ObjectClass *object, TriggerClass *trigger, Cell *cell)
{
    bool handled = false;
    HouseClass *new_house = HouseClass::As_Pointer(Data);
    for (int index = 0; index < Technos.Count(); index++) {
        TechnoClass *techno = Technos[index];
        if (techno->House == house) {
            techno->unknown_slot222(new_house, 0);
            handled = true;
        }
    }
    return handled;
}
