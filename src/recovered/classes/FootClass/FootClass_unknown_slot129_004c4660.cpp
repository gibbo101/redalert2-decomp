// int FootClass::unknown_slot129() (0x004C4660)
// A mission step for electric-assault units: without a target, a unit whose
// secondary weapon's warhead is ElectricAssault looks for an Overpowerable
// building of its own house in the eight cells around it, targets it and
// enters mission 1 (otherwise slot 258); with a target a HoverAttack type
// that is not in the air (slot 108) moves to the target's cell. A kind-15
// unit of a computer-controlled... (0x004F52F0) house that can capture
// (C4 or ability 14) switches to mission 17 when it targets a building.
// Returns the remaining fire delay (timer +0x244), 0 for a DistributedFire
// type with +0x3B8 positive, else the mission's rate in frames plus 0..2.
#include "shared/foot.hpp"
#include "shared/infantry.hpp"
#include "shared/building_type.hpp"
#include "shared/map_view.hpp"
// @ref ?unknown_6d7910@TechnoClass@@QAE_NH@Z=006d7910
// @ref ?Unknown_004717B0@UnknownCellClass@@QAEPAVBuildingClass@@XZ=004717b0
// @ref ?Unknown_004F52F0@HouseClass@@QAE_NXZ=004f52f0
// @ref ?Control@MissionClass@@QBEPAVMissionControlClass@@XZ=005950d0
// @ref __real@8@4008e100000000000000=0079b608
// @ref ?unknown_id_source_a3d290@@3PAVUnknownIDSource@@A=00a3d290
// @ref ?AdjacentCell@@3QBVCell@@B=00851a70
// @ref ?unknown_6cf130@TechnoClass@@QAE?AVCell@@PAVAbstractClass@@@Z=006cf130

int FootClass::unknown_slot129()
{
    if (unknown_228 == 0) {
        if (unknown_slot231(1)->WeaponType != 0 && unknown_slot231(1)->WeaponType->Warhead->ElectricAssault) {
            BuildingClass *building = 0;
            for (int facing = 0; facing < 8; facing++) {
                Cell cell = Adjacent_Cell(unknown_slot104(), facing);
                BuildingClass *candidate = ((UnknownCellClass *)&Map[cell])->Unknown_004717B0();
                if (candidate != 0 && candidate->Type->Overpowerable) {
                    HouseClass *owner = Owning_House();
                    if (candidate->Owning_House() == owner) {
                        building = candidate;
                        break;
                    }
                }
            }
            if (building != 0) {
                unknown_slot220(building);
                unknown_57e = true;
                unknown_slot116(1, false);
            } else {
                unknown_slot258();
            }
        } else {
            unknown_slot258();
        }
    } else if (unknown_slot32()->HoverAttack && unknown_slot108() == 0) {
        unknown_slot260((AbstractClass *)&Map[unknown_6cf130(this)], 1);
    }
    int delay = (int)(Control()->unknown_10 * 900.0);
    if (this != 0 && Kind_Of() == 15 && !House->Unknown_004F52F0()
        && (((InfantryClass *)this)->Type->C4 || unknown_6d7910(14))
        && unknown_slot91() != 17 && unknown_228 != 0 && unknown_228->Kind_Of() == 6) {
        unknown_slot116(17, false);
    }
    int result = 0;
    if (unknown_244.Value() != 0) {
        result = unknown_244.Value();
    } else if (!unknown_slot32()->DistributedFire || unknown_3a8.Count() <= 0) {
        result = delay + unknown_id_source_a3d290->Random()(0, 2);
    }
    return result;
}
