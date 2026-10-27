// int FootClass::unknown_slot144() (0x004CC800)
// Area guard: state 0 attacks its target (slot 304) or, guarding a spot
// (+0x1B0, the unit's own cell by default), takes on an enemy (slot 219)
// within one and a half times its range (slot 188); with no target it
// heads for its house's guard cell (0x004EB270) and enters state 1, which
// resumes mission 11 on arrival. Returns the mission's rate in frames plus
// 0..2 (1 while attacking).
#include "shared/foot.hpp"
#include "shared/house.hpp"
#include "shared/map_view.hpp"
// @ref ?unknown_6d6e50@TechnoClass@@QAEXPAVAbstractClass@@@Z=006d6e50
// @ref ?Unknown_004EB270@HouseClass@@QAE?AVCell@@PAVFootClass@@@Z=004eb270
// @ref ?unknown_sqrt_4ba410@@YANN@Z=004ba410
// @ref __real@8@3fffc000000000000000=0079d568
// @ref ?Control@MissionClass@@QBEPAVMissionControlClass@@XZ=005950d0
// @ref __real@8@4008e100000000000000=0079b608
// @ref ?unknown_id_source_a3d290@@3PAVUnknownIDSource@@A=00a3d290

int FootClass::unknown_slot144()
{
    CoordStruct coord;
    switch (unknown_a8) {
    case 0:
        if (unknown_228 != 0) {
            unknown_slot304();
            break;
        }
        if (unknown_1b0 == 0) {
            coord = Coord;
            unknown_6d6e50((AbstractClass *)&Map[coord]);
        }
        unknown_578 = false;
        {
            AbstractClass *target = unknown_slot219(0, &unknown_1b0->Center_Coord(), 0);
            if (target != 0) {
                double distance = Offset_Length(target->Center_Coord() - unknown_1b0->Center_Coord());
                if (unknown_slot188(1) * 1.5 > distance) {
                    unknown_slot220(target);
                }
            }
        }
        if (unknown_228 != 0) {
            return 1;
        }
        unknown_a8 = 1;
        {
            Cell cell = House->Unknown_004EB270(this);
            if (cell != unknown_geometry_k) {
                unknown_slot260((AbstractClass *)&Map[cell], 1);
            } else {
                unknown_slot260(0, 1);
            }
        }
        unknown_6d6e50(0);
        break;
    case 1:
        if (unknown_494 == 0) {
            unknown_6d6e50(0);
            unknown_slot116(11, false);
            unknown_slot117();
        }
        break;
    }
    int delay = (int)(Control()->unknown_10 * 900.0);
    return delay + unknown_id_source_a3d290->Random()(0, 2);
}
