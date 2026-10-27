// TechnoTypeClass::TechnoTypeClass(NoInitClass const &noinit) (0x006DA6E0)
// Load path: only members with constructors of their own are set up (the
// particle-system lists, cameo names and recoil timing are rebuilt with
// their default constructors); the type rejoins TechnoTypes once.
#include "shared/techno_type.hpp"
#include "shared/house.hpp"
// @ref ??0ObjectTypeClass@@QAE@ABVNoInitClass@@@Z=005d5a80
// @ref ??0?$DynamicVectorClass@PAVVoxelAnimTypeClass@@@@QAE@ABVNoInitClass@@@Z=006df890
// @ref ??_7?$TypeList@PAVVoxelAnimTypeClass@@@@6B@=007a90f8
// @ref ??0?$DynamicVectorClass@H@@QAE@ABVNoInitClass@@@Z=006df8a0
// @ref ??_7?$TypeList@H@@6B@=0079d9f4
// @ref ??0?$DynamicVectorClass@PAVBuildingTypeClass@@@@QAE@ABVNoInitClass@@@Z=006df8b0
// @ref ??_7?$TypeList@PAVBuildingTypeClass@@@@6B@=007a5e4c
// @ref ??0?$DynamicVectorClass@PAVAnimTypeClass@@@@QAE@ABVNoInitClass@@@Z=0050b250
// @ref ??_7?$TypeList@PAVAnimTypeClass@@@@6B@=007a3b3c
// @ref ??0?$DynamicVectorClass@PAVParticleSystemTypeClass@@@@QAE@IPBQAVParticleSystemTypeClass@@@Z=006df930
// @ref ??_7?$TypeList@PAVParticleSystemTypeClass@@@@6B@=007ad144
// @ref ??_7TechnoTypeClass@@6BIPersistStream@@@=007ad080
// @ref ??_7TechnoTypeClass@@6BIRTTITypeInfo@@@=007ad064
// @ref ??_7TechnoTypeClass@@6BINoticeSink@@@=007ad05c
// @ref ??_7TechnoTypeClass@@6BINoticeSource@@@=007ad054
// @ref ?TechnoTypes@@3V?$DynamicVectorClass@PAVTechnoTypeClass@@@@A=00a40ab8

TechnoTypeClass::TechnoTypeClass(NoInitClass const &noinit) :
    ObjectTypeClass(noinit),
    VeteranAbilities(noinit),
    EliteAbilities(noinit),
    DebrisTypes(noinit),
    DebrisMaximums(noinit),
    unknown_390(0),
    Dock(noinit),
    VoiceSelect(noinit),
    VoiceMove(noinit),
    VoiceAttack(noinit),
    VoiceSpecialAttack(noinit),
    VoiceDie(noinit),
    VoiceFeedback(noinit),
    MoveSound(noinit),
    DieSound(noinit),
    DebrisAnims(noinit),
    Prerequisite(noinit),
    PrerequisiteOverride(noinit),
    Explosion(noinit),
    DestroyAnim(noinit)
{
    for (int index = 0; index < TechnoTypes.Count(); index++) {
        if (TechnoTypes[index] == this) {
            return;
        }
    }
    TechnoTypes.Add(this);
}
