// void InfantryClass::unknown_slot255(TechnoClass *techno) (0x005092B0, slot 255)
// Disguises as another infantry: TechnoClass's slot 255, then copies its
// disguise when it is disguised itself, else its type and house.
#include "shared/infantry.hpp"
// @ref ?unknown_slot255@TechnoClass@@UAEXPAV1@@Z=006d8680

void InfantryClass::unknown_slot255(TechnoClass *techno)
{
    if (techno != 0 && techno->Kind_Of() == 15) {
        TechnoClass::unknown_slot255(techno);
        if (techno->unknown_slot48()) {
            unknown_40c = techno->unknown_slot50(true);
            unknown_410 = techno->unknown_slot51(true);
        } else {
            unknown_40c = techno->Class_Of();
            unknown_410 = techno->Owning_House();
        }
    }
}
