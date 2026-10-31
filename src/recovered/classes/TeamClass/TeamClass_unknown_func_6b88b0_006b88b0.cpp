// void TeamClass::unknown_func_6b88b0() (0x006B88B0; TS Regroup): restarts the script and sends the team toward the
// owner's unarmed building that rates best (distance from the team's center times one more than the
// house's value of the building's 4 x 4 cell block, halved for repair buildings) with a cell the leader
// can reach on the way (0x004BB3F0, hypothesis: Safety_Point); the target becomes that cell.
#include "shared/unit.hpp"
#include "shared/foot.hpp"
#include "shared/team.hpp"
#include "shared/house.hpp"
#include "shared/techno_type.hpp"
#include "shared/map_view.hpp"
#include "shared/coord_distance.hpp"
// @ref ?unknown_sqrt_4ba410@@YANN@Z=004ba410
// @ref __ftol=0077f110
// @ref _unknown_geometry_k=00ac0050
// @ref ?unknown_a40774@@3HA=00a40774

void TeamClass::unknown_func_6b88b0()
{
    IsMoving = false;
    Script->Reset();
    if (unknown_48 > 0) {
        unknown_func_6b9610(&unknown_34, &unknown_38);
        if (unknown_34 == 0) {
            if (unknown_38 == 0) {
                return;
            }
            unknown_34 = unknown_38;
        }
        Cell best_cell = Coord_Cell(unknown_34->Center_Coord());
        int best = 0x7FFFFFFF;
        int count = Owner->Buildings.Count();
        for (int index = 0; index < count; index++) {
            BuildingClass *building = Owner->Buildings[index];
            if (building != 0 && !building->unknown_76 && building->unknown_slot231(0)->WeaponType == 0) {
                Cell cell = Coord_Cell(building->Center_Coord());
                int value = Coord_Distance(building->Center_Coord(), unknown_34->Center_Coord()) * (Map.Unknown_0054E3A0(cell, Owner) + 1);
                if (building->Type->unknown_1349) {
                    value /= 2;
                }
                if (value < best) {
                    cell = unknown_func_6baa60()->Unknown_004BB3F0(Coord_Cell(unknown_34->Center_Coord()), cell, 2, 4);
                    if (cell != unknown_geometry_k) {
                        best = value;
                        best_cell = cell;
                    }
                }
            }
        }
        unknown_40 = &Map[best_cell];
        unknown_func_6ba1a0();
    } else {
        unknown_34 = 0;
    }
}

// @ref ?Unknown_004BB3F0@FootClass@@QAE?AVCell@@ABV2@0HH@Z=004bb3f0
