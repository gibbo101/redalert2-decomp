// void InfantryClass::unknown_5094b0(BuildingClass *building) (0x005094B0;
// no callers in the executable: InfantryClass slot 93 expands the same steps
// inline for an infantry arriving in the building's cell)
// An Occupier leaves the map (slot 52), joins the building's occupants
// (+0x554) and the building refreshes its cell; an Assaulter is handed to the
// building (0x004536D0), stops (slot 260) and moves to the building's centre.
#include "shared/foot.hpp"
#include "shared/infantry.hpp"
// @ref ?Unknown_004536D0@BuildingClass@@QAEXPAVInfantryClass@@@Z=004536d0
// @ref ?Unknown_006D9610@TechnoClass@@QAEXPAVAbstractClass@@@Z=006d9610

void InfantryClass::unknown_5094b0(BuildingClass *building)
{
    if (Type->Occupier) {
        unknown_slot52();
        building->unknown_554.Add(this);
        building->Unknown_006D9610(building->unknown_slot105());
        return;
    }
    if (Type->Assaulter) {
        building->Unknown_004536D0(this);
        unknown_slot260(0, 1);
        unknown_slot87(building->Center_Coord(), true, true);
    }
}
