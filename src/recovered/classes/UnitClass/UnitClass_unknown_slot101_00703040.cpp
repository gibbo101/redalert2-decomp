// int UnitClass::unknown_slot101(CellClass *cell, int direction, int height, int adjacent, bool unused) (0x00703040)
// TibSun UnitClass::Can_Enter_Cell.
#include "shared/unit.hpp"
#include "shared/cell.hpp"
#include "shared/map_view.hpp"
#include "shared/building_type_class.hpp"
#include "shared/tube.hpp"
#include "shared/parasite.hpp"
#include "shared/overlay_type.hpp"
#include "shared/weapon_type.hpp"
#include "shared/warhead_type.hpp"
#include "shared/ground_type.hpp"
#include "shared/house.hpp"
#include "shared/fast_math.hpp"
#include "shared/bullet_type.hpp"
extern "C" int __cdecl abs(int);
TubeClass *__fastcall Cell_Tube_0047a130(CellClass const *cell);
TechnoClass *__fastcall As_Techno_0040dbd0(AbstractClass *object);
struct UnknownIsoTile {
    char unknown_000[0x2B4];
    int Width;                  // +0x2B4
    int Height;                 // +0x2B8
};
extern DynamicVectorClass<UnknownIsoTile *> unknown_iso_tiles_a40cd0;
extern double const unknown_facing_scale_79b628;
extern double const unknown_facing_origin_79b630;
// @ref ?unknown_iso_tiles_a40cd0@@=00a40cd0
// @ref ?unknown_facing_scale_79b628@@3NB=0079b628
// @ref ?unknown_facing_origin_79b630@@3NB=0079b630
// @ref ?Cell_Tube_0047a130@@=0047a130
// @ref ?As_Techno_0040dbd0@@=0040dbd0
// @ref ?_com_issue_error@@YGXJ@Z=00795940
// @ref ?Is_Ally@HouseClass@@QBE_NPBVTechnoClass@@@Z=004e5580
inline UnknownFacingDir Direction_00703040(CoordStruct const &coord1,CoordStruct const &coord2)
{
    int x1=coord1.X;
    int x2=coord2.X;
    return UnknownFacingDir((unsigned short)(int)((Fast_Atan2((double)coord1.Y-(double)coord2.Y,(double)x2-(double)x1)-unknown_facing_origin_79b630)*unknown_facing_scale_79b628));
}
inline int Distance_00703040(CoordStruct const &coord1,CoordStruct const &coord2)
{
    CoordStruct diff=coord1-coord2;
    double y=diff.Y;
    double z=diff.Z;
    double x=diff.X;
    return (int)Fast_Sqrt(y*y+z*z+x*x);
}
struct CellOccupancyFlags_00703040 { unsigned int unknown_0:5; unsigned int vehicle:1; unsigned int unknown_6:26; };

