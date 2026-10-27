// TechnoClass *FootClass::unknown_slot300(TechnoTypeClass *type, int arg2, int arg3, int *score) (0x004CD760)
// The best building of a type to dock at (hypothesis): among the house's
// active Buildings of that type that are in radio contact (unless arg3 is
// 1) and reachable (aircraft always), those accepting message 0xF; the
// nearest wins (Distance_Squared into *score, -1 for none yet), a building
// with +0x32B set always replaces the choice. Null when the house has none
// of the type (0x00491D10).
#include "shared/foot.hpp"
#include "shared/building_type.hpp"
#include "shared/building_type.hpp"
#include "shared/aircraft.hpp"
#include "shared/map_view.hpp"
// @ref ?unknown_func_491d10@UnknownHouseCounter@@QAEHH@Z=00491d10
// @ref ?Unknown_00636ED0@RadioClass@@QBE_NPAVTechnoClass@@@Z=00636ed0
// @ref ?Distance_Squared@ObjectClass@@QBEHPBV1@@Z=005d4da0

TechnoClass *FootClass::unknown_slot300(TechnoTypeClass *type, int arg2, int arg3, int *score)
{
    TechnoClass *best = 0;
    if (House->unknown_5420.unknown_func_491d10(((BuildingTypeClass *)type)->ArrayIndex) != 0) {
        int count = House->Buildings.Count();
        for (int index = 0; index < count; index++) {
            BuildingClass *building = House->Buildings[index];
            if (building != 0 && !building->unknown_76 && building->Type == type
                && (arg3 == 1 || building->Unknown_00636ED0(this))) {
                if (Kind_Of() != 2) {
                    Cell there = Coord_Cell(building->Center_Coord());
                    Cell here = Coord_Cell(unknown_slot19(0));
                    if (!Map.Unknown_0054F7C0(here, there, unknown_slot32()->MovementZone, unknown_slot46(0), 0, 0)) {
                        continue;
                    }
                }
                if (unknown_slot150(15, building) == 1) {
                    int distance = Distance_Squared(building);
                    if (*score == -1 || distance < *score || building->unknown_32b) {
                        best = building;
                        *score = distance;
                    }
                }
            }
        }
    }
    return best;
}
