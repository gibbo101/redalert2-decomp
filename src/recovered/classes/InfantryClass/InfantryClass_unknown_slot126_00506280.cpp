// int InfantryClass::unknown_slot126() (0x00506280, slot 126)
// Mission handler for buildings as targets (+0x228): C4 infantry (or those
// passing 0x006D7910 (14)) plant on a building whose type has +0x121A and not
// +0x1385 (slot 260, then queue mission 17); owners failing HouseClass
// 0x004F52F0 send Infiltrate infantry, or Occupier/Assaulter infantry the
// building admits, in (slot 260, mission 8). Owners passing it while
// deploying run slot 240 and wait the mission rate plus 0-2 frames;
// otherwise FootClass's slot 126.
#include "shared/building_type.hpp"
#include "shared/infantry.hpp"
// @ref ?unknown_6d7910@TechnoClass@@QAE_NH@Z=006d7910
// @ref ?Unknown_004F52F0@HouseClass@@QAE_NXZ=004f52f0
// @ref ?Unknown_00452EB0@BuildingClass@@QAE_NPAVTechnoClass@@@Z=00452eb0
// @ref ?Control@MissionClass@@QBEPAVMissionControlClass@@XZ=005950d0
// @ref ?unknown_id_source_a3d290@@3PAVUnknownIDSource@@A=00a3d290
// @ref ??RRandom2Class@@QAEHHH@Z=006388a0
// @ref ?unknown_slot126@FootClass@@UAEHXZ=004c44c0
// @ref __real@8@4008e100000000000000=0079b608

int InfantryClass::unknown_slot126()
{
    if (Type->C4 || unknown_6d7910(14)) {
        if (unknown_228 != 0 && unknown_228->Kind_Of() == 6) {
            BuildingTypeClass *type = ((BuildingClass *)unknown_228)->Type;
            if (type->CanC4 && !type->InvisibleInGame) {
                unknown_slot260(unknown_228, 1);
                unknown_slot116(17, false);
                return 1;
            }
        }
    }
    if (!House->Unknown_004F52F0() && unknown_228 != 0 && unknown_228->Kind_Of() == 6) {
        if (Type->Infiltrate
            || ((Type->Occupier || Type->Assaulter) && ((BuildingClass *)unknown_228)->Unknown_00452EB0(this))) {
            unknown_slot260(unknown_228, 1);
            unknown_slot118(8);
            return 1;
        }
    }
    if (House->Unknown_004F52F0() && unknown_5090d0()) {
        unknown_slot240();
        int delay = (int)(Control()->unknown_10 * 900.0);
        return delay + unknown_id_source_a3d290->Random()(0, 2);   // the scenario's Random()
    }
    return FootClass::unknown_slot126();
}
