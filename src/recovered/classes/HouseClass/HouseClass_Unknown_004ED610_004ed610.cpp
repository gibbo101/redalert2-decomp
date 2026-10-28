// void HouseClass::Unknown_004ED610(TechnoClass *techno, bool arg2) (0x004ED610)
// An object of the house enters the map (TechnoClass slot 53): its type is
// counted by kind (buildings +0x5460, aircraft +0x5490, infantry +0x5480
// unless +0x5C1, units +0x5470); a building also adds its drain, its type's
// Storage to the capacity and its stored tiberium.
#include "shared/unit.hpp"
#include "shared/techno.hpp"
#include "shared/building_type_class.hpp"
#include "shared/infantry.hpp"
// @ref ?Increment@UnknownHouseCounter@@QAEXH@Z=00491c50
// @ref ??YStorageClass@@QAE?AV0@ABV0@@Z=0069af00

void HouseClass::Unknown_004ED610(TechnoClass *techno, bool arg2)
{
    switch (techno->Kind_Of()) {
    case 6:
        unknown_5460.Increment(techno->unknown_slot32()->unknown_slot16());
        if (techno != 0 && techno->Kind_Of() == 6) {
            BuildingClass *building = (BuildingClass *)techno;
            Adjust_Drain(building->unknown_449dd0());
            Capacity += building->Type->Storage;
            Tiberium += building->unknown_294;
        }
        break;
    case 2:
        unknown_5490.Increment(techno->unknown_slot32()->unknown_slot16());
        break;
    case 15:
        if (!((InfantryClass *)techno)->unknown_5c1) {
            unknown_5480.Increment(techno->unknown_slot32()->unknown_slot16());
        }
        break;
    case 1:
        unknown_5470.Increment(techno->unknown_slot32()->unknown_slot16());
        break;
    }
}
