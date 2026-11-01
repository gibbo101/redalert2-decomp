// Infantry cell-entry constraints and occupancy priority.
#include "shared/infantry.hpp"
#include "shared/cell.hpp"
#include "shared/map_view.hpp"
#include "shared/building_type_class.hpp"
#include "shared/tube.hpp"
#include "shared/parasite.hpp"
#include "shared/overlay_type.hpp"
#include "shared/weapon_type.hpp"
#include "shared/ground_type.hpp"
extern "C" int __cdecl abs(int);
TubeClass *__fastcall Cell_Tube_0047a130(CellClass const *cell);
// @ref ?Cell_Tube_0047a130@@=0047a130
// @ref ?_com_issue_error@@YGXJ@Z=00795940
// @ref ?Is_Ally@HouseClass@@QBE_NPBVTechnoClass@@@Z=004e5580
// Four-byte occupancy storage; only the evidenced vehicle bit is interpreted.
struct CellOccupancyFlags_00503190 { unsigned int unknown_0:5; unsigned int vehicle:1; unsigned int unknown_6:26; };
// The existing fourth integer parameter carries adjacent-cell pointer bits.
int InfantryClass::unknown_slot101(CellClass *cell,int direction,int height,int adjacent,bool unused)
{
    bool bridge=(cell->unknown_140&0x100) && (height==-1 || abs(height-cell->unknown_11b)>1);
    unsigned char flags=cell->unknown_124;
    int infantry_owner=cell->unknown_54;
    bool vehicle=reinterpret_cast<CellOccupancyFlags_00503190 const &>(cell->unknown_124).vehicle!=0;
    TubeClass *tube=Cell_Tube_0047a130(cell);
    if (direction==8) {
        if (tube && Cell(tube->ExitCell)!=Cell(tube->EnterCell)) return 0;
        return 7;
    }
    if (tube) {
        int angle=abs(direction-tube->Facing);
        if (angle>2 && angle<6 && direction!=-1) return 7;
    }
    unsigned opposite=(direction-4)&7;
    TubeClass *other_tube=Cell_Tube_0047a130(&cell->Adjacent_Cell(opposite));
    if (other_tube) {
        int angle=abs(opposite-other_tube->Facing);
        if (angle>2 && angle<6 && direction!=-1) return 7;
    }
    if (height-cell->unknown_11b>4) return 0;
    if (unknown_slot102(reinterpret_cast<UnknownCellClass*>(cell),direction,&height,&bridge,reinterpret_cast<UnknownCellClass*>(adjacent))==7) return 7;
    if (height!=-1 && (cell->unknown_140&0x100) && height==cell->unknown_11b+4) {
        flags=cell->unknown_128;
        infantry_owner=cell->unknown_58;
        vehicle=reinterpret_cast<CellOccupancyFlags_00503190 const &>(cell->unknown_128).vehicle!=0;
    }
    if (unknown_32d && !unknown_a40774 && !Map.Unknown_0055A740(cell,true) && !unknown_slot189()) return 7;
    int result=0;
    if (cell->OverlayIndex!=-1) {
        OverlayTypeClass *overlay=OverlayTypes[cell->OverlayIndex];
        if (overlay->Crate && !House->unknown_func_4f52f0()) return 7;
        if (overlay->Wall && (cell->OverlayData>>4)!=overlay->DamageLevels) {
            if (!unknown_slot163() || !unknown_slot231(0)->WeaponType->unknown_func_733a90()) return 7;
            result=House->Is_Ally(cell->unknown_50) ? 4 : 5;
        }
    }
    int stationary_infantry=0;
    ObjectClass *occupant=bridge ? cell->AltOccupierPtr : cell->OccupierPtr;
    while (occupant) {
        if (occupant!=this) {
            if (unknown_588 && unknown_588->unknown_28) {
                if (occupant->unknown_slot104()==unknown_588->unknown_28->unknown_slot104()) return 0;
            }
            if (unknown_slot91()==7 || unknown_slot91()==8 || unknown_slot91()==9 ||
                (unknown_slot91()==17 && Type->C4) ||
                ((unknown_slot91()==11 || unknown_slot91()==25 || unknown_slot91()==5) && Type->Engineer)) {
                if (occupant==unknown_494 || reinterpret_cast<AbstractClass*>(&Map[CoordStruct(occupant->Coord)])==unknown_494 || occupant==unknown_228) {
                    if (!occupant->unknown_slot83()) {
                        float cost=Ground[cell->unknown_ec].Cost[Type->SpeedType];
                        bool unrestricted=unknown_370 || bridge;
                        if (!unrestricted && cost==0) return 7;
                        return 0;
                    }
                    return 7;
                }
                ObjectClass *building=cell->unknown_4717b0();
                if (building && occupant!=building) {
                    if (building==unknown_494 || reinterpret_cast<AbstractClass*>(&Map[building->Center_Coord()])==unknown_494 || building==unknown_228) {
                        occupant=occupant->unknown_30;
                        continue;
                    }
                }
            }
            if (unknown_slot91()==11 && unknown_1b0==occupant && unknown_1b0->Kind_Of()==1) return 7;
            if (Type->VehicleThief && occupant->unknown_slot31() && unknown_494==occupant && !occupant->unknown_slot32()->IsTrain) return 0;
            if (occupant->Kind_Of()==6) {
                BuildingClass *building=static_cast<BuildingClass*>(occupant);
                if (building->Type->InvisibleInGame || (building->Type->LaserFence && (building->unknown_4ec==12 || building->unknown_4ec==8))) {
                    occupant=occupant->unknown_30;
                    continue;
                }
                if (building->Type->FirestormWall) {
                    if (building->House->unknown_142) return 7;
                    occupant=occupant->unknown_30;
                    continue;
                }
                if (building->Type->Gate) {
                    if (!building->unknown_44d880()) {
                        if (building->House->Is_Ally(House)) { if (result<3) result=3; }
                        else {
                            if (!unknown_slot163()) return 7;
                            if (result<5) result=5;
                        }
                    }
                    occupant=occupant->unknown_30;
                    continue;
                }
            }
            if (unknown_slot91()==7 && occupant==unknown_494 && unknown_370) return 0;
            if (House->Is_Ally(static_cast<TechnoClass*>(occupant)) || unknown_a40774) {
                switch (occupant->Kind_Of()) {
                case 1: {
                    FootClass *unit=static_cast<FootClass*>(occupant);
                    if (unit->Locomotor.Checked()->Is_Moving() || unit->unknown_494) {
                        if (unit->unknown_5a0 || unit->Locomotor.Checked()->Will_Jump_Tracks()) { if (result<2) result=2; }
                    } else if (result<6) result=6;
                    break;
                }
                case 2:
                case 6: return 7;
                case 15:
                    if (!static_cast<FootClass*>(occupant)->Locomotor.Checked()->Is_Moving()) ++stationary_infantry;
                    break;
                default: break;
                }
            } else {
                TechnoClass *techno=occupant->As_Techno();
                if (!techno || techno->unknown_1b8!=2) {
                    int kind=occupant->Kind_Of();
                    if (unknown_6c16f0(-1)<=0 && kind!=36) return 7;
                    switch (kind) {
                    case 36: break;
                    case 15:
                        if (occupant->unknown_slot49(House)) result=6;
                        break;
                    case 6:
                        if (static_cast<BuildingClass*>(occupant)->Type->BridgeRepairHut) return 7;
                        if (result<5) result=5;
                        break;
                    default:
                        if (result<5) result=5;
                        break;
                    }
                } else if (result<1) result=1;
            }
        }
        occupant=occupant->unknown_30;
    }
    if (!unknown_370 && !bridge && Ground[cell->unknown_ec].Cost[Type->SpeedType]==0) return 7;
    if (!result && vehicle) return 2;
    if (infantry_owner!=-1) {
        if (House->Is_Ally(infantry_owner)) {
            if ((flags&0x1c)==0x1c && result<2) {
                if (stationary_infantry==3) result=6;
                else result=2;
            }
        } else {
            if (unknown_6c16f0(-1)>0) {
                if (result<5) result=5;
            } else return 7;
        }
    }
    if (!result && (flags&0x1c)==0x1c) return 7;
    return result;
}
