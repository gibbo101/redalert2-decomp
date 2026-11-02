// @ref ??0?$VectorClass@PBVParticleSystemTypeClass@@@@QAE@IPBQBVParticleSystemTypeClass@@@Z=00454ad0
// Complete Building destruction 0043E270; private evidenced slot286 signature hypothesis.
#include "shared/building.hpp"
#include "shared/gscreen.hpp"
#include "shared/building_map.hpp"
#include "shared/house.hpp"
#include "shared/cell.hpp"
#include "shared/rules.hpp"
#include "shared/id_source.hpp"
#include "shared/anim.hpp"
#include "shared/anim_type.hpp"
#include "shared/smudge_type.hpp"
#include "shared/overlay_type.hpp"
#include "shared/particle_system.hpp"
inline CoordStruct Position_Coord_00450950(ObjectClass const &object);
// Existing coordinate-scatter ABI, declared here without the unrelated full Bullet class.
CoordStruct __fastcall Coord_Scatter(CoordStruct const &coord,int distance,bool lock);
// Original491880: ECX hidden result, EDX input coordinate, one stack-facing argument, RET4.
CoordStruct __fastcall Destruction_Adjacent_Coord_00491880(CoordStruct const &coord,int facing);
extern "C" char *__cdecl strncpy(char *,char const *,unsigned);
class Leaf_482e00 { public: void get(); }; // Existing accepted empty original member; receiver unused.
extern int const Destruction_Facings_007cf660[4];
extern char const Destruction_Fire_Name_007cf7b8[];
extern CoordStruct const Destruction_No_Coord_0084ed30;
// @ref ?Destruction_Adjacent_Coord_00491880@@=00491880
// @ref ?get@Leaf_482e00@@QAEXXZ=00482e00
// @ref ?Destruction_Facings_007cf660@@=007cf660
// @ref ?Destruction_Fire_Name_007cf7b8@@=007cf7b8
// @ref ?Destruction_No_Coord_0084ed30@@=0084ed30
// @ref ??_7?$DynamicVectorClass@PBVParticleSystemTypeClass@@@@6B@=0079d0cc
// @ref ??_7?$VectorClass@PBVParticleSystemTypeClass@@@@6B@=0079d0ac
// Private source hypothesis: a world-coordinate constructor over the shared three-int layout.
struct DestructionCellCoordinate_0043e270 : CoordStruct {
    DestructionCellCoordinate_0043e270(Cell const &cell,int z=0)
        : CoordStruct((int)cell.X*256+128,(int)cell.Y*256+128,z) {}
};
// The original unit has one const-particle vector construction, calling454AD0.
// This declaration is paired with the complete original-bounded specialization later in the plan.
// @ref ??_E?$VectorClass@PBVParticleSystemTypeClass@@@@UAEPAXI@Z=00454710
// @ref ??8?$VectorClass@PBVParticleSystemTypeClass@@@@UBE_NABV0@@Z=00453ed0
// @ref ?Resize@?$VectorClass@PBVParticleSystemTypeClass@@@@UAE_NHPBQBVParticleSystemTypeClass@@@Z=00453f10
// @ref ?Clear@?$VectorClass@PBVParticleSystemTypeClass@@@@UAEXXZ=00453fc0
// @ref ?ID@?$VectorClass@PBVParticleSystemTypeClass@@@@UAEHABQBVParticleSystemTypeClass@@@Z=00453ff0
// @ref ?ID@?$VectorClass@PBVParticleSystemTypeClass@@@@UAEHPBQBVParticleSystemTypeClass@@@Z=00454030
// @ref ?Fetch@?$VectorClass@PBVParticleSystemTypeClass@@@@UBEPBVParticleSystemTypeClass@@H@Z=00453d10
// @ref ??0?$VectorClass@PBVParticleSystemTypeClass@@@@QAE@IPBQBVParticleSystemTypeClass@@@Z=00454ad0
// VectorClass<const ParticleSystemTypeClass*> constructor00454AD0: real complete body.
#include "shared/particle_system.hpp"
// @ref ??_7?$VectorClass@PBVParticleSystemTypeClass@@@@6B@=0079d0ac
// Original Building interval438500..454CF0 has one dynamic-vector installation79D0CC,
// immediately after its only base-ctor call43E9BA->454AD0. Other79D0AC uses are destructors.
// WORKER original-never-inline exception, restricted to this actual constructor specialization.
#pragma auto_inline(off)
template <> VectorClass<ParticleSystemTypeClass const *>::VectorClass(unsigned size,ParticleSystemTypeClass const * const *array)
    : Vector(0),VectorMax(size),IsValid(true),IsAllocated(false)
{
    typedef ParticleSystemTypeClass const *Element;
    if (size) {
        if (array) Vector=new ((void *)array) Element[size];
        else { Vector=new Element[size]; IsAllocated=true; }
    }
}
#pragma auto_inline(on)

