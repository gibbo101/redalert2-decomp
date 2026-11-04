// Building selling and undeployment state machine, original00445B30 body3308+4.
#include "shared/building.hpp"
#include "shared/house.hpp"
#include "shared/gscreen.hpp"
#include "shared/building_map.hpp"
#include "shared/cell.hpp"
#include "shared/infantry.hpp"
#include "shared/infantry_type.hpp"
#include "shared/unit.hpp"
#include "shared/unit_type.hpp"
#include "shared/object_type.hpp"
#include "shared/tag.hpp"
#include "shared/rules.hpp"
#include "shared/storage_class.hpp"
#include "shared/unknown_vector3.hpp"
inline UnknownVector3 Coord_Difference(CoordStruct const &,CoordStruct const &);
void __fastcall Building_Refresh_House_Buildings_0044fa40(HouseClass *house);
extern "C" char const deconstruction_eva_unit_sold_007cf9c4[];
extern "C" char const deconstruction_eva_structure_sold_007cf9d4[];
// @ref _deconstruction_eva_unit_sold_007cf9c4=007cf9c4
// @ref _deconstruction_eva_structure_sold_007cf9d4=007cf9d4
// Snap to the cell center with the original signed 32-bit division.
inline CoordStruct Snap_To_Cell_Center(CoordStruct const &coord)
{
    return CoordStruct(coord.X/256*256+128,coord.Y/256*256+128,coord.Z);
}
inline int ObjectClass::Distance(CoordStruct const &coord) const
{
    UnknownVector3 difference=Coord_Difference(Center_Coord(),coord);
    return difference.Length();
}
inline int ObjectClass::Distance_To(AbstractClass const *target) const
{
    return Distance(target->Center_Coord());
}
int BuildingClass::unknown_slot140()
{
    unknown_slot97(0);
    bool selected=unknown_77;
    switch(unknown_a8) {
    case 0:
        if(unknown_445ab0() && (Type->Artillary || Type->TickTank)) {
            unknown_slot220(0);
        }
        if(Type->UnitRepair && unknown_slot149(19)==1 &&
           Distance_To(Contact(0))<128) {
            TechnoClass *contact=Contact(0);
            unknown_slot149(3);
            if(unknown_372) Speech_Play_Name(deconstruction_eva_unit_sold_007cf9c4,-1,-1);
            contact->unknown_slot98(1);
            unknown_slot116(5,false);
            return 1;
        }
        if(unknown_5c6) {
            TechnoClass *upgrade=(TechnoClass*)unknown_4c0[unknown_5c6-1]->unknown_slot35(House);
            House->Refund_Money(upgrade->unknown_slot167());
            delete upgrade;
            unknown_44c860();
            House->unknown_5668=true;
            House->unknown_5669=true;
            Building_Refresh_House_Buildings_0044fa40(House);
            if(unknown_372) Speech_Play_Name(deconstruction_eva_structure_sold_007cf9d4,-1,-1);
            unknown_slot116(5,false);
            return 1;
        }
        unknown_5ad=false;
        unknown_slot152(23);
        if(Type->LaserFencePost) unknown_44e5a0(0);
        unknown_4397c0();
        unknown_a8=1;
        break;
    case 1:
        unknown_slot152(3);
        if(!unknown_370) {
            if(!unknown_1b0 || !Type->UndeploysInto) {
                int count=unknown_slot172();
                bool engineer=false;
                Cell const *foundation=unknown_slot64(0);
                Cell const *end=foundation;
                int cells=0;
                while(end->X!=32767 || end->Y!=32767) {++cells;++end;}
                while(count) {
                    InfantryTypeClass *crew=unknown_slot184();
                    while(crew->Engineer && engineer) crew=unknown_slot184();
                    if(crew->Engineer) engineer=true;
                    InfantryClass *infantry=0;
                    if(crew) infantry=new InfantryClass(crew,House);
                    if(infantry) {
                        ++unknown_a40774;
                        int choice=unknown_id_source_a3d290->RandomNumber(0,cells-1);
                        Cell cell=unknown_slot104()+foundation[choice];
                        CoordStruct position=CoordStruct(cell)+CoordStruct(0,36,0);
                        position=Map[position].Closest_Free_Spot(position,false,false);
                        if(position==unknown_geometry_l || !infantry->unknown_slot53(&position,0)) {
                            delete infantry;
                        } else {
                            if(infantry->Type->Nominal) infantry->unknown_5c1=true;
                            --unknown_a40774;
                            infantry->unknown_slot87(unknown_geometry_l,true,false);
                            ++unknown_a40774;
                            infantry->unknown_slot116(2,false);
                        }
                        --unknown_a40774;
                    }
                    --count;
                }
            }
            if(House->Unknown_004F52B0() && !unknown_slot31()) {
                Voc_Play_At(Rules->unknown_5c4,Position_Coord_004f3f40(),0);
                if(Type->PackupSound!=-1) Voc_Play_At(Type->PackupSound,Position_Coord_004f3f40(),&unknown_570);
            }
            unknown_a8=2;
            unknown_443d60(0);
            unknown_5ad=false;
            if(selected) unknown_slot80();
        }
        break;
    case 2:
        Voc_Update_At(Position_Coord_004f3f40(),&unknown_570);
        if(unknown_5ad) {
            House->unknown_144=true;
            unknown_slot220(0);
            if(unknown_372 && !Type->UndeploysInto) Speech_Play_Name(deconstruction_eva_structure_sold_007cf9d4,-1,-1);
            if(unknown_445ab0()) {
                if(Type->Artillary &&
                   (unknown_2c8.Current()!=UnknownFacingDir((Dir256)Type->BarrelStartPitch) ||
                    unknown_2e0.Current()!=UnknownFacingDir((Dir256)Type->unknown_c64))) {
                    unknown_2c8.Set_Desired(UnknownFacingDir((Dir256)Type->BarrelStartPitch));
                    unknown_2e0.Set_Desired(UnknownFacingDir((Dir256)Type->unknown_c64));
                    return 1;
                }
                ++unknown_a40774;
                UnitClass *unit=new UnitClass(Type->UndeploysInto,House);
                --unknown_a40774;
                if(unit) {
                    double ratio=Health_Ratio();
                    int refund=unknown_slot167();
                    AbstractClass *archive=unknown_1b0;
                    CoordStruct place;
                    if(Type->SensorArray || Type->TickTank || Type->ICBMLauncher || Type->Artillary) {
                        place=Position_Coord_004f3f40();
                    } else {
                        CoordStruct position=Position_Coord_004f3f40();
                        CoordStruct adjacent(position.X+unknown_facing_offsets_851ac0[3].X,
                                             position.Y+unknown_facing_offsets_851ac0[3].Y,position.Z);
                        place=Snap_To_Cell_Center(adjacent);
                    }
                    if(unknown_4e8) unknown_4e8->Deactivate(0);
                    DynamicVectorClass<TechnoClass*> targetters;
                    for(int index=0;index<Technos.Count();++index) {
                        TechnoClass *techno=Technos[index];
                        if(techno->unknown_228 && techno->unknown_228->Kind_Of()==6 &&
                           techno->unknown_228==this && techno->unknown_7d && techno!=this && techno!=unit) {
                            targetters.Add(techno);
                        }
                    }
                    unknown_slot52();
                    int deploy_facing=Type->unknown_func_45ec90();
                    if(unit->unknown_slot53(&place,deploy_facing)) {
                        unit->Strength=(int)(unit->Class_Of()->MaxStrength*ratio);
                        unit->Strength=unit->Strength>1 ? unit->Strength : 1;
                        unit->unknown_70=unit->Strength;
                        unit->unknown_114=unknown_114;
                        unit->unknown_1ac=unknown_1ac;
                        unit->unknown_118=unknown_118;
                        if(Type->Artillary) unit->unknown_2c8.Set_Current(UnknownFacingDir((Dir256)Type->BarrelStartPitch));
                        if(archive) {
                            unit->unknown_slot260(archive,1);
                            unit->unknown_slot116(2,false);
                        }
                        if(unknown_34) {
                            unit->Attach_Tag(unknown_34);
                            --unknown_34->unknown_2c;
                            unknown_34=0;
                        }
                        if(selected) unit->unknown_slot80();
                        for(int index=0;index<targetters.Count();++index) targetters[index]->unknown_slot220(unit);
                    } else {
                        House->Refund_Money(refund);
                    }
                } else {
                    House->Refund_Money(unknown_slot167());
                }
                unknown_slot54(true);
                unknown_570.Unknown_00406070();
                unknown_slot60();
                Building_Refresh_House_Buildings_0044fa40(House);
            } else {
                unknown_434=-1;
                unknown_slot55(0);
                if(unknown_4e8) unknown_4e8->Deactivate(0);
                House->Refund_Money(unknown_slot167());
                unknown_slot52();
                StorageClass *storage=&unknown_294;
                int slot=storage->First_Used_Slot();
                while(slot!=-1) {
                    int amount=(int)storage->Remove_Amount(storage->Get_Amount(slot),slot);
                    House->Harvested((float)amount,slot);
                    slot=storage->First_Used_Slot();
                }
                unknown_slot60();
                Building_Refresh_House_Buildings_0044fa40(House);
                if(Type->CloakGenerator) {
                    unknown_5bb=-1;
                    if(!unknown_5bc) unknown_5bc=Type->CloakRadiusInCells;
                    unknown_75=true;
                    unknown_5bc=1;
                    unknown_slot234(1);
                }
            }
        }
        break;
    }
    return 1;
}
