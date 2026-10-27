// bool VoxelAnimTypeClass::Read_INI(CCINIClass &ini) (0x0070E470)
// The object keys, then the voxel animation keys; angular velocities are
// given in degrees. A type that shares the body, turret or barrel voxel of
// another (ShareSource=) borrows that voxel pair; otherwise <image>.VXL is
// loaded as its own voxel.
#include "shared/voxel_anim_type.hpp"
#include "shared/ccini_class.hpp"
#include "shared/anim_type.hpp"
#include "shared/warhead_type.hpp"
#include "shared/cc_file_class.hpp"
// @ref ??_C@_0L@CMEP@Elasticity?$AA@=007cee8c
// @ref ?Read_INI@ObjectTypeClass@@UAE_NAAVCCINIClass@@@Z=005d7810
// @ref ?From_Name@VocClass@@SIHPBD@Z=00714940
// @ref ?Get_Object_Type@CCINIClass@@QAEPAVObjectTypeClass@@PBD0@Z=0046c2f0
// @ref __makepath=007831f0
// @ref ??0UnknownPairFirst@@QAE@PAVFileClass@@H@Z=00719080
// @ref ??1UnknownPairFirst@@QAE@XZ=007190c0
// @ref ??2@YAPAXI@Z=00782017
// @ref ??3@YAXPAX@Z=00781d3b
// @ref ??0CCFileClass@@QAE@PBD@Z=00468f50
// @ref ??_C@_0L@CMEP@Elasticity?$AA@=007cee8c
// @ref ?Find_Or_Make_ParticleSystemType_00620df0@@YIPAVParticleSystemTypeClass@@PBD@Z=00620df0
// @ref __real@8@3ff98ef920b8f5082800=007ae6e0
// @ref ??_C@_04DJPF@?4VXL?$AA@=007cfe60
// @ref ??_C@_06BMBE@Spawns?$AA@=007cee70
// @ref ??_C@_06ILDP@Damage?$AA@=007cef54
// @ref ??_C@_07BBDO@MaxZVel?$AA@=007f94ac
// @ref ??_C@_07HOLF@MinZVel?$AA@=007cee78
// @ref ??_C@_07LOND@Warhead?$AA@=007ced5c
// @ref ??_C@_08CGML@MaxXYVel?$AA@=007cee80
// @ref ??_C@_08IHLE@IsMeteor?$AA@=007cee58
// @ref ??_C@_08ONKA@Duration?$AA@=007f94b4
// @ref ??_C@_09MJBN@StopSound?$AA@=007cedac
// @ref ??_C@_0BA@HCCE@ShareBarrelData?$AA@=007f947c
// @ref ??_C@_0BA@IAFA@ShareTurretData?$AA@=007f948c
// @ref ??_C@_0BD@BMGJ@MaxAngularVelocity?$AA@=007f94c0
// @ref ??_C@_0BD@GFMC@MinAngularVelocity?$AA@=007f94d4
// @ref ??_C@_0L@CLCE@Normalized?$AA@=007cefc8
// @ref ??_C@_0L@DJNP@ExpireAnim?$AA@=007ced94
// @ref ??_C@_0L@JDDE@BounceAnim?$AA@=007ceda0
// @ref ??_C@_0L@LGCP@VoxelIndex?$AA@=007f9470
// @ref ??_C@_0L@MFM@SpawnCount?$AA@=007cee64
// @ref ??_C@_0L@OGNJ@StartSound?$AA@=007cedc0
// @ref ??_C@_0L@PIJE@IsTiberium?$AA@=007ceed0
// @ref ??_C@_0M@EMBH@Translucent?$AA@=007cefbc
// @ref ??_C@_0M@IPI@TrailerAnim?$AA@=007ced88
// @ref ??_C@_0M@KOCN@ShareSource?$AA@=007f9454
// @ref ??_C@_0N@DNBP@DamageRadius?$AA@=007ced64
// @ref ??_C@_0O@MGIB@ShareBodyData?$AA@=007f949c
// @ref ??_C@_0P@FNM@AttachedSystem?$AA@=007f9460
// @ref ??_C@_00A@?$AA@=0083c55c

extern "C" void __cdecl _makepath(char *path, char const *drive, char const *dir, char const *fname, char const *ext);

// Get_Sound: shared/ccini_class.hpp.

static inline AnimTypeClass *Get_Anim(CCINIClass &ini, char const *section, char const *entry, AnimTypeClass *defvalue)
{
    char name[128];
    if (ini.Get_String(section, entry, unknown_string_83c55c, name, sizeof(name))) {
        return AnimTypeClass::Find_Or_Make(name);
    }
    return defvalue;
}

