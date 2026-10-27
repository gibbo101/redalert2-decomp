// void InfantryClass::unknown_slot220(AbstractClass *target) (0x00502470, slot 220)
// A new target while alive clears +0x57D and replays the idle sequence
// (28 deploying, 2 prone, else 0). Unless deploying without DeployFire:
// clears +0x4D0, TechnoClass's slot 220, and Infiltrate infantry without
// +0x494 aimed at a building whose type allows it (+0x1216 for non-Agents,
// +0x1219 for Agents) call slot 260 (target, 1); clears +0x57E.
#include "shared/building_type.hpp"
#include "shared/infantry.hpp"
// @ref ?unknown_slot220@TechnoClass@@UAEXPAVAbstractClass@@@Z=006c9af0

void InfantryClass::unknown_slot220(AbstractClass *target)
{
    if (target != unknown_228 && Strength > 0) {
        unknown_57d = false;
        if (unknown_5090d0()) {
            unknown_slot311(28, 0, 0);
        } else if (unknown_5c3) {
            unknown_slot311(2, 0, 0);
        } else {
            unknown_slot311(0, 0, 0);
        }
    }
    if (!unknown_5090d0() || Type->DeployFire) {
        unknown_4d0 = -1;
        TechnoClass::unknown_slot220(target);
        if (unknown_494 == 0 && Type->Infiltrate) {
            AbstractClass *object = target;
            BuildingClass *building = (object != 0 && object->Kind_Of() == 6) ? (BuildingClass *)object : 0;
            if (!Type->Agent && building != 0 && building->Type->Capturable) {
                unknown_slot260(object, 1);
            } else if (Type->Agent && building != 0 && building->Type->Spyable) {
                unknown_slot260(object, 1);
            }
        }
        unknown_57e = false;
    }
}
