// ParticleSystemClass::ParticleSystemClass(ParticleSystemTypeClass *type, CoordStruct const &coord, AbstractClass *target, TechnoClass *owner, CoordStruct const &target_coord) (0x0060AA70)
// A new system of a type at a coordinate, aimed at a target object (or a
// plain coordinate), optionally owned by a techno; registered in the system
// list and the 0x00AC0D60 object list.
#include "shared/particle_system.hpp"
#include "shared/map_cell_view.hpp"
#include "shared/techno.hpp"
// @ref ??0ObjectClass@@QAE@XZ=005d22e0
// @ref ?Create_ID@AbstractClass@@UAGXXZ=0040ffd0
// @ref ?As_Techno@AbstractClass@@QAEPAVTechnoClass@@XZ=0040dc20
// @ref ?unknown_slot53@ObjectClass@@UAE_NPBUCoordStruct@@H@Z=005d3890
// @ref _unknown_geometry_j=00a76588
// @ref _unknown_geometry_l=00a76560
// @ref ??_7?$DynamicVectorClass@PAVParticleClass@@@@6B@=007a22a4
// @ref ?ParticleSystems@@3V?$DynamicVectorClass@PAVParticleSystemClass@@@@A=00a32280
// @ref ?unknown_objects_ac0d60@@3V?$DynamicVectorClass@PAVObjectClass@@@@A=00ac0d60
// @ref ??_7ParticleSystemClass@@6BIPersistStream@@@=007a7f8c
// @ref ??_7ParticleSystemClass@@6BIRTTITypeInfo@@@=007a7f70
// @ref ??_7ParticleSystemClass@@6BINoticeSink@@@=007a7f68
// @ref ??_7ParticleSystemClass@@6BINoticeSource@@@=007a7f60

ParticleSystemClass::ParticleSystemClass(ParticleSystemTypeClass *type, CoordStruct const &coord, AbstractClass *target,
                                         TechnoClass *owner, CoordStruct const &target_coord) :
    Class(type),
    unknown_9c(0, 0, 0),
    TargetCoord(unknown_geometry_l),
    Owner(0),
    unknown_d0(0),
    unknown_d4((float)Class->SpawnFrames),
    Lifetime(Class->Lifetime),
    unknown_dc(Class->SparkSpawnFrames),
    unknown_e0(0x1d),
    unknown_e4(false),
    unknown_e5(false)
{
    AbstractClass::Create_ID();
    ParticleSystems.Add(this);
    Particles.Clear();
    if (target != 0) {
        TargetCoord = target->Center_Coord();
        if (Map[target->Center_Coord()].unknown_140 & 0x100) {
            if (target->Kind_Of() == 0xb) {
                TargetCoord.Z += unknown_geometry_j;
            }
        }
    } else {
        TargetCoord = target_coord;
    }
    CoordStruct place(coord.X, coord.Y, coord.Z);
    if (owner != 0) {
        Owner = owner;
        TechnoClass *techno = owner->As_Techno();
        if (techno != 0) {
            unknown_d0 = techno->unknown_228;
        }
    } else {
        Owner = 0;
        unknown_d0 = target;
    }
    ObjectClass::unknown_slot53(&place, 0);
    if (Owner != 0) {
        CoordStruct center = Coord;
        unknown_9c = center - Owner->Center_Coord();
    }
    unknown_objects_ac0d60.Add(this);
}
