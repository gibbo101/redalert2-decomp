// int UnitClass::unknown_slot132() (0x00702F60, slot 132)
// The mission step of a unit that deploys into a building (when that
// building type is listed at rules +0x7C8, or the unit has a target, or the
// owner is human): status 0 becomes 1 when 0x006FD930 and 0x006FDFC0 allow
// it, status 1 falls back to 0 without +0x57C. Answers the mission's delay
// plus 0..2 frames; other units take the foot behaviour.
#include "shared/unit.hpp"
#include "shared/building_type.hpp"
// @ref ?Rules@@3PAVRulesClass@@A=00839848
// @ref ?Unknown_004F52F0@HouseClass@@QAE_NXZ=004f52f0
// @ref ?unknown_6fd930@UnitClass@@QAE_NXZ=006fd930
// @ref ?unknown_6fdfc0@UnitClass@@QAE_NXZ=006fdfc0
// @ref ?Control@MissionClass@@QBEPAVMissionControlClass@@XZ=005950d0
// @ref ??RRandom2Class@@QAEHHH@Z=006388a0
// @ref ?unknown_id_source_a3d290@@3PAVUnknownIDSource@@A=00a3d290
// @ref ?unknown_slot132@FootClass@@UAEHXZ=004c48e0
// @ref __ftol=0077f110
// @ref __real@8@4008e100000000000000=0079b608

int UnitClass::unknown_slot132()
{
    BuildingTypeClass *building = Type->DeploysInto;
    if (building && (Is_Listed(Rules->unknown_7c8, building) || unknown_228 || House->Unknown_004F52F0())) {
        switch (unknown_a8) {
        case 0:
            if (unknown_6fd930() && unknown_6fdfc0()) {
                unknown_a8 = 1;
            }
            break;
        case 1:
            if (!unknown_57c) {
                unknown_a8 = 0;
            }
            break;
        }
        int delay = (int)(Control()->unknown_10 * 900.0);
        return delay + unknown_id_source_a3d290->Random()(0, 2);
    }
    return FootClass::unknown_slot132();
}
