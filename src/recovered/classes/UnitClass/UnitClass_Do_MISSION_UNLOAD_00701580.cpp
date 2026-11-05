// Original RTTI vtable79D0CC raw descriptor .?AV?$DynamicVectorClass@PBVParticleSystemTypeClass@@@@ proves const pointee.
// @ref ??_7?$DynamicVectorClass@PBVParticleSystemTypeClass@@@@6B@=0079d0cc
// @ref ??_7?$VectorClass@PBVParticleSystemTypeClass@@@@6B@=0079d0ac
// @ref ??_G?$VectorClass@PBVParticleSystemTypeClass@@@@UAEPAXI@Z=00454710
// @ref ??8?$VectorClass@PBVParticleSystemTypeClass@@@@UBE_NABV0@@Z=00453ed0
// @ref ?Resize@?$VectorClass@PBVParticleSystemTypeClass@@@@UAE_NHPBQBVParticleSystemTypeClass@@@Z=00453f10
// @ref ?Clear@?$VectorClass@PBVParticleSystemTypeClass@@@@UAEXXZ=00453fc0
// @ref ?ID@?$VectorClass@PBVParticleSystemTypeClass@@@@UAEHABQBVParticleSystemTypeClass@@@Z=00453ff0
// @ref ?ID@?$VectorClass@PBVParticleSystemTypeClass@@@@UAEHPBQBVParticleSystemTypeClass@@@Z=00454030
// @ref ?Fetch@?$VectorClass@PBVParticleSystemTypeClass@@@@UBEPBVParticleSystemTypeClass@@H@Z=00453d10
// @ref ??_G?$DynamicVectorClass@PBVParticleSystemTypeClass@@@@UAEPAXI@Z=00454760
// @ref ?Resize@?$DynamicVectorClass@PBVParticleSystemTypeClass@@@@UAE_NHPBQBVParticleSystemTypeClass@@@Z=00454050
// @ref ?Clear@?$DynamicVectorClass@PBVParticleSystemTypeClass@@@@UAEXXZ=00453cc0
// @ref ?ID@?$DynamicVectorClass@PBVParticleSystemTypeClass@@@@UAEHABQBVParticleSystemTypeClass@@@Z=00454100
// @ref ?ID@?$DynamicVectorClass@PBVParticleSystemTypeClass@@@@UAEHPBQBVParticleSystemTypeClass@@@Z=00453cf0
// Do_MISSION_UNLOAD (TibSun unit.cpp): passengers leave a transport, harvesters dump at the refinery, MCVs deploy.
#include "shared/unit.hpp"
#include "shared/building_type_class.hpp"
#include "shared/house.hpp"
#include "shared/map_view.hpp"
#include "shared/cell.hpp"
#include "shared/team.hpp"
#include "shared/particle_system.hpp"
#include "shared/id_source.hpp"
#include "shared/house_adjacent.hpp"
extern Cell const unknown_cell_ad0488;
extern CoordStruct const unknown_coord_ad04c0;
// @ref ?unknown_cell_ad0488@@=00ad0488
// @ref ?unknown_coord_ad04c0@@=00ad04c0

