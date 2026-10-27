// int UnitClass::unknown_slot129() (0x00704440, slot 129)
// The harvest mission step (hypothesis). A computer harvester or weeder
// returns to mission 10 when its house owns one of its dock types (a
// harvester only while the house lacks +0x189); a human-owned teleporting
// miner does when a friendly refinery is adjacent, or when it is full and
// not moving. A unit deploying into a listed building for a computer house
// with +0x13B queues mission 16 and answers the mission's delay plus 0..2;
// a weeder flagged +0x5A2 returns to mission 10. Then the foot behaviour.
#include "shared/unit.hpp"
#include "shared/building_type.hpp"
#include "shared/cell.hpp"
// @ref ?Rules@@3PAVRulesClass@@A=00839848
// @ref ?Unknown_004F52F0@HouseClass@@QAE_NXZ=004f52f0
// @ref ?unknown_func_491d10@UnknownHouseCounter@@QAEHH@Z=00491d10
// @ref ?Adjacent_Cell@CellClass@@QAEAAV1@I@Z=00476ac0
// @ref ?unknown_4717b0@CellClass@@QBEPAVObjectClass@@XZ=004717b0
// @ref __com_issue_error@4=00795940
// @ref ?Control@MissionClass@@QBEPAVMissionControlClass@@XZ=005950d0
// @ref ??RRandom2Class@@QAEHHH@Z=006388a0
// @ref ?unknown_id_source_a3d290@@3PAVUnknownIDSource@@A=00a3d290
// @ref ?unknown_slot129@FootClass@@UAEHXZ=004c4660
// @ref __ftol=0077f110
// @ref __real@8@4008e100000000000000=0079b608
// @ref __real@8@3fff8000000000000000=0079a708

// A building's type and house (a view until shared/building.hpp is
// installed: the type pointer follows TechnoClass at +0x418).
struct UnknownUnitBuildingView2 : TechnoClass {
    BuildingTypeClass *Type;                // +0x418
};

int UnitClass::unknown_slot129()
{
    if (Type->Harvester || Type->Weeder) {
        if (!House->Unknown_004F52F0()) {
            for (int index = 0; index < Type->Dock.Count(); index++) {
                if (House->unknown_5420.unknown_func_491d10(Type->Dock[index]->ArrayIndex) > 0) {
                    if (!Type->Harvester || !House->unknown_189) {
                        unknown_slot116(10, false);
                        return 1;
                    }
                    break;
                }
            }
        } else if (Type->Teleporter) {
            CellClass *cell = (CellClass *)unknown_slot105();
            for (int facing = 0; facing < 8; facing++) {
                UnknownUnitBuildingView2 *building = (UnknownUnitBuildingView2 *)cell->Adjacent_Cell(facing).unknown_4717b0();
                if (building && building->Type->Refinery && building->House == House) {
                    unknown_slot116(10, false);
                    return 1;
                }
            }
            if (unknown_slot165() == 1.0 && Locomotor.Checked()->Is_Moving()) {
                unknown_slot116(10, false);
                return 1;
            }
        }
    }
    BuildingTypeClass *building = Type->DeploysInto;
    if (building && Is_Listed(Rules->unknown_7c8, building)
        && House->unknown_13b && !House->Unknown_004F52F0()) {
        unknown_slot116(16, false);
        int delay = (int)(Control()->unknown_10 * 900.0);
        return delay + unknown_id_source_a3d290->Random()(0, 2);
    }
    if (Type->Weeder && unknown_5a2) {
        unknown_5a2 = false;
        unknown_slot116(10, false);
    }
    return FootClass::unknown_slot129();
}
