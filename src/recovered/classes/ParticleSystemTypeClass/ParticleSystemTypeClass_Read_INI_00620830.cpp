// bool ParticleSystemTypeClass::Read_INI(CCINIClass &ini) (0x00620830)
// The object keys, then the particle system keys: the particle type it
// holds (made when missing), spawn timing and limits, BehavesLike= by
// name (Smoke, Gas, Fire, Spark, Railgun; -1 when unknown), the spawn
// direction and perturbation coefficients, and the laser and light keys.
#include "shared/particle_system.hpp"
#include "shared/ccini_class.hpp"
// @ref ?Read_INI@ObjectTypeClass@@UAE_NAAVCCINIClass@@@Z=005d7810
// @ref ?ParticleTypeClass_Index_Or_Make_621960@@YIHPBD@Z=00621960
// @ref ?unknown_behaves_like_names_7ebfd8@@3PAPBDA=007ebfd8
// @ref ?Get_Float_Triple@CCINIClass@@QAE?AUINIVector3@@PBD0ABU2@@Z=0046b780
// @ref ?Get_RGB@CCINIClass@@QBE?AVRGBClass@@PBD0ABV2@@Z=0046a010
// @ref __stricmp=00781f20
// @ref ??_C@_05HLNJ@Laser?$AA@=007ec08c
// @ref ??_C@_06BMBE@Spawns?$AA@=007cee70
// @ref ??_C@_08IBDG@Lifetime?$AA@=007ec148
// @ref ??_C@_08LEOA@Slowdown?$AA@=007ec178
// @ref ??_C@_09NKGP@HoldsWhat?$AA@=007ec1a8
// @ref ??_C@_09NPHL@LightSize?$AA@=007ec060
// @ref ??_C@_0BB@KNPJ@SparkSpawnFrames?$AA@=007ec06c
// @ref ??_C@_0BC@LGDL@ParticlesPerCoord?$AA@=007ec118
// @ref ??_C@_0BE@MGHE@SpiralDeltaPerCoord?$AA@=007ec104
// @ref ??_C@_0BF@MDNO@SpawnSparkPercentage?$AA@=007ec038
// @ref ??_C@_0BI@COGJ@SpawnTranslucencyCutoff?$AA@=007ec154
// @ref ??_C@_0CA@ELOF@MovementPerturbationCoefficient?$AA@=007ec0b4
// @ref ??_C@_0CA@JJNP@VelocityPerturbationCoefficient?$AA@=007ec094
// @ref ??_C@_0CA@LGMN@PositionPerturbationCoefficient?$AA@=007ec0d4
// @ref ??_C@_0L@MKLI@LaserColor?$AA@=007ec080
// @ref ??_C@_0M@BHFL@SpawnFrames?$AA@=007ec19c
// @ref ??_C@_0M@CAMN@BehavesLike?$AA@=007ec13c
// @ref ??_C@_0M@GHND@SpawnCutoff?$AA@=007ec16c
// @ref ??_C@_0M@GLAK@SpawnRadius?$AA@=007ec184
// @ref ??_C@_0M@JCCE@ParticleCap?$AA@=007ec190
// @ref ??_C@_0N@BHNN@SpiralRadius?$AA@=007ec0f4
// @ref ??_C@_0O@ELOP@OneFrameLight?$AA@=007ec050
// @ref ??_C@_0P@MDNJ@SpawnDirection?$AA@=007ec12c

// The index of the named particle type, made when missing; -1 for
// "<none>" (0x00621960, __fastcall; ParticleType.cpp).
int __fastcall ParticleTypeClass_Index_Or_Make_621960(char const *name);

// The behaviour names in BehavesLike order (0x007EBFD8).
extern char const *unknown_behaves_like_names_7ebfd8[5];

// The behaviour with this name, or -1.
static inline int Behaves_From_Name(char const *name)
{
    for (int index = 0; index < 5; index++) {
        if (_stricmp(name, unknown_behaves_like_names_7ebfd8[index]) == 0) {
            return index;
        }
    }
    return -1;
}

bool ParticleSystemTypeClass::Read_INI(CCINIClass &ini)
{
    if (ObjectTypeClass::Read_INI(ini)) {
        char buffer[64];
        ini.Get_String(ID, "HoldsWhat", unknown_string_83c55c, buffer, sizeof(buffer));
        HoldsWhat = ParticleTypeClass_Index_Or_Make_621960(buffer);
        Spawns = ini.Get_Bool(ID, "Spawns", Spawns);
        SpawnFrames = ini.Get_Int(ID, "SpawnFrames", SpawnFrames);
        ParticleCap = ini.Get_Int(ID, "ParticleCap", ParticleCap);
        SpawnRadius = ini.Get_Int(ID, "SpawnRadius", SpawnRadius);
        Slowdown = ini.Get_Double(ID, "Slowdown", Slowdown);
        SpawnCutoff = ini.Get_Double(ID, "SpawnCutoff", SpawnCutoff);
        SpawnTranslucencyCutoff = ini.Get_Double(ID, "SpawnTranslucencyCutoff", SpawnTranslucencyCutoff);
        Lifetime = ini.Get_Int(ID, "Lifetime", Lifetime);
        ini.Get_String(ID, "BehavesLike", unknown_string_83c55c, buffer, sizeof(buffer));
        BehavesLike = Behaves_From_Name(buffer);
        SpawnDirection = ini.Get_Float_Triple(ID, "SpawnDirection", SpawnDirection);
        ParticlesPerCoord = ini.Get_Double(ID, "ParticlesPerCoord", ParticlesPerCoord);
        SpiralDeltaPerCoord = ini.Get_Double(ID, "SpiralDeltaPerCoord", SpiralDeltaPerCoord);
        SpiralRadius = ini.Get_Double(ID, "SpiralRadius", SpiralRadius);
        PositionPerturbationCoefficient = ini.Get_Double(ID, "PositionPerturbationCoefficient", PositionPerturbationCoefficient);
        MovementPerturbationCoefficient = ini.Get_Double(ID, "MovementPerturbationCoefficient", MovementPerturbationCoefficient);
        VelocityPerturbationCoefficient = ini.Get_Double(ID, "VelocityPerturbationCoefficient", VelocityPerturbationCoefficient);
        Laser = ini.Get_Bool(ID, "Laser", Laser);
        LaserColor = ini.Get_RGB(ID, "LaserColor", LaserColor);
        SparkSpawnFrames = ini.Get_Int(ID, "SparkSpawnFrames", SparkSpawnFrames);
        LightSize = ini.Get_Int(ID, "LightSize", LightSize);
        OneFrameLight = ini.Get_Bool(ID, "OneFrameLight", OneFrameLight);
        SpawnSparkPercentage = ini.Get_Double(ID, "SpawnSparkPercentage", SpawnSparkPercentage);
        return true;
    }
    return false;
}
