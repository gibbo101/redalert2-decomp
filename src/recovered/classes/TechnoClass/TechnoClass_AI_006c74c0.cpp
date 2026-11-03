// TechnoClass::AI (slot 23, 0x006C74C0; TibSun techno.cpp TechnoClass::AI): per-tick techno logic:
// veterancy promotion, the draw-behind cell test, friendly-target and range checks, the turret
// charge stage, recoil, self-heal, cloaking, flashing, damage sparks and the EMP recovery.
// Unknown names keep their offsets. Is_Foot is a file-local helper (hypothesis): its stored
// result reproduces the original's spilled flag at the first two foot tests; the EMP test keeps
// the same form written in place.
// The local sparks vector holds const ParticleSystemTypeClass pointers (original RTTI);
// const_cast bridges the existing mutable ParticleSystemClass constructor contract only.
// @ref ??_7?$VectorClass@PBVParticleSystemTypeClass@@@@6B@=0079d0ac
// @ref ??_7?$DynamicVectorClass@PBVParticleSystemTypeClass@@@@6B@=0079d0cc
// @ref ??_E?$VectorClass@PBVParticleSystemTypeClass@@@@UAEPAXI@Z=00454710
// @ref ??_G?$VectorClass@PBVParticleSystemTypeClass@@@@UAEPAXI@Z=00454710
// @ref ??8?$VectorClass@PBVParticleSystemTypeClass@@@@UBE_NABV0@@Z=00453ed0
// @ref ?Resize@?$VectorClass@PBVParticleSystemTypeClass@@@@UAE_NHPBQBVParticleSystemTypeClass@@@Z=00453f10
// @ref ?Clear@?$VectorClass@PBVParticleSystemTypeClass@@@@UAEXXZ=00453fc0
// @ref ?ID@?$VectorClass@PBVParticleSystemTypeClass@@@@UAEHABQBVParticleSystemTypeClass@@@Z=00453ff0
// @ref ?ID@?$VectorClass@PBVParticleSystemTypeClass@@@@UAEHPBQBVParticleSystemTypeClass@@@Z=00454030
// @ref ?Fetch@?$VectorClass@PBVParticleSystemTypeClass@@@@UBEPBVParticleSystemTypeClass@@H@Z=00453d10
// @ref ??_E?$DynamicVectorClass@PBVParticleSystemTypeClass@@@@UAEPAXI@Z=00454760
// @ref ??_G?$DynamicVectorClass@PBVParticleSystemTypeClass@@@@UAEPAXI@Z=00454760
// @ref ?Resize@?$DynamicVectorClass@PBVParticleSystemTypeClass@@@@UAE_NHPBQBVParticleSystemTypeClass@@@Z=00454050
// @ref ?Clear@?$DynamicVectorClass@PBVParticleSystemTypeClass@@@@UAEXXZ=00453cc0
// @ref ?ID@?$DynamicVectorClass@PBVParticleSystemTypeClass@@@@UAEHABQBVParticleSystemTypeClass@@@Z=00454100
// @ref ?ID@?$DynamicVectorClass@PBVParticleSystemTypeClass@@@@UAEHPBQBVParticleSystemTypeClass@@@Z=00453cf0
#include "shared/techno.hpp"
#include "shared/infantry.hpp"
#include "shared/infantry_type.hpp"
#include "shared/building_class.hpp"
#include "shared/building_type_class.hpp"
#include "shared/weapon_type.hpp"
#include "shared/warhead_type.hpp"
#include "shared/house.hpp"
#include "shared/cell.hpp"
#include "shared/map_view.hpp"
#include "shared/particle_system.hpp"
#include "shared/spawn_manager.hpp"
#include "shared/tactical.hpp"
#include "shared/anim.hpp"
#include "shared/rules.hpp"
#include "shared/vox_class.hpp"
namespace seed_00496ce0 { void __fastcall FUN_00496ce0(int timer); }
extern CoordStruct unknown_coord_ac0188;
extern double const unknown_random_scale_79c280;
// @ref ?Process@FlasherClass@@QAE_NXZ=004bbf00
// @ref ?FUN_00496ce0@seed_00496ce0@@YIXH@Z=00496ce0
// @ref ?Damage_Smoke_Offset@TechnoTypeClass@@QBE?AUCoordStruct@@XZ=006df6c0
// @ref ??_C@_0BB@KGAO@EVA_UnitPromoted?$AA@=007f7140
// @ref ?unknown_random_scale_79c280@@3NB=0079c280
// @ref ?unknown_coord_ac0188@@3UCoordStruct@@A=00ac0188
static inline bool Is_Foot(AbstractClass const *object)
{
    bool foot = false;
    if (object) foot = object->AbstractFlags.IsFoot;
    return foot;
}

