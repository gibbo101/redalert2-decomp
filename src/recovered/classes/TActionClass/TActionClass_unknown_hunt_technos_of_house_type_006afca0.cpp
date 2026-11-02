// bool TActionClass::unknown_hunt_technos_of_house_type(...) (0x006AFCA0)
// Sends every living, active techno whose +0x1AC equals Data.Value and that is idle or on mission 23 to mission 5; always true.
#include "shared/taction.hpp"
#include "shared/techno.hpp"
// @ref ?Technos@@3V?$DynamicVectorClass@PAVTechnoClass@@@@A=00a40c20

bool TActionClass::unknown_hunt_technos_of_house_type(HouseClass *house, ObjectClass *object, TriggerClass *trigger, Cell *cell)
{
    for (int index = 0; index < Technos.Count(); index++) {
        TechnoClass *techno = Technos[index];
        if (techno->unknown_1ac == Data.Value && (techno->unknown_slot91() == 0 || techno->unknown_slot91() == 0x17)
            && techno->Strength > 0 && techno->unknown_7d && techno->unknown_74 && !techno->unknown_76) {
            techno->unknown_slot116(5, false);
        }
    }
    return true;
}