int UnitClass::unknown_slot101(CellClass *cell,int direction,int height,int adjacent,bool unused)
{
    bool bridge=(cell->unknown_140&0x100) && (height==-1 || abs(height-cell->unknown_11b)>1);
    unsigned char flags=cell->unknown_124;
    bool vehicle=reinterpret_cast<CellOccupancyFlags_00703040 const &>(cell->unknown_124).vehicle!=0;
    int infantry_owner=cell->unknown_54;
    TubeClass *tube=Cell_Tube_0047a130(cell);
    if (Type->MovementRestrictedTo!=-1) {
        if (cell->unknown_ec==10) {
            UnknownIsoTile *tile=unknown_iso_tiles_a40cd0[cell->IsoTileIndex];
            if ((tile->Width==5 && tile->Height==3) || (tile->Width==4 && tile->Height==3)) {
                if (cell->unknown_11a!=2) return 7;
            } else if ((tile->Width==3 && tile->Height==4 || tile->Width==3 && tile->Height==5) && cell->unknown_11a!=6) {
                return 7;
            }
        }
        if (cell->unknown_ec!=Type->MovementRestrictedTo && cell->unknown_ec!=10) {
            if (cell->OverlayIndex<0xED || cell->OverlayIndex>0xEE || height==cell->unknown_11b) return 7;
        }
    }
    if (direction==8) {
        if (tube) {
            Cell exit=tube->ExitCell;
            if (exit!=Cell(0,0)) return 0;
        }
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
    int result=unknown_slot102(reinterpret_cast<UnknownCellClass*>(cell),direction,&height,&bridge,reinterpret_cast<UnknownCellClass*>(adjacent));
    if (result==7) return 7;
    if (height!=-1 && (cell->unknown_140&0x100) && height==cell->unknown_11b+4) {
        flags=cell->unknown_128;
        vehicle=reinterpret_cast<CellOccupancyFlags_00703040 const &>(cell->unknown_128).vehicle!=0;
        infantry_owner=cell->unknown_58;
    }
    if (!unknown_a40774 && !Map.Unknown_0055A740(cell,true) && !unknown_slot189() && unknown_32d) return 7;
    result=FootClass::unknown_slot101(cell,direction,height,adjacent,unused);
    if (result==7) return 7;
    if (cell->OverlayIndex!=-1) {
        OverlayTypeClass *overlay=OverlayTypes[cell->OverlayIndex];
        if (overlay->Crate && !House->unknown_func_4f52f0() && unknown_game_mode_a3d298==0) return 7;
        if (overlay->Wall) {
            if (overlay->unknown_1fd && (Type->Crusher || unknown_6d7910(0x11))) {
                if (House->Is_Ally(cell->unknown_50)) {
                    if (result<4) result=4;
                }
            } else {
                if (unknown_slot163()) {
                    WarheadTypeClass *warhead=unknown_slot231(0)->WeaponType->Warhead;
                    if (warhead->Wall || (warhead->Wood && overlay->unknown_9c==6)) {
                        if (House->Is_Ally(cell->unknown_50)) {
                            if (result<4) result=4;
                        } else {
                            if (result<5) result=5;
                        }
                    } else {
                        return 7;
                    }
                } else {
                    return 7;
                }
            }
        }
    }
    bool crushable=false;
    ObjectClass *occupant=bridge ? cell->AltOccupierPtr : cell->OccupierPtr;
    while (occupant) {
        if (this!=occupant) {
            if (unknown_588 && unknown_588->unknown_28) {
                if (occupant->unknown_slot104()==unknown_588->unknown_28->unknown_slot104()) return 0;
            }
            TechnoClass *contact=occupant->AbstractFlags.IsTechno ? static_cast<TechnoClass*>(occupant) : 0;
            if (Is_Radio_Contact(contact) && occupant->Kind_Of()==6 && !static_cast<BuildingClass*>(occupant)->Cell_Is_Impassable_Row_00453af0(cell)) {
                occupant=occupant->unknown_30;
                continue;
            }
            if (Type->SmallVisceroid && occupant->Kind_Of()==1 && static_cast<UnitClass*>(occupant)->Type->SmallVisceroid) return 0;
            if (occupant->Kind_Of()==6) {
                BuildingClass *building=static_cast<BuildingClass*>(occupant);
                if (building->Type->Gate) {
                    if (!building->unknown_44d880()) {
                        if (building->House->Is_Ally(House)) {
                            if (result<3) result=3;
                        } else {
                            if (!unknown_slot163()) return 7;
                            if (result<5) result=5;
                        }
                    }
                    occupant=occupant->unknown_30;
                    continue;
                }
                if (direction!=-1 && building->Type->UnitRepair && cell->unknown_4717b0()==building && !building->Cell_Is_Impassable_Row_00453af0(cell)) {
                    occupant=occupant->unknown_30;
                    continue;
                }
                if (building->Type->InvisibleInGame) {
                    occupant=occupant->unknown_30;
                    continue;
                }
                if (building->Type->LaserFence && (building->unknown_4ec==12 || building->unknown_4ec==8)) {
                    occupant=occupant->unknown_30;
                    continue;
                }
                if (building->Type->FirestormWall) {
                    if (building->House->unknown_142) return 7;
                    occupant=occupant->unknown_30;
                    continue;
                }
                if (building->Type->Bib) {
                    if (Map[Adjacent_Cell(cell->MapCoords,2)].unknown_4717b0()!=building) {
                        occupant=occupant->unknown_30;
                        continue;
                    }
                }
            }
            if (unknown_slot91()==7 && occupant==unknown_494 && occupant->Kind_Of()==1) return 0;
            if (unknown_slot91()==11 && unknown_1b0==occupant) return 7;
            FootClass *foot;
            if (occupant->AbstractFlags.IsFoot) {
                foot=static_cast<FootClass*>(occupant);
            } else {
                foot=0;
            }
            bool is_moving=foot!=0 && (foot->unknown_494 || foot->unknown_2e0.Is_Rotating() || foot->Locomotor.Checked()->Is_Moving());
            if (House->Is_Ally(static_cast<TechnoClass*>(occupant))) {
                if (is_moving) {
                    int face=Dir_To_8(unknown_2e0.Current());
                    UnknownFacingDir reverse=UnknownFacingDir((unsigned short)(static_cast<FootClass*>(occupant)->unknown_2e0.Current().Raw+0x7FFF));
                    int techface=Dir_To_8(reverse);
                    int &tech=techface;
                    UnknownFacingDir direct=Direction_00703040(Position_Coord_004f3f40(),occupant->Position_Coord_004f3f40());
                    if (face==tech && Distance_00703040(Center_Coord(),occupant->Center_Coord())<=0x1FF && Dir_To_8(direct)==face) return 7;
                    if ((foot->unknown_5a0 && foot->Kind_Of()!=15) || foot->Locomotor.Checked()->Will_Jump_Tracks()) {
                        if (result<2) result=2;
                    }
                } else {
                    if (occupant->Kind_Of()==6) return 7;
                    if (result<6) result=6;
                }
            } else {
                TechnoClass *techno=As_Techno_0040dbd0(occupant);
                if (techno && techno->unknown_1b8==2) {
                    if (result<1) result=1;
                } else {
                    ObjectTypeClass *otype;
                    if ((Type->Crusher || unknown_6d7910(0x11)) && (otype=occupant->Class_Of())->unknown_1fd) {
                        if (!House->Is_Ally(static_cast<TechnoClass*>(occupant))) crushable=true;
                    } else {
                        if (!unknown_slot231(0)->WeaponType && !Type->IsTrain) return 7;
                        switch (occupant->Kind_Of()) {
                        case 36: {
                            int which=unknown_slot174(occupant);
                            WeaponTypeClass *weapon=unknown_slot231(which)->WeaponType;
                            if (weapon==0 || weapon->Warhead==0 || !weapon->Warhead->Wood) return 7;
                        }
                        default:
                            if (result<5) result=5;
                            break;
                        case 6:
                            if (static_cast<BuildingClass*>(occupant)->Type->BridgeRepairHut) return 7;
                            if (result<5) result=5;
                            break;
                        }
                    }
                }
            }
        } else {
            vehicle=false;
            flags&=~0x20;
        }
        occupant=occupant->unknown_30;
    }
    if (!bridge && Ground[cell->unknown_ec].Cost[Type->SpeedType]==0) return 7;
    if (result==0 && !crushable && (flags&0x3F)) {
        if (vehicle) {
            result=2;
        } else {
            if (infantry_owner!=-1 && House->Is_Ally(infantry_owner)) {
                result=2;
            } else {
                if (!Type->Crusher && !unknown_6d7910(0x11)) {
                    if (Type->IsTrain || (unknown_slot231(0)->WeaponType!=0 && unknown_slot231(0)->WeaponType->Projectile->AG)) {
                        result=5;
                    } else {
                        return 7;
                    }
                }
            }
        }
    }
    if (result==0 && crushable && vehicle) {
        if (!cell->Cell_Unit() || !static_cast<UnitClass*>(cell->Cell_Unit())->Type->unknown_1fd) return 2;
    }
    return result;
}
