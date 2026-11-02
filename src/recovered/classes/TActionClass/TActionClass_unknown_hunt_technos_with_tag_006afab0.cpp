// bool TActionClass::unknown_hunt_technos_with_tag(...) (0x006AFAB0)
// Sends every living, active non-building techno that has the action's trigger attached through its tag and is idle or on mission 23 to mission 5; always true.
#include "shared/building.hpp"   // first: the unit also sees the full BuildingClass
#include "shared/taction.hpp"
#include "shared/techno.hpp"
#include "shared/tag.hpp"
// @ref ?Technos@@3V?$DynamicVectorClass@PAVTechnoClass@@@@A=00a40c20
// @ref ?Is_Trigger_Attached@TagClass@@QBE_NPAVTriggerClass@@@Z=006b3dd0

bool TActionClass::unknown_hunt_technos_with_tag(HouseClass *house, ObjectClass *object, TriggerClass *trigger, Cell *cell)
{
    for (int index = 0; index < Technos.Count(); index++) {
        TechnoClass *techno = Technos[index];
        if (techno->Kind_Of() != 6 && techno->unknown_7d && techno->unknown_74 && techno->unknown_34 != 0
            && techno->unknown_34->Is_Trigger_Attached(trigger)) {
            if (techno->unknown_slot91() == 0 || techno->unknown_slot91() == 0x17) {
                techno->unknown_slot116(5, false);
            }
        }
    }
    return true;
}


