// bool TActionClass::unknown_technos_with_tag_to_house(...) (0x006B0360)
// Passes the house of type Data to TechnoClass slot 222 of every living, active techno whose tag has the action's trigger attached; true when any was handled.
#include "shared/taction.hpp"
#include "shared/techno.hpp"
#include "shared/house.hpp"
#include "shared/tag.hpp"
// @ref ?As_Pointer@HouseClass@@SIPAV1@H@Z=004ed760
// @ref ?Technos@@3V?$DynamicVectorClass@PAVTechnoClass@@@@A=00a40c20
// @ref ?Is_Trigger_Attached@TagClass@@QBE_NPAVTriggerClass@@@Z=006b3dd0

bool TActionClass::unknown_technos_with_tag_to_house(HouseClass *house, ObjectClass *object, TriggerClass *trigger, Cell *cell)
{
    bool handled = false;
    for (int index = 0; index < Technos.Count(); index++) {
        TechnoClass *techno = Technos[index];
        if (techno->unknown_7d && techno->unknown_74 && !techno->unknown_76 && techno->unknown_34 != 0
            && techno->unknown_34->Is_Trigger_Attached(trigger)) {
            techno->unknown_slot222(HouseClass::As_Pointer(Data), 0);
            handled = true;
        }
    }
    return handled;
}
