// int UnitClass::unknown_slot131() (0x007025A0, slot 131)
// TibSun UnitClass::Mission_Harvest: the harvester state machine (looking,
// harvesting, find home, heading home, going idle). Goes to guard when no dock
// building type is owned.
#include "shared/unit.hpp"
#include "shared/building_type_class.hpp"
#include "shared/house.hpp"
#include "shared/rules.hpp"
#include "shared/map_view.hpp"
#include "shared/cell.hpp"
#include "shared/mission.hpp"
#include "shared/id_source.hpp"
#include "shared/teleport_locomotion.hpp"
#include "shared/unknown_globals.hpp"
extern Cell const unknown_cell_ad0488;
// @ref ?unknown_cell_ad0488@@3VCell@@B=00ad0488
// @ref _CLSID_TeleportLocomotionClass=007a1fd0
// @ref _unknown_uuid_IPersist_7cf208=007cf208
// @ref ?Release_Held@?$UnknownComPtr@UIPersist@@$1?unknown_uuid_IPersist_7cf208@@3UGUID@@B@@QAEXXZ=004a4d00
// @ref ?Query@?$UnknownComPtr@UIPersist@@$1?unknown_uuid_IPersist_7cf208@@3UGUID@@B@@QAEJABV?$UnknownComPtr@UILocomotion@@$1?unknown_uuid_ILocomotion_7ce600@@3UGUID@@B@@@Z=00454bf0
// @ref ?unknown_func_491d10@UnknownHouseCounter@@QAEHH@Z=00491d10
// @ref ?Adjacent_Cell@CellClass@@QAEAAV1@I@Z=00476ac0
// @ref ?unknown_4717b0@CellClass@@QBEPAVObjectClass@@XZ=004717b0
// @ref __com_issue_error@4=00795940
// @ref ?Control@MissionClass@@QBEPAVMissionControlClass@@XZ=005950d0
// @ref ??RRandom2Class@@QAEHHH@Z=006388a0
// @ref ?unknown_id_source_a3d290@@3PAVUnknownIDSource@@A=00a3d290
// @ref __ftol=0077f110
// @ref ?unknown_4cb830@FootClass@@QAE_NH_N@Z=004cb830
// @ref ?unknown_4cb8f0@FootClass@@QAE?AVCell@@H_N@Z=004cb8f0
// @ref __real@8@4008e100000000000000=0079b608
// @ref __real@8@3fff8000000000000000=0079a708

ILocomotion *__fastcall Unit_Checked_Locomotor_004cde90(UnknownComPtr<ILocomotion,&unknown_uuid_ILocomotion_7ce600> const &owner);
// @ref ?Unit_Checked_Locomotor_004cde90@@=004cde90

class UnknownBuildingView_007025a0 : public TechnoClass {
public:
    BuildingTypeClass *Type;
};

inline CoordStruct Coord_Delta_007025a0(CoordStruct const &a, CoordStruct const &b)
{
    return CoordStruct(a.X - b.X, a.Y - b.Y, a.Z - b.Z);
}
inline int Length_007025a0(CoordStruct const &coord)
{
    double x = coord.X;
    double y = coord.Y;
    double z = coord.Z;
    return (int)unknown_sqrt_4ba410(z * z + y * y + x * x);
}
inline int Dist_A(ObjectClass const *self, ObjectClass const *other)
{
    return Length_007025a0(Coord_Delta_007025a0(self->Center_Coord(), other->Center_Coord()));
}
inline int Dist_B(ObjectClass const *self, ObjectClass const *other)
{
    return Offset_Length(Coord_Delta_007025a0(self->Center_Coord(), other->Center_Coord()));
}
#define DIST_A(o) Dist_A(this, o)
#define DIST_B(o) Dist_B(this, o)

