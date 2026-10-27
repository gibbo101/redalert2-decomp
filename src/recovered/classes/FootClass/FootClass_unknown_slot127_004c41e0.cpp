// int FootClass::unknown_slot127() (0x004C41E0)
// As slot 128 for infantry that can take, occupy, assault or infiltrate
// the building it targets; with no target a computer-controlled unit that
// is not an Occupier drops its target and enters mission 15. Returns the
// mission's rate in frames plus 0..2.
#include "shared/foot.hpp"
#include "shared/infantry.hpp"
#include "shared/map_view.hpp"
// @ref ?unknown_6d7910@TechnoClass@@QAE_NH@Z=006d7910
// @ref ?Unknown_004717B0@UnknownCellClass@@QAEPAVBuildingClass@@XZ=004717b0
// @ref ?Unknown_004F52F0@HouseClass@@QAE_NXZ=004f52f0
// @ref ?Control@MissionClass@@QBEPAVMissionControlClass@@XZ=005950d0
// @ref __real@8@4008e100000000000000=0079b608
// @ref ?unknown_id_source_a3d290@@3PAVUnknownIDSource@@A=00a3d290

int FootClass::unknown_slot127()
{
    InfantryClass *infantry = As_Infantry(this);
    if (unknown_228 != 0 && unknown_228->Kind_Of() == 6 && unknown_494 == 0 && infantry != 0) {
        if (infantry->Type->C4 || infantry->unknown_6d7910(14) || infantry->Type->Engineer
            || infantry->Type->Occupier || infantry->Type->Assaulter || infantry->Type->Infiltrate) {
            unknown_slot260(unknown_228, true);
        }
    }
    if (unknown_494 == 0) {
        unknown_slot261(0, true);
        if (((UnknownCellClass *)&Map[Center_Coord()])->Unknown_004717B0() != 0) {
            unknown_slot87(unknown_geometry_l, 1 != 0, 0 != 0);
        }
    }
    if (unknown_228 == 0 && !House->Unknown_004F52F0()
        && (Kind_Of() != 15 || !((InfantryClass *)this)->Type->Occupier)) {
        unknown_slot220(0);
        unknown_slot260(0, true);
        unknown_slot116(15, false);
    }
    int delay = (int)(Control()->unknown_10 * 900.0);
    return delay + unknown_id_source_a3d290->Random()(0, 2);
}
