// int FootClass::unknown_slot130() (0x004C5900, slot 130)
// Guard area (TibSun Do_MISSION_GUARD_AREA shape; hypothesis). The navigation
// queue step is the unit's own 0x004C8B00 (TibSun Handle_Navigation_List),
// inlined here through a guard-area condition helper; its Delete 0x00454B20
// and Add 0x004CE210 stay out of line (Add binds the population-19 row as
// this unit's COMDAT copy). The archive-target stray test spills its flag
// byte (shared `bool; if (target) flag = ...; if (target && flag)` rule).
// @ref ?Add@?$DynamicVectorClass@PAVAbstractClass@@@@QAE_NABQAVAbstractClass@@@Z=004ce210
#include "shared/foot.hpp"
#include "shared/infantry.hpp"
#include "shared/building_type.hpp"
#include "shared/house.hpp"
#include "shared/rules.hpp"
#include "shared/map_view.hpp"
// @ref ?unknown_6d7910@TechnoClass@@QAE_NH@Z=006d7910
// @ref ?Unknown_004717B0@UnknownCellClass@@QAEPAVBuildingClass@@XZ=004717b0
// @ref ?Unknown_004F52F0@HouseClass@@QAE_NXZ=004f52f0
// @ref ?Control@MissionClass@@QBEPAVMissionControlClass@@XZ=005950d0
// @ref __real@8@4008e100000000000000=0079b608
// @ref __real@8@3ffec000000000000000=007a05d8
// @ref ?unknown_id_source_a3d290@@3PAVUnknownIDSource@@A=00a3d290
// @ref ?AdjacentCell@@3QBVCell@@B=00851a70
// @ref ?Map@@3VMouseClass@@A=008324e0
// @ref ?Unknown_005502E0@MapClass@@QAE?AVCell@@ABV2@HHH_NUPoint2D@@11110H@Z=005502e0
// @ref ?unknown_6d6e50@TechnoClass@@QAEXPAVAbstractClass@@@Z=006d6e50

inline Cell Coord_Cell_Value(CoordStruct coord)
{
    return Coord_Cell(coord);
}

inline void Guard_Navigation(FootClass *foot)
{
    if (!foot->House->Unknown_004F52F0() && foot->unknown_49c.Count() > 0 && foot->unknown_494 == 0 && foot->unknown_49c[0] == foot->unknown_1b0) {
        foot->unknown_4c8b00();
    }
}

int FootClass::unknown_slot130()
{
    Guard_Navigation(this);

    if (unknown_1b0 != 0 && unknown_1b0->Kind_Of() == 11) {
        BuildingClass *building = ((UnknownCellClass *)&Map[unknown_1b0->Center_Coord()])->Unknown_004717B0();
        if (building != 0 && House->Is_Ally(building->House) && !House->Unknown_004F52F0()
            && (Kind_Of() != 1 || !((UnitClass *)this)->Type->Harvester)) {
            Cell nearby = Map.Unknown_005502E0(Coord_Cell(unknown_1b0->Center_Coord()), 1, Map.Zone(Coord_Cell_Value(Coord), 0, false), 0, false, Point2D(1, 1), 0, 0, 0, 1, Cell(0, 0), 0);
            if (nearby != unknown_geometry_k) {
                unknown_6d6e50((AbstractClass *)&Map[nearby]);
            }
        }
    }

    if (Kind_Of() == 1 && ((UnitClass *)this)->Type->Harvester) {
        unknown_slot116(10, false);
        unknown_slot117();
        return 1 + unknown_id_source_a3d290->Random()(1, 10);
    }

    if (unknown_1b0 == 0 && MissionQueue == -1) {
        unknown_6d6e50((AbstractClass *)&Map[CoordStruct(Coord)]);
    }

    InfantryClass *infantry = As_Infantry(this);
    if (!House->Unknown_004F52F0() && infantry != 0 && (infantry->Type->C4 || infantry->unknown_6d7910(14))
        && unknown_slot91() != 17 && unknown_228 != 0 && unknown_228->Kind_Of() == 6) {
        unknown_slot116(17, false);
        return 1;
    }

    int maxrange = (int)(unknown_slot188(1) * 0.75);

    AbstractClass *archive = unknown_1b0;
    bool foot;
    if (archive != 0) {
        foot = archive->AbstractFlags.IsFoot;
    }
    if (archive != 0 && foot) {
        maxrange = Rules->GuardModeStray;
    }

    if (unknown_1b0 != 0) {
        if (!unknown_57d && unknown_494 == 0 && unknown_5d4c00(unknown_1b0) > maxrange) {
            unknown_slot220(0);
            unknown_slot260(unknown_1b0, 1);
        }

        if (unknown_228 == 0) {
            if (unknown_6d40c0() && unknown_6d9710()) {
                unknown_slot209(&unknown_1b0->Center_Coord(), 2);
            }
            if (unknown_228 != 0) {
                return 1;
            }
            unknown_slot258();
        } else {
            unknown_slot304();
        }
    }

    if (unknown_228 == 0 && unknown_slot231(1)->WeaponType != 0 && unknown_slot231(1)->WeaponType->Warhead->ElectricAssault) {
        for (int facing = 0; facing < 8; facing++) {
            Cell cell = Adjacent_Cell(unknown_slot104(), facing);
            BuildingClass *candidate = ((UnknownCellClass *)&Map[cell])->Unknown_004717B0();
            if (candidate != 0 && candidate->Type->Overpowerable && candidate->Owning_House() == Owning_House()) {
                if (candidate != 0) {
                    unknown_slot220(candidate);
                    unknown_57e = true;
                    unknown_slot116(1, false);
                }
                break;
            }
        }
    }

    int delay = (int)(Control()->unknown_10 * 900.0);
    if (Kind_Of() == 2) {
        delay *= 2;
    }
    return delay + unknown_id_source_a3d290->Random()(1, 5);
}