int UnitClass::unknown_slot131()
{
    enum { LOOKING, HARVESTING, FINDHOME, HEADINGHOME, GOINGTOIDLE };
    int index;

    if (!Type->Harvester && !Type->Weeder) {
        return 450;
    }
    if (Type->Dock.Count() == 0 && !House->unknown_func_4f52f0()) {
        unknown_slot116(5, false);
        return 1;
    }
    bool found = false;
    for (index = 0; index < Type->Dock.Count(); index++) {
        if (House->unknown_5420.unknown_func_491d10(Type->Dock[index]->ArrayIndex) > 0) {
            found = true;
            break;
        }
    }
    if (!found) {
        unknown_slot116(5, false);
        return 1;
    }
    {
        bool teleporter = Type->Teleporter;
        switch (unknown_a8) {
        case LOOKING:
            if (!Type->Weeder && unknown_slot165() >= 1.0) {
                unknown_a8 = FINDHOME;
                return 1;
            }
            {
                bool hastarget = true;
                if (unknown_1b0 != 0) {
                    unknown_slot260(unknown_1b0, 1);
                    unknown_6d6e50(0);
                    hastarget = false;
                }
                unknown_5ba = false;
                bool ok;
                if (Type->Weeder) {
                    ok = unknown_4cc400(Rules->TiberiumFarScan / 256);
                } else {
                    UnknownComPtr<IPersist, &unknown_uuid_IPersist_7cf208> persist;
                    if (Locomotor) {
                        HRESULT status = persist.Query_Held(Unit_Checked_Locomotor_004cde90(Locomotor));
                        if (FAILED(status) && status != E_NOINTERFACE) {
                            _com_issue_error(status);
                        }
                    }
                    GUID clsid;
                    persist.Checked()->GetClassID(&clsid);
                    if (memcmp(&clsid, &CLSID_TeleportLocomotionClass, sizeof(GUID)) == 0 && unknown_494 != 0) {
                        unknown_slot260(0, 1);
                    }
                    ok = unknown_4cb830(Rules->TiberiumFarScan / 256, hastarget);
                }
                if (ok) {
                    unknown_5ba = true;
                    StageClass::Set_Rate(2);
                    StageClass::Stage = 0;
                    unknown_a8 = HARVESTING;
                    return 1;
                }
                if (unknown_494 == 0) {
                    if (unknown_1b0 != 0) {
                        unknown_slot260(unknown_1b0, 1);
                    } else {
                        unknown_a8 = GOINGTOIDLE;
                        unknown_328 = true;
                        if (Type->Harvester) {
                            House->unknown_189 = true;
                        }
                        return 105;
                    }
                } else {
                    unknown_328 = false;
                }
            }
            break;
        case HARVESTING:
            if (StageClass::Rate == 0) {
                StageClass::Stage = 0;
                StageClass::Set_Rate(Rules->unknown_1180);
            }
            if (StageClass::Stage < 9) {
                return 1;
            }
            if (!unknown_7013a0()) {
                unknown_5ba = false;
                if (Type->Harvester && unknown_slot165() == 1.0) {
                    unknown_a8 = FINDHOME;
                    Cell cell;
                    if (Type->Harvester) {
                        cell = unknown_4cb8f0(Rules->TiberiumNearScan / 256, 0);
                    } else {
                        cell = unknown_4cc100(Rules->TiberiumNearScan / 256);
                    }
                    if (cell != unknown_cell_ad0488) {
                        unknown_6d6e50(&Map[cell]);
                    } else {
                        unknown_6d6e50(0);
                    }
                    return 1;
                }
                bool ok;
                if (Type->Harvester) {
                    ok = unknown_4cb830(Rules->TiberiumNearScan / 256, false);
                } else {
                    ok = unknown_4cc400(Rules->TiberiumNearScan / 256);
                }
                if (!ok && unknown_494 == 0) {
                    unknown_6d6e50(0);
                    unknown_a8 = FINDHOME;
                } else {
                    unknown_a8 = HARVESTING;
                    unknown_5ba = true;
                }
                return 1;
            }
            return 1;
        case FINDHOME:
            if (unknown_494 != 0 && teleporter && unknown_slot299((DynamicVectorClass<TechnoTypeClass *> const *)&Type->Dock, 0, 0)) {
                unknown_4cd9b0();
            }
            if (unknown_494 == 0) {
                TechnoClass *nearest = unknown_slot299((DynamicVectorClass<TechnoTypeClass *> const *)&Type->Dock, 0, 0);
                if (((!teleporter && nearest != 0 && DIST_A(nearest) <= Rules->HarvesterTooFarDistance * 256)
                    || (teleporter && nearest != 0 && DIST_A(nearest) <= Rules->ChronoHarvTooFarDistance * 256))
                    && unknown_slot150(2, nearest) == 1) {
                    unknown_a8 = HEADINGHOME;
                    break;
                }
                unknown_a40774++;
                nearest = unknown_slot299((DynamicVectorClass<TechnoTypeClass *> const *)&Type->Dock, 0, 1);
                unknown_a40774--;
                if (nearest != 0) {
                    if (DIST_B(nearest) > 0x300 || teleporter) {
                        Cell cell = Coord_Cell(CoordStruct(nearest->Coord));
                        BuildingTypeClass *dock = ((UnknownBuildingView_007025a0 *)nearest)->Type;
                        Cell here = cell;
                        here.X = dock->QueueingCell.X + cell.X;
                        here.Y += dock->QueueingCell.Y;
                        here = Map.Unknown_005502E0(here, 2, -1, 0, false, Point2D(1, 1), 0, 0, 0, 1, Cell(0, 0), 0);
                        if (!(here == unknown_cell_ad0488)) {
                            unknown_slot260(&Map[here], 1);
                        } else {
                            unknown_slot260(0, 1);
                        }
                    }
                }
            }
            break;
        case HEADINGHOME:
            unknown_slot116(7, false);
            return 1;
        case GOINGTOIDLE:
            if (unknown_328) {
                if (House->unknown_5420.unknown_func_491d10(Rules->unknown_778->ArrayIndex) > 0) {
                    unknown_slot116(0x14, false);
                } else {
                    unknown_slot116(0xf, false);
                }
            }
            {
                ObjectClass *object = Map[CoordStruct(Coord)].unknown_4717b0();
                if (object != 0) {
                    BuildingTypeClass *type = ((UnknownBuildingView_007025a0 *)object)->Type;
                    if (type->Refinery || type->Weeder) {
                        unknown_slot260(&Map[unknown_6cf130(object)], 1);
                    }
                }
            }
            unknown_slot116(5, false);
            break;
        }
        int delay = (int)(Control()->unknown_10 * 900.0);
        return delay + Random_Pick(0, 2);
    }
}
