// VoxelAnimTypeClass::VoxelAnimTypeClass(char const *ini_name) (0x0070E1A0)
// Default voxel animation values, then registration in the 0x00AC0CB0 list
// and the voxel animation type list.
// Assumptions: the 0x00AC0CB0 list is declared as an ObjectClass list in
// shared/object.hpp (element type unknown; it also holds types).
#include "shared/voxel_anim_type.hpp"
// @ref ??0ObjectTypeClass@@QAE@PBD@Z=005d57f0
// @ref ?Create_ID@AbstractClass@@UAGXXZ=0040ffd0
// @ref ?unknown_objects_ac0cb0@@3V?$DynamicVectorClass@PAVAbstractClass@@@@A=00ac0cb0
// @ref ?VoxelAnimTypes@@3V?$DynamicVectorClass@PAVVoxelAnimTypeClass@@@@A=00a40ae0
// @ref ??_7VoxelAnimTypeClass@@6BIPersistStream@@@=007ae640
// @ref ??_7VoxelAnimTypeClass@@6BIRTTITypeInfo@@@=007ae624
// @ref ??_7VoxelAnimTypeClass@@6BINoticeSink@@@=007ae61c
// @ref ??_7VoxelAnimTypeClass@@6BINoticeSource@@@=007ae614

VoxelAnimTypeClass::VoxelAnimTypeClass(char const *ini_name) :
    ObjectTypeClass(ini_name),
    Normalized(false),
    Translucent(false),
    unknown_266(false),
    VoxelIndex(0),
    Duration(30),
    Elasticity(.8f),
    MinAngularVelocity(0),
    MaxAngularVelocity(10.0 * 3.1415 / 180.0),
    MinZVel(3.5),
    MaxZVel(5.0),
    MaxXYVel(15.0),
    IsMeteor(false),
    Spawns(0),
    SpawnCount(0),
    StartSound(-1),
    StopSound(-1),
    BounceAnim(0),
    ExpireAnim(0),
    TrailerAnim(0),
    Damage(0),
    DamageRadius(0),
    Warhead(0),
    AttachedSystem(0),
    IsTiberium(false)
{
    AbstractClass::Create_ID();
    unknown_201 = false;
    unknown_204 = true;
    unknown_1ff = true;
    unknown_200 = true;
    unknown_202 = true;
    unknown_203 = true;
    unknown_205 = false;
    unknown_objects_ac0cb0.Add(this);
    VoxelAnimTypes.Add(this);
}