static inline VoxelAnimTypeClass *Get_Voxel_Anim(CCINIClass &ini, char const *section, char const *entry, VoxelAnimTypeClass *defvalue)
{
    char name[128];
    if (ini.Get_String(section, entry, unknown_string_83c55c, name, sizeof(name))) {
        return Find_Or_Make_Type(name, VoxelAnimTypes);
    }
    return defvalue;
}

static inline WarheadTypeClass *Get_Warhead(CCINIClass &ini, char const *section, char const *entry, WarheadTypeClass *defvalue)
{
    char name[128];
    if (ini.Get_String(section, entry, unknown_string_83c55c, name, sizeof(name))) {
        return WarheadTypeClass::Find_Or_Make(name);
    }
    return defvalue;
}

static inline ParticleSystemTypeClass *Get_Particle_System(CCINIClass &ini, char const *section, char const *entry, ParticleSystemTypeClass *defvalue)
{
    char name[128];
    if (ini.Get_String(section, entry, unknown_string_83c55c, name, sizeof(name))) {
        return Find_Or_Make_ParticleSystemType_00620df0(name);
    }
    return defvalue;
}

bool VoxelAnimTypeClass::Read_INI(CCINIClass &ini)
{
    if (ObjectTypeClass::Read_INI(ini)) {
        Normalized = ini.Get_Bool(ID, "Normalized", Normalized);
        Translucent = ini.Get_Bool(ID, "Translucent", Translucent);
        IsTiberium = ini.Get_Bool(ID, "IsTiberium", IsTiberium);
        IsMeteor = ini.Get_Bool(ID, "IsMeteor", IsMeteor);
        Elasticity = ini.Get_Double(ID, "Elasticity", Elasticity);
        double velocity = ini.Get_Double(ID, "MinAngularVelocity", -1.0);
        if (velocity != 0.0) {
            MinAngularVelocity = velocity * 0.01745277777777778;
        }
        velocity = ini.Get_Double(ID, "MaxAngularVelocity", -1.0);
        if (velocity != 0.0) {
            MaxAngularVelocity = velocity * 0.01745277777777778;
        }
        Duration = ini.Get_Int(ID, "Duration", Duration);
        MinZVel = ini.Get_Double(ID, "MinZVel", MinZVel);
        MaxZVel = ini.Get_Double(ID, "MaxZVel", MaxZVel);
        MaxXYVel = ini.Get_Double(ID, "MaxXYVel", MaxXYVel);

        Spawns = Get_Voxel_Anim(ini, ID, "Spawns", Spawns);
        SpawnCount = ini.Get_Int(ID, "SpawnCount", SpawnCount);
        bool share_body = ini.Get_Bool(ID, "ShareBodyData", false);
        bool share_turret = ini.Get_Bool(ID, "ShareTurretData", false);
        bool share_barrel = ini.Get_Bool(ID, "ShareBarrelData", false);
        VoxelIndex = ini.Get_Int(ID, "VoxelIndex", VoxelIndex);
        StartSound = Get_Sound(ini, ID, "StartSound", StartSound);
        StopSound = Get_Sound(ini, ID, "StopSound", StopSound);
        BounceAnim = Get_Anim(ini, ID, "BounceAnim", BounceAnim);
        ExpireAnim = Get_Anim(ini, ID, "ExpireAnim", ExpireAnim);
        TrailerAnim = Get_Anim(ini, ID, "TrailerAnim", TrailerAnim);
        Damage = ini.Get_Int(ID, "Damage", Damage);
        DamageRadius = ini.Get_Int(ID, "DamageRadius", DamageRadius);
        Warhead = Get_Warhead(ini, ID, "Warhead", Warhead);
        AttachedSystem = Get_Particle_System(ini, ID, "AttachedSystem", AttachedSystem);

        unknown_266 = share_body || share_barrel || share_turret;
        if (unknown_266) {
            ObjectTypeClass *source = ini.Get_Object_Type(ID, "ShareSource");
            if (source != 0) {
                if (share_body) {
                    unknown_b0.unknown_00 = source->unknown_b0.unknown_00;
                    unknown_b0.unknown_04 = source->unknown_b0.unknown_04;
                    return true;
                }
                if (share_turret) {
                    unknown_b0.unknown_00 = source->unknown_b8.unknown_00;
                    unknown_b0.unknown_04 = source->unknown_b8.unknown_04;
                    return true;
                }
                if (share_barrel) {
                    unknown_b0.unknown_00 = source->unknown_c0.unknown_00;
                    unknown_b0.unknown_04 = source->unknown_c0.unknown_04;
                    return true;
                }
            } else {
                unknown_b0.unknown_00 = 0;
                unknown_b0.unknown_04 = 0;
                return true;
            }
        } else {
            char fullname[512];
            _makepath(fullname, 0, 0, unknown_1c8, ".VXL");
            CCFileClass file(fullname);
            delete unknown_b0.unknown_00;
            unknown_b0.unknown_00 = new UnknownPairFirst(&file);
        }
        return true;
    }
    return false;
}