int UnitClass::unknown_slot137()
{
    Cell cell;
    if (Type->Passengers>0) {
        switch (unknown_a8) {
            case 0: {
                if (Locomotor.Checked()->Is_Moving()) return 10;
                Cell current=unknown_slot104();
                CellClass &current_cell=Map[current];
                if (!unknown_494 && current_cell.unknown_ec==2) {
                    Cell destination=Map.Unknown_005502E0(unknown_slot104(),2,-1,0,false,Point2D(1,1),0,0,0,1,Cell(0,0),0);
                    unknown_slot260(&Map[destination],1);
                    return 10;
                }
                int passengers=Cargo.Count;
                int facing=unknown_slot182(0,&cell);
                if (passengers && cell!=unknown_cell_ad0488) {
                    if (unknown_6d83e0()) {
                        if (passengers==1) unknown_5cc=0;
                        else unknown_5cc=1;
                    }
                    UnknownFacingDir direction((unsigned short)(facing<<13));
                    Locomotor.Checked()->Do_Turn(direction);
                    unknown_a8=1;
                    return 1;
                }
                unknown_slot116(5,false);
                break;
            }
            case 1:
            if (!unknown_599) { unknown_a8=3;return 1; }
            break;
            case 3:
            if (Cargo.Count>unknown_5cc) {
                FootClass *passenger=unknown_4ccfc0();
                if (passenger) {
                    UnknownFacingDir opposite((unsigned short)(unknown_2e0.Current().Raw+0x7fff));
                    int attempt=0;
                    int start=((*(unsigned const *)&opposite>>12)+1)>>1;
                    bool prefer_far=true;
                    bool placed=false;
                    for (;attempt<8;++attempt) {
                        int facing=(start+attempt)&7;
                        Cell near_cell=Adjacent_Cell(unknown_slot104(),(FacingType)facing);
                        Cell far_cell=Adjacent_Cell(near_cell,(FacingType)facing);
                        bool far_allowed=passenger->unknown_slot101(&Map[far_cell],facing,unknown_5d47d0(),0,1)==0;
                        bool near_allowed=passenger->unknown_slot101(&Map[near_cell],facing,unknown_5d47d0(),0,1)==0;
                        if (!near_allowed || (!far_allowed && prefer_far)) {
                            if (prefer_far && attempt+1==8) { attempt=0;prefer_far=false; }
                            continue;
                        }
                        if (Map[near_cell].unknown_140&0x100) continue;
                        ++unknown_a40774;
                        CoordStruct position=Cell_Coord(near_cell);
                        position=Map.Unknown_0049CB70(position,false);
                        UnknownFacingDir direction((unsigned short)(facing<<13));
                        placed=passenger->unknown_slot53(&position,Dir_To_256(direction));
                        --unknown_a40774;
                        if (placed) {
                            passenger->unknown_slot116(2,false);
                            if (prefer_far) passenger->unknown_slot260(&Map[far_cell],1);
                            else passenger->unknown_slot260(&Map[near_cell],1);
                            if (Team) Team->unknown_func_6b8cc0(passenger);
                        }
                        break;
                    }
                    if (!placed) { Cargo.Unknown_00468960(passenger);passenger->unknown_slot69(); }
                }
            } else unknown_a8=4;
            break;
            case 4:
            unknown_slot116(5,false);
            unknown_a4=true;
            break;
        }
        int delay=Control()->Normal_Delay();
        return delay+Random_Pick(0,2);
    }
    if (!Type->Harvester && !Type->Weeder) {
        if (Type->DeploysInto) {
            switch (unknown_a8) {
                case 2:
                if (!unknown_57c) {
                    unknown_slot261(false,true);
                    unknown_slot117();
                } else if (!unknown_6fdfc0() && unknown_494) unknown_57c=false;
                break;
                case 0:
                unknown_slot149(3);
                Path[0]=-1;
                unknown_a8=1;
                // Initial setup falls through into the movement check.
                case 1:
                if (!Locomotor.Checked()->Is_Moving()) {
                    unknown_6fdfc0();
                    if (unknown_7d) {
                        if (unknown_57c) unknown_a8=2;
                        else if (!House->Unknown_004F52F0() && unknown_game_mode_a3d298) unknown_slot116(15,false);
                        else unknown_slot116(5,false);
                    }
                } else if (MissionQueue!=-1 && MissionQueue!=16) unknown_slot117();
                break;
                default: break;
            }
        } else {
            if (Type->IsSimpleDeployer) {
                unknown_slot116(5,false);
                unknown_slot117();
            }
            return FootClass::unknown_slot137();
        }
        int delay=Control()->Normal_Delay();
        return delay+Random_Pick(0,2);
    }
    if (!In_Radio_Contact()) {
        unknown_slot261(false,true);
        unknown_5b9=false;
        if (Locomotor.Checked()->Is_Moving()) unknown_slot291();
        if (unknown_slot122()) unknown_slot117();
        return 1;
    }
    int current_dir=Dir_To_256(unknown_2e0.Current());
    if (current_dir!=64) {
        if (!unknown_599) Locomotor.Checked()->Do_Turn(UnknownFacingDir(0x4000));
        return 5;
    }
    if (!unknown_5b9) {
        unknown_5b9=true;
        StageClass::Stage=0;
        StageClass::Set_Rate(1);
        if (Type->Harvester) {
            BuildingClass *building=(BuildingClass *)Map[unknown_slot104()+AdjacentCell[6]].unknown_4717b0();
            if (building) building->unknown_44c920(7,building->Health_Ratio()<=Rules->unknown_1368,false,0);
        }
        unknown_a8=3;
    } else {
        switch (unknown_a8) {
            case 4: {
                if (Type->Weeder) {
                    unknown_5b9=false;
                    if (unknown_494 && MissionQueue!=-1 && MissionQueue!=10) {
                        if (Locomotor.Checked()->Is_Moving()) unknown_slot291();
                        if (unknown_slot122()) unknown_slot117();
                    } else {
                        unknown_slot116(10,false);
                        if (unknown_slot122()) { if (In_Radio_Contact()) unknown_slot149(3);unknown_slot117(); }
                    }
                } else {
                    BuildingClass *building=(BuildingClass *)Map[unknown_slot104()+AdjacentCell[6]].unknown_4717b0();
                    bool active=false;
                    if (building && building->Type->Refinery) active=building->unknown_454[8]!=0;
                    if (active) return 1;
                    unknown_5b9=false;
                    if (unknown_494 && MissionQueue!=-1 && MissionQueue!=10) {
                        if (Locomotor.Checked()->Is_Moving()) unknown_slot291();
                        if (unknown_slot122()) unknown_slot117();
                    } else {
                        unknown_slot116(10,false);
                        if (unknown_slot122()) { if (In_Radio_Contact()) unknown_slot149(3);unknown_slot117(); }
                    }
                }
                break;
            }
            case 3: {
                BuildingClass *building=(BuildingClass *)Map[unknown_slot104()+AdjacentCell[6]].unknown_4717b0();
                if (!building) {
                    if (In_Radio_Contact()) unknown_slot149(3);
                    unknown_slot116(10,true);
                    int delay=Control()->Normal_Delay();
                    return delay+Random_Pick(0,2);
                } else {
                    if (StageClass::Stage>=Rules->HarvesterDumpRate*900.0) {
                        DynamicVectorClass<ParticleSystemTypeClass const *> smoke;
                        for (int n=building->unknown_slot32()->DamageParticleSystems.Count()-1;n>=0;--n) {
                            if (building->unknown_slot32()->DamageParticleSystems[n]->BehavesLike==0) smoke.Add(building->unknown_slot32()->DamageParticleSystems[n]);
                        }
                        if (!building->unknown_25c[5] && smoke.Count()>0 && unknown_slot108()>-10) {
                            TechnoTypeClass *type=building->unknown_slot32();
                            CoordStruct &o=type->RefnSmokeOffsetOne; CoordStruct offset=o;
                            building->unknown_25c[5]=new ParticleSystemClass(const_cast<ParticleSystemTypeClass *>(smoke[unknown_id_source_a3d290->Random()(0,smoke.Count()-1)]),building->Position_Coord_004f3f40()+offset,0,building,unknown_coord_ad04c0);
                        }
                        if (!building->unknown_25c[6] && smoke.Count()>0 && unknown_slot108()>-10) {
                            TechnoTypeClass *type=building->unknown_slot32();
                            CoordStruct &o=type->RefnSmokeOffsetTwo; CoordStruct offset=o;
                            building->unknown_25c[6]=new ParticleSystemClass(const_cast<ParticleSystemTypeClass *>(smoke[unknown_id_source_a3d290->Random()(0,smoke.Count()-1)]),building->Position_Coord_004f3f40()+offset,0,building,unknown_coord_ad04c0);
                        }
                        if (!building->unknown_454[10]) building->unknown_44c920(10,building->Health_Ratio()<=Rules->unknown_1368,false,0);
                        int slot=unknown_294.First_Used_Slot();
                        HouseClass *owner=building->Owning_House();
                        int purifiers=owner->unknown_52cc;
                        if (owner->Power_Fraction()<1.0) purifiers=0;
                        if (!owner->unknown_134 && unknown_game_mode_a3d298!=0) purifiers+=Rules->AIVirtualPurifiers[owner->unknown_c8];
                        float amount=slot!=-1 ? unknown_294.Get_Amount(slot) : 0.0f;
                        float bonus=(float)purifiers*Rules->PurifierBonus*amount;
                        float removed;
                        if (slot!=-1 && (removed=unknown_294.Remove_Amount(amount,slot))>0.0f) {
                            if (Type->Weeder) {
                                House->Place_Tiberium((int)removed,slot);
                                StageClass::Stage=0;
                            } else {
                                owner->Harvested(removed,slot);
                                if (bonus>0.0f) owner->Harvested(bonus,slot);
                                StageClass::Stage=0;
                            }
                        } else {
                            if (building->Type->Refinery) building->unknown_44c920(8,building->Health_Ratio()<=Rules->unknown_1368,false,0);
                            unknown_a8=4;
                            if (building->unknown_25c[5]) building->unknown_25c[5]->unknown_slot60();
                            if (building->unknown_25c[6]) building->unknown_25c[6]->unknown_slot60();
                            if (building->unknown_454[10]) building->unknown_44cfd0(10);
                        }
                    }
                    if (unknown_494 && MissionQueue!=-1 && MissionQueue!=10) {
                        if (building->Type->Refinery) building->unknown_44c920(8,building->Health_Ratio()<=Rules->unknown_1368,false,0);
                        unknown_a8=4;
                        if (building->unknown_25c[5]) building->unknown_25c[5]->unknown_slot60();
                        if (building->unknown_25c[6]) building->unknown_25c[6]->unknown_slot60();
                        if (building->unknown_454[10]) building->unknown_44cfd0(10);
                    }
                    return 1;
                }

                break;
            }
            default: break;
        }
    }
    int delay=Control()->Normal_Delay();
    return delay+Random_Pick(0,2);
}