void TechnoClass::AI()
{
    Point2D point;
    Rect window;
    if (unknown_380) unknown_380=false;
    unknown_6d8820();
    if (unknown_70>Strength) unknown_70=Strength;
    if ((Frame&4) && unknown_70<Strength) {
        if (unknown_70+30<0) unknown_70=-30;
        ++unknown_70;
    }
    if (unknown_slot32()->Turret) {
        if (unknown_3f0) {
        if (unknown_3ec) {
            unknown_3d8.Unknown_00405D50();
            Voc_Play_At(unknown_slot32()->TurretRotateSound,Position_Coord_004f3f40(),&unknown_3d8);
            unknown_3ec=0;
        }
        } else { unknown_3d8.Unknown_00406070(); unknown_3ec=1; }
        Voc_Update_At(Position_Coord_004f3f40(),&unknown_3d8);
    }
    int old_rank=unknown_110;
    if (old_rank!=unknown_118.unknown_713440()) {
        if (old_rank!=-1) {
            if (unknown_118.unknown_713440()==0) {
                if (House->Unknown_004F52B0()) { Voc_Play_At(Rules->UpgradeEliteSound,Position_Coord_004f3f40(),0); Speech_Play_Name("EVA_UnitPromoted",-1,-1); }
                FlashCount=Rules->EliteFlashTimer;
            } else if (unknown_118.unknown_713440()==1 && House->Unknown_004F52B0()) {
                Voc_Play_At(Rules->UpgradeVeteranSound,Position_Coord_004f3f40(),0);
                Speech_Play_Name("EVA_UnitPromoted",-1,-1);
            }
        }
        unknown_110=unknown_118.unknown_713440();
    }
    if (unknown_slot158()) { unknown_slot237(); if (!unknown_7d) return; }
    Cell where(Center_Coord());
    CellClass &cell=Map[where];
    bool draw_behind;
    if (Kind_Of()==6) {
        if (static_cast<BuildingClass *>(this)->Type->CanBeHidden) draw_behind=cell.unknown_100>1;
        else draw_behind=false;
    } else draw_behind=cell.unknown_100!=0;
    if (draw_behind && !(this && Kind_Of()==2)) {
        unknown_6d9080(point,&window);
    } else if (unknown_108) {
        if (Kind_Of()!=6) unknown_abstracts_ac0bf8.Delete(this);
        unknown_108->unknown_slot60();
        unknown_108=0;
    }
    if (!House->unknown_func_4f52f0() && unknown_228 && House->Is_Ally(static_cast<ObjectClass *>(unknown_228))) {
        bool infantry=Kind_Of()==15;
        bool building=unknown_228->Kind_Of()==6;
        bool can_enter=infantry && building && static_cast<BuildingClass *>(unknown_228)->Unknown_00452EB0(this);
        bool engineer=infantry && static_cast<InfantryClass *>(this)->Type->Engineer;
        bool assault=unknown_slot231(1)->WeaponType && unknown_slot231(1)->WeaponType->Warhead->ElectricAssault && building && static_cast<BuildingClass *>(unknown_228)->Type->Overpowerable;
        if (!engineer && !assault && !can_enter) unknown_slot220(0);
    }
    if ((int)Frame%16==0 && Mission!=8 && Mission!=17) {
        int fire_error=unknown_slot217(unknown_228,unknown_slot174(unknown_228));
        if (unknown_228 && (fire_error==5 || fire_error==6)) unknown_slot220(0);
    }
    if (unknown_slot32()->TurretRecoil) { unknown_330.unknown_6d8bc0(); unknown_350.unknown_6d8bc0(); }
    if (unknown_slot32()->IsChargeTurret && unknown_slot32()->Has_Turret_Weapons()) {
        int turret=0;
        if (unknown_250>0) {
            turret=unknown_slot32()->TurretCount*unknown_244.Value()/unknown_250;
            if (turret>=unknown_slot32()->TurretCount) turret=unknown_slot32()->TurretCount-1;
            else if (turret<0) turret=0;
        }
        unknown_100=turret;
    }
    if (unknown_2a8.Is_Complete_00496AD0()) seed_00496ce0::FUN_00496ce0(reinterpret_cast<int>(&unknown_2a8));
    if (unknown_376) --unknown_376;
    if (unknown_228 && unknown_404) {
        if (Mission==0 || Mission==7 || Mission==13 || Mission==14 || Mission==16 || Mission==18 || Mission==19 || Mission==20 || Mission==22 || Mission==23 || Mission==28 || Mission==24) unknown_slot220(0);
    }
    MissionClass::AI();
    if (unknown_148.Value()==0) {
        if (unknown_slot276()) {
            unknown_slot278();
        } else if ((Mission==2 || Mission==10 || Mission==5) && unknown_6d4180()) {
            unknown_3f4=Frame;
            AbstractClass *target=unknown_228;
            CoordStruct coord=Coord;
            if (unknown_slot209(&coord,1) && unknown_228!=target) unknown_404=true;
        }
    }
    if (unknown_38 && unknown_38->Unknown_00436070()) unknown_38->Unknown_00435D30();
    if (!unknown_7d) return;
    if (unknown_slot157()) {
        ++Strength;
        if ((Health_Ratio()>Rules->unknown_1368 || unknown_slot108()<-10) && unknown_25c[3]) unknown_25c[3]->unknown_slot60();
    }
    unknown_slot234(0);
    if (SpawnManager) SpawnManager->AI();
    if (unknown_1b8==0 && Map[Center_Coord()].Is_House_Bit(House->ArrayIndex)) unknown_slot238();
    if (unknown_1b8==2 && !Map[Center_Coord()].Is_House_Bit(House->ArrayIndex)) unknown_slot238();
    if (unknown_game_mode_a3d298==0 && !House->Unknown_004F52B0() && unknown_228 && !House->Is_Ally(static_cast<ObjectClass *>(unknown_228)) && unknown_6c16f0(-1)<0) unknown_slot220(0);
    if (unknown_228 && unknown_game_mode_a3d298!=0 && House->unknown_134 && unknown_6c16f0(-1)<0 && !House->Is_Ally(static_cast<ObjectClass *>(unknown_228))) unknown_slot220(0);
    if (unknown_228 && unknown_228->Kind_Of()==2) {
        ObjectClass *aircraft=static_cast<ObjectClass *>(unknown_228);
        if (Kind_Of()==1 && unknown_6c16f0(-1)<0 && (aircraft->unknown_slot108()>0 || Map[aircraft->Position_Coord_004f3f40()].unknown_4717b0())) unknown_slot220(0);
    }
    if (Kind_Of()!=2 && unknown_228 && !unknown_slot156()) {
        FootClass *foot=0;
        if (Is_Foot(this)) foot=static_cast<FootClass *>(this);
        if (!foot || !foot->unknown_494) {
            if (!unknown_slot169(unknown_228)) {
                if (Is_Foot(this)) foot->unknown_slot304();
                if (!foot || !foot->unknown_494) {
                    int primary=unknown_slot174(unknown_228);
                    if (!unknown_slot212(unknown_228,primary)) unknown_slot220(0);
                }
            }
        }
    }
    if (Kind_Of()!=6) StageClass::Graphic_Logic();
    unsigned old_flash=FlashCount;
    bool was_flash_on=(old_flash&2)==2;
    if (FlasherClass::Process()) unknown_slot71(2);
    if (old_flash && old_flash!=FlashCount && Kind_Of()==6 && was_flash_on!=((FlashCount&2)==2)) {
        unknown_tactical_83996c->Register_Dirty_Area(unknown_slot73(),false);
        static_cast<BuildingClass *>(this)->unknown_44d190();
    }
    TechnoTypeClass const *type=unknown_slot32();
    if (type->unknown_a9b && Health_Ratio()<Rules->unknown_1368 && unknown_slot108()>-10) {
        DynamicVectorClass<ParticleSystemTypeClass const *> sparks;
        for (int i=0;i<type->DamageParticleSystems.Count();++i) {
            if (type->DamageParticleSystems[i]->BehavesLike==3) sparks.Add(type->DamageParticleSystems[i]);
        }
        if (!unknown_25c[1] && sparks.Count()>0) {
            double probability=Health_Ratio()<Rules->unknown_1370 ? Rules->ConditionRedSparkingProbability:Rules->ConditionYellowSparkingProbability;
            if (double(unknown_id_source_a3d290->Random()(0,0x7ffffffe))*unknown_random_scale_79c280<probability) {
                unknown_25c[1]=new ParticleSystemClass(const_cast<ParticleSystemTypeClass *>(sparks[unknown_id_source_a3d290->Random()(0,sparks.Count()-1)]),unknown_slot32()->Damage_Smoke_Offset()+Center_Coord(),0,this,unknown_coord_ac0188);
            }
        }
    }
    unknown_slot267(false);
    if (unknown_3fc>0 && --unknown_3fc==0) {
        if (Kind_Of()==6) {
            BuildingClass *building=static_cast<BuildingClass *>(this);
            if (building && !building->Type->InvisibleInGame) { building->unknown_44d600(); if (building->Type->Radar) House->unknown_5669=true; }
        } else {
            bool is_foot=false;
            if (this) is_foot=AbstractFlags.IsFoot;
            if (is_foot) {
                FootClass *foot=static_cast<FootClass *>(this);
                if (foot->Locomotor) foot->Locomotor.Checked()->Power_On();
                for (int i=0;i<Anims.Count();++i) {
                    AnimClass *anim=Anims[i];
                    if (anim && anim->unknown_b4==this && anim->Class==Rules->unknown_1438) anim->Loops=0;
                }
            }
        }
    }
}