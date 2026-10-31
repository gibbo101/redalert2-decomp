// BuildingClass *__fastcall Unknown_006BD240(BuildingTypeClass *type, HouseClass *enemy, FootClass *member, int mode, bool arg5) (0x006BD240)
// The member's own house's building of a type that rates best by mode: 0 lowest and 1 highest
// house value of its cell's block (0x0054E3A0), 2 nearest and 3 farthest from the member.
#include "shared/unit.hpp"
#include "shared/foot.hpp"
#include "shared/team.hpp"
#include "shared/house.hpp"
#include "shared/map_view.hpp"
#include "shared/coord_distance.hpp"
// @ref ?unknown_sqrt_4ba410@@YANN@Z=004ba410
// @ref __ftol=0077f110

AbstractClass *__fastcall Unknown_006BD240(BuildingTypeClass *type, HouseClass *enemy, FootClass *member, int mode, bool arg5)
{
    BuildingClass *best = 0;
    int best_value = -1;
    HouseClass *house = member->House;
    int count = house->Buildings.Count();
    for (int index = 0; index < count; index++) {
        BuildingClass *building = house->Buildings[index];
        if (building->Type == type) {
            int value = -1;
            switch (mode) {
            case 0: {
                Cell cell = Coord_Cell(building->Center_Coord());
                value = 0x7FFFFFFF - Map.Unknown_0054E3A0(cell, member->House);
                break;
            }
            case 1: {
                Cell cell = Coord_Cell(building->Center_Coord());
                value = Map.Unknown_0054E3A0(cell, member->House);
                break;
            }
            case 2: {
                CoordStruct here = member->Coord;
                CoordStruct there = building->Coord;
                CoordStruct delta(there.X-here.X, there.Y-here.Y, there.Z-here.Z);
                value = 0x7FFFFFFF - (int)unknown_sqrt_4ba410((double)delta.X * delta.X + (double)delta.Z * delta.Z + (double)delta.Y * delta.Y);
                break;
            }
            case 3: {
                CoordStruct here = member->Coord;
                CoordStruct there = building->Coord;
                value = Coord_Distance(there, here);
                break;
            }
            }
            if (value > best_value) {
                best_value = value;
                best = building;
            }
        }
    }
    return best;
}