// Above is a complete auxiliary duplicate of canonical454AD0, zero new-byte credit.
void BuildingClass::unknown_slot286(TechnoClass *last_contact,TechnoClass *source,bool forced,Cell const *offset)
{
    unknown_6d3040(source);
    for (int index=0;index<8;++index) {
        if (unknown_49c[index]) {
            unknown_49c[index]->unknown_slot60();
            unknown_49c[index]=0;
        }
    }
    if (unknown_1a8) {
        unknown_1a8=0;
        if (Type->Radar) unknown_44ab00();
    }
    if (Type->CloakGenerator) {
        unknown_5bb=-1;
        if (unknown_5bc==0) unknown_5bc=Type->CloakRadiusInCells;
        unknown_75=true;
        unknown_5bc=1;
        unknown_slot234(1);
    }
    if (Type->LaserFencePost) unknown_44dc40(true);
    if (unknown_slot32()->DieSound.Count()==0) Voc_Static_Add(Rules->BuildingDieSound,Position_Coord_00450950(*this),0);
    if (Type->Width()>=2 && Type->Foundation_Height(false)>=2) {
        if (Type->Width()>2) Random_Pick(0,Type->Width()-2);
        if (Type->Foundation_Height(false)>2) Random_Pick(0,Type->Foundation_Height(false)-2);
        if (Random_Pick(0,99)<50) SmudgeTypeClass::Create_Scorch(DestructionCellCoordinate_0043e270(Cell(Position_Coord_00450950(*this))),100,100,true);
        else SmudgeTypeClass::Create_Crater(DestructionCellCoordinate_0043e270(Cell(Position_Coord_00450950(*this))),100,100,true);
    }
    while (*offset!=Cell(32767,32767)) {
        CoordStruct position;
        CoordStruct height_offset(0,0,0);
        Cell const *current=offset++;
        Cell cell=Cell(unknown_slot42())+*current;
        if (Type->Explosion.Count()>0) {
            height_offset.Z=Position_Coord_00450950(*this).Z;
            position=height_offset+Coord_Scatter(DestructionCellCoordinate_0043e270(cell),64,false);
            new AnimClass(Type->Explosion.Pick(unknown_id_source_a3d290->Random()()),position,Random_Pick(0,3),1,0x600,0);
        }
    }
    if (Type->Explodes) {
        for (int index=0;index<4;++index) {
            CoordStruct coord=Destruction_Adjacent_Coord_00491880(Position_Coord_00450950(*this),Destruction_Facings_007cf660[index]);
            if (Map[coord].OverlayIndex!=-1 && OverlayTypes[Map[coord].OverlayIndex]->Explodes) {
                new AnimClass(AnimTypes[AnimTypeClass::From_Name(Destruction_Fire_Name_007cf7b8)],coord,Random_Pick(1,3)+3,1,0x600,0);
            }
        }
    }
    while (unknown_294.Get_Total_Amount()>=1.0f) {
        int type=unknown_294.First_Used_Slot();
        unknown_294.Remove_Amount(1.0f,type);
        House->Tiberium.Remove_Amount(1.0f,type);
        CoordStruct coord=Coord_Scatter(Position_Coord_00450950(*this),Random_Pick(256,768),true);
        Map[coord].unknown_47c3a0(type, 1);
    }
    int shakes=Type->unknown_slot33((int)House)/Rules->unknown_4e8;
    if (shakes>0) ((Leaf_482e00 *)shakes)->get();
    if (unknown_slot91()==19 || Type->Explodes) {
        unknown_420=CDTimerClass<FrameTimerClass>(0);
        StageClass::Set_Rate(0);
    } else unknown_420=CDTimerClass<FrameTimerClass>(8);
    if (Type->DestroyAnim.Count()>0) {
        AnimTypeClass *type=Type->DestroyAnim.Pick(unknown_id_source_a3d290->Random()());
        if (type) {
            AnimClass *animation=new AnimClass(type,unknown_slot42(),0,1,0x600,0);
            if (unknown_slot32()->Palette) {
                animation->unknown_bc=unknown_slot115();
                if (Type->PaletteFile.Buffer[0]) strncpy(animation->Palette.Buffer,Type->PaletteFile.Buffer,32);
            }
        }
    }
    // Original RTTI79D0CC: DynamicVectorClass<const ParticleSystemTypeClass *>.
    DynamicVectorClass<ParticleSystemTypeClass const *> systems;
    for (int system_index=unknown_slot32()->DestroyParticleSystems.Count()-1;system_index>=0;--system_index) {
        if (unknown_slot32()->DestroyParticleSystems[system_index]->BehavesLike==0) {
            systems.Add(unknown_slot32()->DestroyParticleSystems[system_index]);
        }
    }
    // Existing eight-pointer view: the last slot is the destruction particle system at+278.
    if (!unknown_25c[7] && systems.Count()>0 && unknown_slot108()>-10) {
        TechnoTypeClass *type=unknown_slot32();
        UnknownCoord434820 smoke_offset(type->DestroySmokeOffset);
        unknown_25c[7]=new ParticleSystemClass(const_cast<ParticleSystemTypeClass *>(systems[Random_Pick(0,systems.Count()-1)]),Position_Coord_00450950(*this)+smoke_offset,0,this,Destruction_No_Coord_0084ed30);
    }
    Strength=0;
    if (forced) unknown_5b0=true;
    Spawn_Survivors_0043f8e0(static_cast<ObjectClass *>(unknown_438));
}

// Actual original dynamic-vector79D0CC slot bindings; auxiliary duplicates, zero new credit.
// @ref ??_E?$DynamicVectorClass@PBVParticleSystemTypeClass@@@@UAEPAXI@Z=00454760
// @ref ??8?$VectorClass@PBVParticleSystemTypeClass@@@@UBE_NABV0@@Z=00453ed0
// @ref ?Resize@?$DynamicVectorClass@PBVParticleSystemTypeClass@@@@UAE_NHPBQBVParticleSystemTypeClass@@@Z=00454050
// @ref ?Clear@?$DynamicVectorClass@PBVParticleSystemTypeClass@@@@UAEXXZ=00453cc0
// @ref ?ID@?$DynamicVectorClass@PBVParticleSystemTypeClass@@@@UAEHABQBVParticleSystemTypeClass@@@Z=00454100
// @ref ?ID@?$DynamicVectorClass@PBVParticleSystemTypeClass@@@@UAEHPBQBVParticleSystemTypeClass@@@Z=00453cf0
// @ref ?Fetch@?$VectorClass@PBVParticleSystemTypeClass@@@@UBEPBVParticleSystemTypeClass@@H@Z=00453d10
