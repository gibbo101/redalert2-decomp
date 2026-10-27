// Header-static dynamic initializers of the unit at 0x004D2BA0 and its
// list globals (AITriggerTypeClass, AbstractTypeClass, AircraftClass, AircraftTypeClass, AnimClass, AnimTypeClass, BuildingClass, BuildingLightClass, BuildingTypeClass, BulletClass, BulletTypeClass, CampaignClass, FactoryClass, HouseClass, HouseTypeClass, InfantryClass, InfantryTypeClass, IsometricTileTypeClass, ObjectClass, OverlayClass, OverlayTypeClass, ParticleClass, ParticleSystemClass, ParticleSystemTypeClass, ParticleTypeClass, ScriptTypeClass, SideClass, SmudgeClass, SmudgeTypeClass, SuperClass, SuperWeaponTypeClass, TaskForceClass, TeamClass, TeamTypeClass, TechnoClass, TechnoTypeClass, TerrainClass, TerrainTypeClass, TriggerClass, TriggerTypeClass, TubeClass, UnitClass, UnitTypeClass, VoxelAnimTypeClass, WaveClass); the other drafts of this plan are emitted by this file.
#include "shared/unknown_geometry.hpp"
#include "shared/unknown_static_rect.hpp"
#ifndef VECTOR_IMPLEMENT_ALL
#define VECTOR_IMPLEMENT_ALL
#endif
#include "shared/vector_class.hpp"

class AITriggerTypeClass;
class TriggerTypeClass;
class TriggerClass;
class BuildingLightClass;
class ParticleSystemClass;
class TubeClass;
class WaveClass;
class BulletClass;
class OverlayClass;
class ParticleClass;
class SmudgeClass;
class TerrainClass;
class InfantryClass;
class BuildingClass;
class AircraftClass;
class UnitClass;
class HouseClass;
class AnimClass;
class TeamClass;
class FactoryClass;
class CampaignClass;
class SideClass;
class HouseTypeClass;
class TaskForceClass;
class TeamTypeClass;
class ScriptTypeClass;
class OverlayTypeClass;
class SmudgeTypeClass;
class TerrainTypeClass;
class BuildingTypeClass;
class AircraftTypeClass;
class UnitTypeClass;
class AnimTypeClass;
class InfantryTypeClass;
class BulletTypeClass;
class VoxelAnimTypeClass;
class IsometricTileTypeClass;
class ParticleTypeClass;
class ParticleSystemTypeClass;
class SuperWeaponTypeClass;
class SuperClass;
class TechnoClass;
class TechnoTypeClass;
class ObjectClass;
class AbstractTypeClass;

// The unit's list of AITriggerTypeClass (0x00A3D260; name is a hypothesis).
DynamicVectorClass<AITriggerTypeClass *> AITriggerTypes;
// The unit's list of TriggerTypeClass (0x00866208; name is a hypothesis).
DynamicVectorClass<TriggerTypeClass *> TriggerTypes;
// The unit's list of TriggerClass (0x00A40AA0; name is a hypothesis).
DynamicVectorClass<TriggerClass *> unknown_TriggerClass_list_00a40aa0;
// The unit's list of BuildingLightClass (0x00866220; name is a hypothesis).
DynamicVectorClass<BuildingLightClass *> BuildingLights;
// The unit's list of ParticleSystemClass (0x00A32280; name is a hypothesis).
DynamicVectorClass<ParticleSystemClass *> ParticleSystems;
// The unit's list of TubeClass (0x008661C8; name is a hypothesis).
DynamicVectorClass<TubeClass *> unknown_TubeClass_list_008661c8;
// The unit's list of WaveClass (0x00A40BE8; name is a hypothesis).
DynamicVectorClass<WaveClass *> Waves;
// The unit's list of BulletClass (0x00A40CE8; name is a hypothesis).
DynamicVectorClass<BulletClass *> unknown_BulletClass_list_00a40ce8;
// The unit's list of OverlayClass (0x00A40C00; name is a hypothesis).
DynamicVectorClass<OverlayClass *> unknown_OverlayClass_list_00a40c00;
// The unit's list of ParticleClass (0x00A35E28; name is a hypothesis).
DynamicVectorClass<ParticleClass *> unknown_ParticleClass_list_00a35e28;
// The unit's list of SmudgeClass (0x00A3D240; name is a hypothesis).
DynamicVectorClass<SmudgeClass *> Smudges;
// The unit's list of TerrainClass (0x00A40940; name is a hypothesis).
DynamicVectorClass<TerrainClass *> Terrains;
// The unit's list of InfantryClass (0x00A35E48; name is a hypothesis).
DynamicVectorClass<InfantryClass *> Infantry;
// The unit's list of BuildingClass (0x00A40AF8; name is a hypothesis).
DynamicVectorClass<BuildingClass *> unknown_BuildingClass_list_00a40af8;
// The unit's list of AircraftClass (0x00A40398; name is a hypothesis).
DynamicVectorClass<AircraftClass *> Aircraft;
// The unit's list of UnitClass (0x00866198; name is a hypothesis).
DynamicVectorClass<UnitClass *> Units;
// The unit's list of HouseClass (0x00A32298; name is a hypothesis).
DynamicVectorClass<HouseClass *> Houses;
// The unit's list of AnimClass (0x00A40960; name is a hypothesis).
DynamicVectorClass<AnimClass *> Anims;
// The unit's list of TeamClass (0x00866178; name is a hypothesis).
DynamicVectorClass<TeamClass *> Teams;
// The unit's list of FactoryClass (0x00A35E90; name is a hypothesis).
DynamicVectorClass<FactoryClass *> Factories;
// The unit's list of CampaignClass (0x00A35D60; name is a hypothesis).
DynamicVectorClass<CampaignClass *> Campaigns;
// The unit's list of SideClass (0x008661B0; name is a hypothesis).
DynamicVectorClass<SideClass *> Sides;
// The unit's list of HouseTypeClass (0x00A35D08; name is a hypothesis).
DynamicVectorClass<HouseTypeClass *> HouseTypes;
// The unit's list of TaskForceClass (0x00A40890; name is a hypothesis).
DynamicVectorClass<TaskForceClass *> TaskForces;
// The unit's list of TeamTypeClass (0x00A40C48; name is a hypothesis).
DynamicVectorClass<TeamTypeClass *> TeamTypes;
// The unit's list of ScriptTypeClass (0x00866258; name is a hypothesis).
DynamicVectorClass<ScriptTypeClass *> ScriptTypes;
// The unit's list of OverlayTypeClass (0x00A35DE8; name is a hypothesis).
DynamicVectorClass<OverlayTypeClass *> OverlayTypes;
// The unit's list of SmudgeTypeClass (0x00A40BC8; name is a hypothesis).
DynamicVectorClass<SmudgeTypeClass *> SmudgeTypes;
// The unit's list of TerrainTypeClass (0x00A40320; name is a hypothesis).
DynamicVectorClass<TerrainTypeClass *> TerrainTypes;
// The unit's list of BuildingTypeClass (0x00A35CD8; name is a hypothesis).
DynamicVectorClass<BuildingTypeClass *> BuildingTypes;
// The unit's list of AircraftTypeClass (0x00A3D278; name is a hypothesis).
DynamicVectorClass<AircraftTypeClass *> AircraftTypes;
// The unit's list of UnitTypeClass (0x00A35D48; name is a hypothesis).
DynamicVectorClass<UnitTypeClass *> UnitTypes;
// The unit's list of AnimTypeClass (0x008661E0; name is a hypothesis).
DynamicVectorClass<AnimTypeClass *> unknown_AnimTypeClass_list_008661e0;
// The unit's list of InfantryTypeClass (0x00A40350; name is a hypothesis).
DynamicVectorClass<InfantryTypeClass *> InfantryTypes;
// The unit's list of BulletTypeClass (0x00A35CF0; name is a hypothesis).
DynamicVectorClass<BulletTypeClass *> BulletTypes;
// The unit's list of VoxelAnimTypeClass (0x00A40AE0; name is a hypothesis).
DynamicVectorClass<VoxelAnimTypeClass *> VoxelAnimTypes;
// The unit's list of IsometricTileTypeClass (0x00A40CD0; name is a hypothesis).
DynamicVectorClass<IsometricTileTypeClass *> IsoTileTypes;
// The unit's list of ParticleTypeClass (0x00A35E00; name is a hypothesis).
DynamicVectorClass<ParticleTypeClass *> ParticleTypes;
// The unit's list of ParticleSystemTypeClass (0x00A35DD0; name is a hypothesis).
DynamicVectorClass<ParticleSystemTypeClass *> ParticleSystemTypes;
// The unit's list of SuperWeaponTypeClass (0x00A40338; name is a hypothesis).
DynamicVectorClass<SuperWeaponTypeClass *> SuperWeaponTypes;
// The unit's list of SuperClass (0x00A35D28; name is a hypothesis).
DynamicVectorClass<SuperClass *> Supers;
// The unit's list of SuperClass (0x00A35DB8; name is a hypothesis).
DynamicVectorClass<SuperClass *> unknown_SuperClass_list_00a35db8;
// The unit's list of TechnoClass (0x00A40C20; name is a hypothesis).
DynamicVectorClass<TechnoClass *> Technos;
// The unit's list of TechnoTypeClass (0x00A40AB8; name is a hypothesis).
DynamicVectorClass<TechnoTypeClass *> TechnoTypes;
// The unit's list of ObjectClass (0x00A40368; name is a hypothesis).
DynamicVectorClass<ObjectClass *> unknown_objects_a40368;
// The unit's list of AbstractTypeClass (0x00A40928; name is a hypothesis).
DynamicVectorClass<AbstractTypeClass *> AbstractTypes;
// The unit's list of AnimClass (0x00A35E60; name is a hypothesis).
DynamicVectorClass<AnimClass *> unknown_AnimClass_list_00a35e60;
// @ref ??3@YAXPAX@Z=00781d3b
// @ref ??8?$VectorClass@PAVAITriggerTypeClass@@@@UBE_NABV0@@Z=004d6030
// @ref ??8?$VectorClass@PAVAbstractTypeClass@@@@UBE_NABV0@@Z=004db990
// @ref ??8?$VectorClass@PAVAircraftClass@@@@UBE_NABV0@@Z=004d7e30
// @ref ??8?$VectorClass@PAVAircraftTypeClass@@@@UBE_NABV0@@Z=004da1d0
// @ref ??8?$VectorClass@PAVAnimClass@@@@UBE_NABV0@@Z=004d8550
// @ref ??8?$VectorClass@PAVAnimTypeClass@@@@UBE_NABV0@@Z=004da690
// @ref ??8?$VectorClass@PAVBuildingClass@@@@UBE_NABV0@@Z=004d5b70
// @ref ??8?$VectorClass@PAVBuildingLightClass@@@@UBE_NABV0@@Z=004d6290
// @ref ??8?$VectorClass@PAVBuildingTypeClass@@@@UBE_NABV0@@Z=004d9f70
// @ref ??8?$VectorClass@PAVBulletClass@@@@UBE_NABV0@@Z=00463fa0
// @ref ??8?$VectorClass@PAVBulletTypeClass@@@@UBE_NABV0@@Z=004dab50
// @ref ??8?$VectorClass@PAVCampaignClass@@@@UBE_NABV0@@Z=004d8a10
// @ref ??8?$VectorClass@PAVFactoryClass@@@@UBE_NABV0@@Z=004d87b0
// @ref ??8?$VectorClass@PAVHouseClass@@@@UBE_NABV0@@Z=004d82f0
// @ref ??8?$VectorClass@PAVHouseTypeClass@@@@UBE_NABV0@@Z=004d8ed0
// @ref ??8?$VectorClass@PAVInfantryClass@@@@UBE_NABV0@@Z=00454130
// @ref ??8?$VectorClass@PAVInfantryTypeClass@@@@UBE_NABV0@@Z=004da8f0
// @ref ??8?$VectorClass@PAVIsometricTileTypeClass@@@@UBE_NABV0@@Z=004db010
// @ref ??8?$VectorClass@PAVObjectClass@@@@UBE_NABV0@@Z=0040cbc0
// @ref ??8?$VectorClass@PAVOverlayClass@@@@UBE_NABV0@@Z=004d7710
// @ref ??8?$VectorClass@PAVOverlayTypeClass@@@@UBE_NABV0@@Z=004d9850
// @ref ??8?$VectorClass@PAVParticleClass@@@@UBE_NABV0@@Z=004d64f0
// @ref ??8?$VectorClass@PAVParticleSystemClass@@@@UBE_NABV0@@Z=004d7250
// @ref ??8?$VectorClass@PAVParticleSystemTypeClass@@@@UBE_NABV0@@Z=004db4d0
// @ref ??8?$VectorClass@PAVParticleTypeClass@@@@UBE_NABV0@@Z=004db270
// @ref ??8?$VectorClass@PAVScriptTypeClass@@@@UBE_NABV0@@Z=004d95f0
// @ref ??8?$VectorClass@PAVSideClass@@@@UBE_NABV0@@Z=004d8c70
// @ref ??8?$VectorClass@PAVSmudgeClass@@@@UBE_NABV0@@Z=004d7970
// @ref ??8?$VectorClass@PAVSmudgeTypeClass@@@@UBE_NABV0@@Z=004d9ab0
// @ref ??8?$VectorClass@PAVSuperClass@@@@UBE_NABV0@@Z=004d5dd0
// @ref ??8?$VectorClass@PAVSuperWeaponTypeClass@@@@UBE_NABV0@@Z=004db730
// @ref ??8?$VectorClass@PAVTaskForceClass@@@@UBE_NABV0@@Z=004d9130
// @ref ??8?$VectorClass@PAVTeamClass@@@@UBE_NABV0@@Z=004d6750
// @ref ??8?$VectorClass@PAVTeamTypeClass@@@@UBE_NABV0@@Z=004d9390
// @ref ??8?$VectorClass@PAVTechnoClass@@@@UBE_NABV0@@Z=0040b870
// @ref ??8?$VectorClass@PAVTechnoTypeClass@@@@UBE_NABV0@@Z=0046d400
// @ref ??8?$VectorClass@PAVTerrainClass@@@@UBE_NABV0@@Z=004d7bd0
// @ref ??8?$VectorClass@PAVTerrainTypeClass@@@@UBE_NABV0@@Z=004d9d10
// @ref ??8?$VectorClass@PAVTriggerClass@@@@UBE_NABV0@@Z=004d6b30
// @ref ??8?$VectorClass@PAVTriggerTypeClass@@@@UBE_NABV0@@Z=004d6d90
// @ref ??8?$VectorClass@PAVTubeClass@@@@UBE_NABV0@@Z=004d6ff0
// @ref ??8?$VectorClass@PAVUnitClass@@@@UBE_NABV0@@Z=004d8090
// @ref ??8?$VectorClass@PAVUnitTypeClass@@@@UBE_NABV0@@Z=004da430
// @ref ??8?$VectorClass@PAVVoxelAnimTypeClass@@@@UBE_NABV0@@Z=004dadb0
// @ref ??8?$VectorClass@PAVWaveClass@@@@UBE_NABV0@@Z=004d74b0
// @ref ??_7?$DynamicVectorClass@PAVAITriggerTypeClass@@@@6B@=007a20a4
// @ref ??_7?$DynamicVectorClass@PAVAbstractTypeClass@@@@6B@=007a2a64
// @ref ??_7?$DynamicVectorClass@PAVAircraftClass@@@@6B@=007a23a4
// @ref ??_7?$DynamicVectorClass@PAVAircraftTypeClass@@@@6B@=007a27a4
// @ref ??_7?$DynamicVectorClass@PAVAnimClass@@@@6B@=007a2464
// @ref ??_7?$DynamicVectorClass@PAVAnimTypeClass@@@@6B@=007a2824
// @ref ??_7?$DynamicVectorClass@PAVBuildingClass@@@@6B@=007a2364
// @ref ??_7?$DynamicVectorClass@PAVBuildingLightClass@@@@6B@=007a2164
// @ref ??_7?$DynamicVectorClass@PAVBuildingTypeClass@@@@6B@=007a2764
// @ref ??_7?$DynamicVectorClass@PAVBulletClass@@@@6B@=0079d308
// @ref ??_7?$DynamicVectorClass@PAVBulletTypeClass@@@@6B@=007a28a4
// @ref ??_7?$DynamicVectorClass@PAVCampaignClass@@@@6B@=007a2524
// @ref ??_7?$DynamicVectorClass@PAVFactoryClass@@@@6B@=007a24e4
// @ref ??_7?$DynamicVectorClass@PAVHouseClass@@@@6B@=007a2424
// @ref ??_7?$DynamicVectorClass@PAVHouseTypeClass@@@@6B@=007a25a4
// @ref ??_7?$DynamicVectorClass@PAVInfantryClass@@@@6B@=0079d054
// @ref ??_7?$DynamicVectorClass@PAVInfantryTypeClass@@@@6B@=007a2864
// @ref ??_7?$DynamicVectorClass@PAVIsometricTileTypeClass@@@@6B@=007a2924
// @ref ??_7?$DynamicVectorClass@PAVObjectClass@@@@6B@=0079db7c
// @ref ??_7?$DynamicVectorClass@PAVOverlayClass@@@@6B@=007a2264
// @ref ??_7?$DynamicVectorClass@PAVOverlayTypeClass@@@@6B@=007a26a4
// @ref ??_7?$DynamicVectorClass@PAVParticleClass@@@@6B@=007a22a4
// @ref ??_7?$DynamicVectorClass@PAVParticleSystemClass@@@@6B@=007a21a4
// @ref ??_7?$DynamicVectorClass@PAVParticleSystemTypeClass@@@@6B@=007a29a4
// @ref ??_7?$DynamicVectorClass@PAVParticleTypeClass@@@@6B@=007a2964
// @ref ??_7?$DynamicVectorClass@PAVScriptTypeClass@@@@6B@=007a2664
// @ref ??_7?$DynamicVectorClass@PAVSideClass@@@@6B@=007a2564
// @ref ??_7?$DynamicVectorClass@PAVSmudgeClass@@@@6B@=007a22e4
// @ref ??_7?$DynamicVectorClass@PAVSmudgeTypeClass@@@@6B@=007a26e4
// @ref ??_7?$DynamicVectorClass@PAVSuperClass@@@@6B@=007a2a24
// @ref ??_7?$DynamicVectorClass@PAVSuperWeaponTypeClass@@@@6B@=007a29e4
// @ref ??_7?$DynamicVectorClass@PAVTaskForceClass@@@@6B@=007a25e4
// @ref ??_7?$DynamicVectorClass@PAVTeamClass@@@@6B@=007a24a4
// @ref ??_7?$DynamicVectorClass@PAVTeamTypeClass@@@@6B@=007a2624
// @ref ??_7?$DynamicVectorClass@PAVTechnoClass@@@@6B@=0079a79c
// @ref ??_7?$DynamicVectorClass@PAVTechnoTypeClass@@@@6B@=007a0b9c
// @ref ??_7?$DynamicVectorClass@PAVTerrainClass@@@@6B@=007a2324
// @ref ??_7?$DynamicVectorClass@PAVTerrainTypeClass@@@@6B@=007a2724
// @ref ??_7?$DynamicVectorClass@PAVTriggerClass@@@@6B@=007a2124
// @ref ??_7?$DynamicVectorClass@PAVTriggerTypeClass@@@@6B@=007a20e4
// @ref ??_7?$DynamicVectorClass@PAVTubeClass@@@@6B@=007a21e4
// @ref ??_7?$DynamicVectorClass@PAVUnitClass@@@@6B@=007a23e4
// @ref ??_7?$DynamicVectorClass@PAVUnitTypeClass@@@@6B@=007a27e4
// @ref ??_7?$DynamicVectorClass@PAVVoxelAnimTypeClass@@@@6B@=007a28e4
// @ref ??_7?$DynamicVectorClass@PAVWaveClass@@@@6B@=007a2224
// @ref ??_7?$VectorClass@PAVAITriggerTypeClass@@@@6B@=007a20c4
// @ref ??_7?$VectorClass@PAVAbstractTypeClass@@@@6B@=007a2a84
// @ref ??_7?$VectorClass@PAVAircraftClass@@@@6B@=007a23c4
// @ref ??_7?$VectorClass@PAVAircraftTypeClass@@@@6B@=007a27c4
// @ref ??_7?$VectorClass@PAVAnimClass@@@@6B@=007a2484
// @ref ??_7?$VectorClass@PAVAnimTypeClass@@@@6B@=007a2844
// @ref ??_7?$VectorClass@PAVBuildingClass@@@@6B@=007a2384
// @ref ??_7?$VectorClass@PAVBuildingLightClass@@@@6B@=007a2184
// @ref ??_7?$VectorClass@PAVBuildingTypeClass@@@@6B@=007a2784
// @ref ??_7?$VectorClass@PAVBulletClass@@@@6B@=0079d328
// @ref ??_7?$VectorClass@PAVBulletTypeClass@@@@6B@=007a28c4
// @ref ??_7?$VectorClass@PAVCampaignClass@@@@6B@=007a2544
// @ref ??_7?$VectorClass@PAVFactoryClass@@@@6B@=007a2504
// @ref ??_7?$VectorClass@PAVHouseClass@@@@6B@=007a2444
// @ref ??_7?$VectorClass@PAVHouseTypeClass@@@@6B@=007a25c4
// @ref ??_7?$VectorClass@PAVInfantryClass@@@@6B@=0079d074
// @ref ??_7?$VectorClass@PAVInfantryTypeClass@@@@6B@=007a2884
// @ref ??_7?$VectorClass@PAVIsometricTileTypeClass@@@@6B@=007a2944
// @ref ??_7?$VectorClass@PAVObjectClass@@@@6B@=0079a91c
// @ref ??_7?$VectorClass@PAVOverlayClass@@@@6B@=007a2284
// @ref ??_7?$VectorClass@PAVOverlayTypeClass@@@@6B@=007a26c4
// @ref ??_7?$VectorClass@PAVParticleClass@@@@6B@=007a22c4
// @ref ??_7?$VectorClass@PAVParticleSystemClass@@@@6B@=007a21c4
// @ref ??_7?$VectorClass@PAVParticleSystemTypeClass@@@@6B@=007a29c4
// @ref ??_7?$VectorClass@PAVParticleTypeClass@@@@6B@=007a2984
// @ref ??_7?$VectorClass@PAVScriptTypeClass@@@@6B@=007a2684
// @ref ??_7?$VectorClass@PAVSideClass@@@@6B@=007a2584
// @ref ??_7?$VectorClass@PAVSmudgeClass@@@@6B@=007a2304
// @ref ??_7?$VectorClass@PAVSmudgeTypeClass@@@@6B@=007a2704
// @ref ??_7?$VectorClass@PAVSuperClass@@@@6B@=007a2a44
// @ref ??_7?$VectorClass@PAVSuperWeaponTypeClass@@@@6B@=007a2a04
// @ref ??_7?$VectorClass@PAVTaskForceClass@@@@6B@=007a2604
// @ref ??_7?$VectorClass@PAVTeamClass@@@@6B@=007a24c4
// @ref ??_7?$VectorClass@PAVTeamTypeClass@@@@6B@=007a2644
// @ref ??_7?$VectorClass@PAVTechnoClass@@@@6B@=0079a7fc
// @ref ??_7?$VectorClass@PAVTechnoTypeClass@@@@6B@=0079da14
// @ref ??_7?$VectorClass@PAVTerrainClass@@@@6B@=007a2344
// @ref ??_7?$VectorClass@PAVTerrainTypeClass@@@@6B@=007a2744
// @ref ??_7?$VectorClass@PAVTriggerClass@@@@6B@=007a2144
// @ref ??_7?$VectorClass@PAVTriggerTypeClass@@@@6B@=007a2104
// @ref ??_7?$VectorClass@PAVTubeClass@@@@6B@=007a2204
// @ref ??_7?$VectorClass@PAVUnitClass@@@@6B@=007a2404
// @ref ??_7?$VectorClass@PAVUnitTypeClass@@@@6B@=007a2804
// @ref ??_7?$VectorClass@PAVVoxelAnimTypeClass@@@@6B@=007a2904
// @ref ??_7?$VectorClass@PAVWaveClass@@@@6B@=007a2244
// @ref ??_G?$DynamicVectorClass@PAVAITriggerTypeClass@@@@UAEPAXI@Z=004dbe20
// @ref ??_G?$DynamicVectorClass@PAVAbstractTypeClass@@@@UAEPAXI@Z=004dd590
// @ref ??_G?$DynamicVectorClass@PAVAircraftClass@@@@UAEPAXI@Z=004dc5f0
// @ref ??_G?$DynamicVectorClass@PAVAircraftTypeClass@@@@UAEPAXI@Z=004dcf50
// @ref ??_G?$DynamicVectorClass@PAVAnimClass@@@@UAEPAXI@Z=004dc7d0
// @ref ??_G?$DynamicVectorClass@PAVAnimTypeClass@@@@UAEPAXI@Z=004dd090
// @ref ??_G?$DynamicVectorClass@PAVBuildingClass@@@@UAEPAXI@Z=004dbce0
// @ref ??_G?$DynamicVectorClass@PAVBuildingLightClass@@@@UAEPAXI@Z=004dbec0
// @ref ??_G?$DynamicVectorClass@PAVBuildingTypeClass@@@@UAEPAXI@Z=004dceb0
// @ref ??_G?$DynamicVectorClass@PAVBulletClass@@@@UAEPAXI@Z=00464250
// @ref ??_G?$DynamicVectorClass@PAVBulletTypeClass@@@@UAEPAXI@Z=004dd1d0
// @ref ??_G?$DynamicVectorClass@PAVCampaignClass@@@@UAEPAXI@Z=004dc910
// @ref ??_G?$DynamicVectorClass@PAVFactoryClass@@@@UAEPAXI@Z=004dc870
// @ref ??_G?$DynamicVectorClass@PAVHouseClass@@@@UAEPAXI@Z=004dc730
// @ref ??_G?$DynamicVectorClass@PAVHouseTypeClass@@@@UAEPAXI@Z=004dca50
// @ref ??_G?$DynamicVectorClass@PAVInfantryClass@@@@UAEPAXI@Z=00454800
// @ref ??_G?$DynamicVectorClass@PAVInfantryTypeClass@@@@UAEPAXI@Z=004dd130
// @ref ??_G?$DynamicVectorClass@PAVIsometricTileTypeClass@@@@UAEPAXI@Z=004dd310
// @ref ??_G?$DynamicVectorClass@PAVObjectClass@@@@UAEPAXI@Z=0047d090
// @ref ??_G?$DynamicVectorClass@PAVOverlayClass@@@@UAEPAXI@Z=004dc410
// @ref ??_G?$DynamicVectorClass@PAVOverlayTypeClass@@@@UAEPAXI@Z=004dccd0
// @ref ??_G?$DynamicVectorClass@PAVParticleClass@@@@UAEPAXI@Z=004dbf60
// @ref ??_G?$DynamicVectorClass@PAVParticleSystemClass@@@@UAEPAXI@Z=004dc2d0
// @ref ??_G?$DynamicVectorClass@PAVParticleSystemTypeClass@@@@UAEPAXI@Z=004dd450
// @ref ??_G?$DynamicVectorClass@PAVParticleTypeClass@@@@UAEPAXI@Z=004dd3b0
// @ref ??_G?$DynamicVectorClass@PAVScriptTypeClass@@@@UAEPAXI@Z=004dcc30
// @ref ??_G?$DynamicVectorClass@PAVSideClass@@@@UAEPAXI@Z=004dc9b0
// @ref ??_G?$DynamicVectorClass@PAVSmudgeClass@@@@UAEPAXI@Z=004dc4b0
// @ref ??_G?$DynamicVectorClass@PAVSmudgeTypeClass@@@@UAEPAXI@Z=004dcd70
// @ref ??_G?$DynamicVectorClass@PAVSuperClass@@@@UAEPAXI@Z=004dbd80
// @ref ??_G?$DynamicVectorClass@PAVSuperWeaponTypeClass@@@@UAEPAXI@Z=004dd4f0
// @ref ??_G?$DynamicVectorClass@PAVTaskForceClass@@@@UAEPAXI@Z=004dcaf0
// @ref ??_G?$DynamicVectorClass@PAVTeamClass@@@@UAEPAXI@Z=004dc000
// @ref ??_G?$DynamicVectorClass@PAVTeamTypeClass@@@@UAEPAXI@Z=004dcb90
// @ref ??_G?$DynamicVectorClass@PAVTechnoClass@@@@UAEPAXI@Z=0040bbc0
// @ref ??_G?$DynamicVectorClass@PAVTechnoTypeClass@@@@UAEPAXI@Z=004aa080
// @ref ??_G?$DynamicVectorClass@PAVTerrainClass@@@@UAEPAXI@Z=004dc550
// @ref ??_G?$DynamicVectorClass@PAVTerrainTypeClass@@@@UAEPAXI@Z=004dce10
// @ref ??_G?$DynamicVectorClass@PAVTriggerClass@@@@UAEPAXI@Z=004dc0f0
// @ref ??_G?$DynamicVectorClass@PAVTriggerTypeClass@@@@UAEPAXI@Z=004dc190
// @ref ??_G?$DynamicVectorClass@PAVTubeClass@@@@UAEPAXI@Z=004dc230
// @ref ??_G?$DynamicVectorClass@PAVUnitClass@@@@UAEPAXI@Z=004dc690
// @ref ??_G?$DynamicVectorClass@PAVUnitTypeClass@@@@UAEPAXI@Z=004dcff0
// @ref ??_G?$DynamicVectorClass@PAVVoxelAnimTypeClass@@@@UAEPAXI@Z=004dd270
// @ref ??_G?$DynamicVectorClass@PAVWaveClass@@@@UAEPAXI@Z=004dc370
// @ref ??_G?$VectorClass@PAVAITriggerTypeClass@@@@UAEPAXI@Z=004dbdd0
// @ref ??_G?$VectorClass@PAVAbstractTypeClass@@@@UAEPAXI@Z=004dd540
// @ref ??_G?$VectorClass@PAVAircraftClass@@@@UAEPAXI@Z=004dc5a0
// @ref ??_G?$VectorClass@PAVAircraftTypeClass@@@@UAEPAXI@Z=004dcf00
// @ref ??_G?$VectorClass@PAVAnimClass@@@@UAEPAXI@Z=004dc780
// @ref ??_G?$VectorClass@PAVAnimTypeClass@@@@UAEPAXI@Z=004dd040
// @ref ??_G?$VectorClass@PAVBuildingClass@@@@UAEPAXI@Z=004dbc90
// @ref ??_G?$VectorClass@PAVBuildingLightClass@@@@UAEPAXI@Z=004dbe70
// @ref ??_G?$VectorClass@PAVBuildingTypeClass@@@@UAEPAXI@Z=004dce60
// @ref ??_G?$VectorClass@PAVBulletClass@@@@UAEPAXI@Z=00464200
// @ref ??_G?$VectorClass@PAVBulletTypeClass@@@@UAEPAXI@Z=004dd180
// @ref ??_G?$VectorClass@PAVCampaignClass@@@@UAEPAXI@Z=004dc8c0
// @ref ??_G?$VectorClass@PAVFactoryClass@@@@UAEPAXI@Z=004dc820
// @ref ??_G?$VectorClass@PAVHouseClass@@@@UAEPAXI@Z=004dc6e0
// @ref ??_G?$VectorClass@PAVHouseTypeClass@@@@UAEPAXI@Z=004dca00
// @ref ??_G?$VectorClass@PAVInfantryClass@@@@UAEPAXI@Z=004547b0
// @ref ??_G?$VectorClass@PAVInfantryTypeClass@@@@UAEPAXI@Z=004dd0e0
// @ref ??_G?$VectorClass@PAVIsometricTileTypeClass@@@@UAEPAXI@Z=004dd2c0
// @ref ??_G?$VectorClass@PAVObjectClass@@@@UAEPAXI@Z=0040ce20
// @ref ??_G?$VectorClass@PAVOverlayClass@@@@UAEPAXI@Z=004dc3c0
// @ref ??_G?$VectorClass@PAVOverlayTypeClass@@@@UAEPAXI@Z=004dcc80
// @ref ??_G?$VectorClass@PAVParticleClass@@@@UAEPAXI@Z=004dbf10
// @ref ??_G?$VectorClass@PAVParticleSystemClass@@@@UAEPAXI@Z=004dc280
// @ref ??_G?$VectorClass@PAVParticleSystemTypeClass@@@@UAEPAXI@Z=004dd400
// @ref ??_G?$VectorClass@PAVParticleTypeClass@@@@UAEPAXI@Z=004dd360
// @ref ??_G?$VectorClass@PAVScriptTypeClass@@@@UAEPAXI@Z=004dcbe0
// @ref ??_G?$VectorClass@PAVSideClass@@@@UAEPAXI@Z=004dc960
// @ref ??_G?$VectorClass@PAVSmudgeClass@@@@UAEPAXI@Z=004dc460
// @ref ??_G?$VectorClass@PAVSmudgeTypeClass@@@@UAEPAXI@Z=004dcd20
// @ref ??_G?$VectorClass@PAVSuperClass@@@@UAEPAXI@Z=004dbd30
// @ref ??_G?$VectorClass@PAVSuperWeaponTypeClass@@@@UAEPAXI@Z=004dd4a0
// @ref ??_G?$VectorClass@PAVTaskForceClass@@@@UAEPAXI@Z=004dcaa0
// @ref ??_G?$VectorClass@PAVTeamClass@@@@UAEPAXI@Z=004dbfb0
// @ref ??_G?$VectorClass@PAVTeamTypeClass@@@@UAEPAXI@Z=004dcb40
// @ref ??_G?$VectorClass@PAVTechnoClass@@@@UAEPAXI@Z=0040bb70
// @ref ??_G?$VectorClass@PAVTechnoTypeClass@@@@UAEPAXI@Z=0046dac0
// @ref ??_G?$VectorClass@PAVTerrainClass@@@@UAEPAXI@Z=004dc500
// @ref ??_G?$VectorClass@PAVTerrainTypeClass@@@@UAEPAXI@Z=004dcdc0
// @ref ??_G?$VectorClass@PAVTriggerClass@@@@UAEPAXI@Z=004dc0a0
// @ref ??_G?$VectorClass@PAVTriggerTypeClass@@@@UAEPAXI@Z=004dc140
// @ref ??_G?$VectorClass@PAVTubeClass@@@@UAEPAXI@Z=004dc1e0
// @ref ??_G?$VectorClass@PAVUnitClass@@@@UAEPAXI@Z=004dc640
// @ref ??_G?$VectorClass@PAVUnitTypeClass@@@@UAEPAXI@Z=004dcfa0
// @ref ??_G?$VectorClass@PAVVoxelAnimTypeClass@@@@UAEPAXI@Z=004dd220
// @ref ??_G?$VectorClass@PAVWaveClass@@@@UAEPAXI@Z=004dc320
// @ref ?AbstractTypes@@3V?$DynamicVectorClass@PAVAbstractTypeClass@@@@A=00a40928
// @ref ?Clear@?$DynamicVectorClass@PAVAITriggerTypeClass@@@@UAEXXZ=004d4ac0
// @ref ?Clear@?$DynamicVectorClass@PAVAbstractTypeClass@@@@UAEXXZ=004d58b0
// @ref ?Clear@?$DynamicVectorClass@PAVAircraftClass@@@@UAEXXZ=004d4f50
// @ref ?Clear@?$DynamicVectorClass@PAVAircraftTypeClass@@@@UAEXXZ=004d54f0
// @ref ?Clear@?$DynamicVectorClass@PAVAnimClass@@@@UAEXXZ=004d5070
// @ref ?Clear@?$DynamicVectorClass@PAVAnimTypeClass@@@@UAEXXZ=004d55b0
// @ref ?Clear@?$DynamicVectorClass@PAVBuildingClass@@@@UAEXXZ=004d4a00
// @ref ?Clear@?$DynamicVectorClass@PAVBuildingLightClass@@@@UAEXXZ=004d4b20
// @ref ?Clear@?$DynamicVectorClass@PAVBuildingTypeClass@@@@UAEXXZ=004d5490
// @ref ?Clear@?$DynamicVectorClass@PAVBulletClass@@@@UAEXXZ=00463f20
// @ref ?Clear@?$DynamicVectorClass@PAVBulletTypeClass@@@@UAEXXZ=004d5670
// @ref ?Clear@?$DynamicVectorClass@PAVCampaignClass@@@@UAEXXZ=004d5130
// @ref ?Clear@?$DynamicVectorClass@PAVFactoryClass@@@@UAEXXZ=004d50d0
// @ref ?Clear@?$DynamicVectorClass@PAVHouseClass@@@@UAEXXZ=004d5010
// @ref ?Clear@?$DynamicVectorClass@PAVHouseTypeClass@@@@UAEXXZ=004d51f0
// @ref ?Clear@?$DynamicVectorClass@PAVInfantryClass@@@@UAEXXZ=00453d20
// @ref ?Clear@?$DynamicVectorClass@PAVInfantryTypeClass@@@@UAEXXZ=004d5610
// @ref ?Clear@?$DynamicVectorClass@PAVIsometricTileTypeClass@@@@UAEXXZ=004d5730
// @ref ?Clear@?$DynamicVectorClass@PAVObjectClass@@@@UAEXXZ=0040cb60
// @ref ?Clear@?$DynamicVectorClass@PAVOverlayClass@@@@UAEXXZ=004d4e30
// @ref ?Clear@?$DynamicVectorClass@PAVOverlayTypeClass@@@@UAEXXZ=004d5370
// @ref ?Clear@?$DynamicVectorClass@PAVParticleClass@@@@UAEXXZ=004d4b80
// @ref ?Clear@?$DynamicVectorClass@PAVParticleSystemClass@@@@UAEXXZ=004d4d70
// @ref ?Clear@?$DynamicVectorClass@PAVParticleSystemTypeClass@@@@UAEXXZ=004d57f0
// @ref ?Clear@?$DynamicVectorClass@PAVParticleTypeClass@@@@UAEXXZ=004d5790
// @ref ?Clear@?$DynamicVectorClass@PAVScriptTypeClass@@@@UAEXXZ=004d5310
// @ref ?Clear@?$DynamicVectorClass@PAVSideClass@@@@UAEXXZ=004d5190
// @ref ?Clear@?$DynamicVectorClass@PAVSmudgeClass@@@@UAEXXZ=004d4e90
// @ref ?Clear@?$DynamicVectorClass@PAVSmudgeTypeClass@@@@UAEXXZ=004d53d0
// @ref ?Clear@?$DynamicVectorClass@PAVSuperClass@@@@UAEXXZ=004d4a60
// @ref ?Clear@?$DynamicVectorClass@PAVSuperWeaponTypeClass@@@@UAEXXZ=004d5850
// @ref ?Clear@?$DynamicVectorClass@PAVTaskForceClass@@@@UAEXXZ=004d5250
// @ref ?Clear@?$DynamicVectorClass@PAVTeamClass@@@@UAEXXZ=004d4be0
// @ref ?Clear@?$DynamicVectorClass@PAVTeamTypeClass@@@@UAEXXZ=004d52b0
// @ref ?Clear@?$DynamicVectorClass@PAVTechnoClass@@@@UAEXXZ=0040b5b0
// @ref ?Clear@?$DynamicVectorClass@PAVTechnoTypeClass@@@@UAEXXZ=0046cce0
// @ref ?Clear@?$DynamicVectorClass@PAVTerrainClass@@@@UAEXXZ=004d4ef0
// @ref ?Clear@?$DynamicVectorClass@PAVTerrainTypeClass@@@@UAEXXZ=004d5430
// @ref ?Clear@?$DynamicVectorClass@PAVTriggerClass@@@@UAEXXZ=004d4c50
// @ref ?Clear@?$DynamicVectorClass@PAVTriggerTypeClass@@@@UAEXXZ=004d4cb0
// @ref ?Clear@?$DynamicVectorClass@PAVTubeClass@@@@UAEXXZ=004d4d10
// @ref ?Clear@?$DynamicVectorClass@PAVUnitClass@@@@UAEXXZ=004d4fb0
// @ref ?Clear@?$DynamicVectorClass@PAVUnitTypeClass@@@@UAEXXZ=004d5550
// @ref ?Clear@?$DynamicVectorClass@PAVVoxelAnimTypeClass@@@@UAEXXZ=004d56d0
// @ref ?Clear@?$DynamicVectorClass@PAVWaveClass@@@@UAEXXZ=004d4dd0
// @ref ?Clear@?$VectorClass@PAVAITriggerTypeClass@@@@UAEXXZ=004d6120
// @ref ?Clear@?$VectorClass@PAVAbstractTypeClass@@@@UAEXXZ=004dba80
// @ref ?Clear@?$VectorClass@PAVAircraftClass@@@@UAEXXZ=004d7f20
// @ref ?Clear@?$VectorClass@PAVAircraftTypeClass@@@@UAEXXZ=004da2c0
// @ref ?Clear@?$VectorClass@PAVAnimClass@@@@UAEXXZ=004d8640
// @ref ?Clear@?$VectorClass@PAVAnimTypeClass@@@@UAEXXZ=004da780
// @ref ?Clear@?$VectorClass@PAVBuildingClass@@@@UAEXXZ=004d5c60
// @ref ?Clear@?$VectorClass@PAVBuildingLightClass@@@@UAEXXZ=004d6380
// @ref ?Clear@?$VectorClass@PAVBuildingTypeClass@@@@UAEXXZ=004da060
// @ref ?Clear@?$VectorClass@PAVBulletClass@@@@UAEXXZ=00464090
// @ref ?Clear@?$VectorClass@PAVBulletTypeClass@@@@UAEXXZ=004dac40
// @ref ?Clear@?$VectorClass@PAVCampaignClass@@@@UAEXXZ=004d8b00
// @ref ?Clear@?$VectorClass@PAVFactoryClass@@@@UAEXXZ=004d88a0
// @ref ?Clear@?$VectorClass@PAVHouseClass@@@@UAEXXZ=004d83e0
// @ref ?Clear@?$VectorClass@PAVHouseTypeClass@@@@UAEXXZ=004d8fc0
// @ref ?Clear@?$VectorClass@PAVInfantryClass@@@@UAEXXZ=00454220
// @ref ?Clear@?$VectorClass@PAVInfantryTypeClass@@@@UAEXXZ=004da9e0
// @ref ?Clear@?$VectorClass@PAVIsometricTileTypeClass@@@@UAEXXZ=004db100
// @ref ?Clear@?$VectorClass@PAVObjectClass@@@@UAEXXZ=0040ccb0
// @ref ?Clear@?$VectorClass@PAVOverlayClass@@@@UAEXXZ=004d7800
// @ref ?Clear@?$VectorClass@PAVOverlayTypeClass@@@@UAEXXZ=004d9940
// @ref ?Clear@?$VectorClass@PAVParticleClass@@@@UAEXXZ=004d65e0
// @ref ?Clear@?$VectorClass@PAVParticleSystemClass@@@@UAEXXZ=004d7340
// @ref ?Clear@?$VectorClass@PAVParticleSystemTypeClass@@@@UAEXXZ=004db5c0
// @ref ?Clear@?$VectorClass@PAVParticleTypeClass@@@@UAEXXZ=004db360
// @ref ?Clear@?$VectorClass@PAVScriptTypeClass@@@@UAEXXZ=004d96e0
// @ref ?Clear@?$VectorClass@PAVSideClass@@@@UAEXXZ=004d8d60
// @ref ?Clear@?$VectorClass@PAVSmudgeClass@@@@UAEXXZ=004d7a60
// @ref ?Clear@?$VectorClass@PAVSmudgeTypeClass@@@@UAEXXZ=004d9ba0
// @ref ?Clear@?$VectorClass@PAVSuperClass@@@@UAEXXZ=004d5ec0
// @ref ?Clear@?$VectorClass@PAVSuperWeaponTypeClass@@@@UAEXXZ=004db820
// @ref ?Clear@?$VectorClass@PAVTaskForceClass@@@@UAEXXZ=004d9220
// @ref ?Clear@?$VectorClass@PAVTeamClass@@@@UAEXXZ=004d6840
// @ref ?Clear@?$VectorClass@PAVTeamTypeClass@@@@UAEXXZ=004d9480
// @ref ?Clear@?$VectorClass@PAVTechnoClass@@@@UAEXXZ=0040b960
// @ref ?Clear@?$VectorClass@PAVTechnoTypeClass@@@@UAEXXZ=0046d4f0
// @ref ?Clear@?$VectorClass@PAVTerrainClass@@@@UAEXXZ=004d7cc0
// @ref ?Clear@?$VectorClass@PAVTerrainTypeClass@@@@UAEXXZ=004d9e00
// @ref ?Clear@?$VectorClass@PAVTriggerClass@@@@UAEXXZ=004d6c20
// @ref ?Clear@?$VectorClass@PAVTriggerTypeClass@@@@UAEXXZ=004d6e80
// @ref ?Clear@?$VectorClass@PAVTubeClass@@@@UAEXXZ=004d70e0
// @ref ?Clear@?$VectorClass@PAVUnitClass@@@@UAEXXZ=004d8180
// @ref ?Clear@?$VectorClass@PAVUnitTypeClass@@@@UAEXXZ=004da520
// @ref ?Clear@?$VectorClass@PAVVoxelAnimTypeClass@@@@UAEXXZ=004daea0
// @ref ?Clear@?$VectorClass@PAVWaveClass@@@@UAEXXZ=004d75a0
// @ref ?Fetch@?$VectorClass@PAVAITriggerTypeClass@@@@UBEPAVAITriggerTypeClass@@H@Z=004d4b10
// @ref ?Fetch@?$VectorClass@PAVAbstractTypeClass@@@@UBEPAVAbstractTypeClass@@H@Z=004d5900
// @ref ?Fetch@?$VectorClass@PAVAircraftClass@@@@UBEPAVAircraftClass@@H@Z=004d4fa0
// @ref ?Fetch@?$VectorClass@PAVAircraftTypeClass@@@@UBEPAVAircraftTypeClass@@H@Z=004d5540
// @ref ?Fetch@?$VectorClass@PAVAnimClass@@@@UBEPAVAnimClass@@H@Z=004d50c0
// @ref ?Fetch@?$VectorClass@PAVAnimTypeClass@@@@UBEPAVAnimTypeClass@@H@Z=004d5600
// @ref ?Fetch@?$VectorClass@PAVBuildingClass@@@@UBEPAVBuildingClass@@H@Z=004d4a50
// @ref ?Fetch@?$VectorClass@PAVBuildingLightClass@@@@UBEPAVBuildingLightClass@@H@Z=004d4b70
// @ref ?Fetch@?$VectorClass@PAVBuildingTypeClass@@@@UBEPAVBuildingTypeClass@@H@Z=004d54e0
// @ref ?Fetch@?$VectorClass@PAVBulletClass@@@@UBEPAVBulletClass@@H@Z=00463f70
// @ref ?Fetch@?$VectorClass@PAVBulletTypeClass@@@@UBEPAVBulletTypeClass@@H@Z=004d56c0
// @ref ?Fetch@?$VectorClass@PAVCampaignClass@@@@UBEPAVCampaignClass@@H@Z=004d5180
// @ref ?Fetch@?$VectorClass@PAVFactoryClass@@@@UBEPAVFactoryClass@@H@Z=004d5120
// @ref ?Fetch@?$VectorClass@PAVHouseClass@@@@UBEPAVHouseClass@@H@Z=004d5060
// @ref ?Fetch@?$VectorClass@PAVHouseTypeClass@@@@UBEPAVHouseTypeClass@@H@Z=004d5240
// @ref ?Fetch@?$VectorClass@PAVInfantryClass@@@@UBEPAVInfantryClass@@H@Z=00453d70
// @ref ?Fetch@?$VectorClass@PAVInfantryTypeClass@@@@UBEPAVInfantryTypeClass@@H@Z=004d5660
// @ref ?Fetch@?$VectorClass@PAVIsometricTileTypeClass@@@@UBEPAVIsometricTileTypeClass@@H@Z=004d5780
// @ref ?Fetch@?$VectorClass@PAVObjectClass@@@@UBEPAVObjectClass@@H@Z=0040cbb0
// @ref ?Fetch@?$VectorClass@PAVOverlayClass@@@@UBEPAVOverlayClass@@H@Z=004d4e80
// @ref ?Fetch@?$VectorClass@PAVOverlayTypeClass@@@@UBEPAVOverlayTypeClass@@H@Z=004d53c0
// @ref ?Fetch@?$VectorClass@PAVParticleClass@@@@UBEPAVParticleClass@@H@Z=004d4bd0
// @ref ?Fetch@?$VectorClass@PAVParticleSystemClass@@@@UBEPAVParticleSystemClass@@H@Z=004d4dc0
// @ref ?Fetch@?$VectorClass@PAVParticleSystemTypeClass@@@@UBEPAVParticleSystemTypeClass@@H@Z=004d5840
// @ref ?Fetch@?$VectorClass@PAVParticleTypeClass@@@@UBEPAVParticleTypeClass@@H@Z=004d57e0
// @ref ?Fetch@?$VectorClass@PAVScriptTypeClass@@@@UBEPAVScriptTypeClass@@H@Z=004d5360
// @ref ?Fetch@?$VectorClass@PAVSideClass@@@@UBEPAVSideClass@@H@Z=004d51e0
// @ref ?Fetch@?$VectorClass@PAVSmudgeClass@@@@UBEPAVSmudgeClass@@H@Z=004d4ee0
// @ref ?Fetch@?$VectorClass@PAVSmudgeTypeClass@@@@UBEPAVSmudgeTypeClass@@H@Z=004d5420
// @ref ?Fetch@?$VectorClass@PAVSuperClass@@@@UBEPAVSuperClass@@H@Z=004d4ab0
// @ref ?Fetch@?$VectorClass@PAVSuperWeaponTypeClass@@@@UBEPAVSuperWeaponTypeClass@@H@Z=004d58a0
// @ref ?Fetch@?$VectorClass@PAVTaskForceClass@@@@UBEPAVTaskForceClass@@H@Z=004d52a0
// @ref ?Fetch@?$VectorClass@PAVTeamClass@@@@UBEPAVTeamClass@@H@Z=004d4c30
// @ref ?Fetch@?$VectorClass@PAVTeamTypeClass@@@@UBEPAVTeamTypeClass@@H@Z=004d5300
// @ref ?Fetch@?$VectorClass@PAVTechnoClass@@@@UBEPAVTechnoClass@@H@Z=0040b600
// @ref ?Fetch@?$VectorClass@PAVTechnoTypeClass@@@@UBEPAVTechnoTypeClass@@H@Z=0046cd30
// @ref ?Fetch@?$VectorClass@PAVTerrainClass@@@@UBEPAVTerrainClass@@H@Z=004d4f40
// @ref ?Fetch@?$VectorClass@PAVTerrainTypeClass@@@@UBEPAVTerrainTypeClass@@H@Z=004d5480
// @ref ?Fetch@?$VectorClass@PAVTriggerClass@@@@UBEPAVTriggerClass@@H@Z=004d4ca0
// @ref ?Fetch@?$VectorClass@PAVTriggerTypeClass@@@@UBEPAVTriggerTypeClass@@H@Z=004d4d00
// @ref ?Fetch@?$VectorClass@PAVTubeClass@@@@UBEPAVTubeClass@@H@Z=004d4d60
// @ref ?Fetch@?$VectorClass@PAVUnitClass@@@@UBEPAVUnitClass@@H@Z=004d5000
// @ref ?Fetch@?$VectorClass@PAVUnitTypeClass@@@@UBEPAVUnitTypeClass@@H@Z=004d55a0
// @ref ?Fetch@?$VectorClass@PAVVoxelAnimTypeClass@@@@UBEPAVVoxelAnimTypeClass@@H@Z=004d5720
// @ref ?Fetch@?$VectorClass@PAVWaveClass@@@@UBEPAVWaveClass@@H@Z=004d4e20
// @ref ?ID@?$DynamicVectorClass@PAVAITriggerTypeClass@@@@UAEHABQAVAITriggerTypeClass@@@Z=004d6260
// @ref ?ID@?$DynamicVectorClass@PAVAITriggerTypeClass@@@@UAEHPBQAVAITriggerTypeClass@@@Z=004d4af0
// @ref ?ID@?$DynamicVectorClass@PAVAbstractTypeClass@@@@UAEHABQAVAbstractTypeClass@@@Z=004dbbc0
// @ref ?ID@?$DynamicVectorClass@PAVAbstractTypeClass@@@@UAEHPBQAVAbstractTypeClass@@@Z=004d58e0
// @ref ?ID@?$DynamicVectorClass@PAVAircraftClass@@@@UAEHABQAVAircraftClass@@@Z=004d8060
// @ref ?ID@?$DynamicVectorClass@PAVAircraftClass@@@@UAEHPBQAVAircraftClass@@@Z=004d4f80
// @ref ?ID@?$DynamicVectorClass@PAVAircraftTypeClass@@@@UAEHABQAVAircraftTypeClass@@@Z=004da400
// @ref ?ID@?$DynamicVectorClass@PAVAircraftTypeClass@@@@UAEHPBQAVAircraftTypeClass@@@Z=004d5520
// @ref ?ID@?$DynamicVectorClass@PAVAnimClass@@@@UAEHABQAVAnimClass@@@Z=004d8780
// @ref ?ID@?$DynamicVectorClass@PAVAnimClass@@@@UAEHPBQAVAnimClass@@@Z=004d50a0
// @ref ?ID@?$DynamicVectorClass@PAVAnimTypeClass@@@@UAEHABQAVAnimTypeClass@@@Z=004da8c0
// @ref ?ID@?$DynamicVectorClass@PAVAnimTypeClass@@@@UAEHPBQAVAnimTypeClass@@@Z=004d55e0
// @ref ?ID@?$DynamicVectorClass@PAVBuildingClass@@@@UAEHABQAVBuildingClass@@@Z=004d5da0
// @ref ?ID@?$DynamicVectorClass@PAVBuildingClass@@@@UAEHPBQAVBuildingClass@@@Z=004d4a30
// @ref ?ID@?$DynamicVectorClass@PAVBuildingLightClass@@@@UAEHABQAVBuildingLightClass@@@Z=004d64c0
// @ref ?ID@?$DynamicVectorClass@PAVBuildingLightClass@@@@UAEHPBQAVBuildingLightClass@@@Z=004d4b50
// @ref ?ID@?$DynamicVectorClass@PAVBuildingTypeClass@@@@UAEHABQAVBuildingTypeClass@@@Z=004da1a0
// @ref ?ID@?$DynamicVectorClass@PAVBuildingTypeClass@@@@UAEHPBQAVBuildingTypeClass@@@Z=004d54c0
// @ref ?ID@?$DynamicVectorClass@PAVBulletClass@@@@UAEHABQAVBulletClass@@@Z=004641d0
// @ref ?ID@?$DynamicVectorClass@PAVBulletClass@@@@UAEHPBQAVBulletClass@@@Z=00463f50
// @ref ?ID@?$DynamicVectorClass@PAVBulletTypeClass@@@@UAEHABQAVBulletTypeClass@@@Z=004dad80
// @ref ?ID@?$DynamicVectorClass@PAVBulletTypeClass@@@@UAEHPBQAVBulletTypeClass@@@Z=004d56a0
// @ref ?ID@?$DynamicVectorClass@PAVCampaignClass@@@@UAEHABQAVCampaignClass@@@Z=004d8c40
// @ref ?ID@?$DynamicVectorClass@PAVCampaignClass@@@@UAEHPBQAVCampaignClass@@@Z=004d5160
// @ref ?ID@?$DynamicVectorClass@PAVFactoryClass@@@@UAEHABQAVFactoryClass@@@Z=004d89e0
// @ref ?ID@?$DynamicVectorClass@PAVFactoryClass@@@@UAEHPBQAVFactoryClass@@@Z=004d5100
// @ref ?ID@?$DynamicVectorClass@PAVHouseClass@@@@UAEHABQAVHouseClass@@@Z=004d8520
// @ref ?ID@?$DynamicVectorClass@PAVHouseClass@@@@UAEHPBQAVHouseClass@@@Z=004d5040
// @ref ?ID@?$DynamicVectorClass@PAVHouseTypeClass@@@@UAEHABQAVHouseTypeClass@@@Z=004d9100
// @ref ?ID@?$DynamicVectorClass@PAVHouseTypeClass@@@@UAEHPBQAVHouseTypeClass@@@Z=004d5220
// @ref ?ID@?$DynamicVectorClass@PAVInfantryClass@@@@UAEHABQAVInfantryClass@@@Z=00454360
// @ref ?ID@?$DynamicVectorClass@PAVInfantryClass@@@@UAEHPBQAVInfantryClass@@@Z=00453d50
// @ref ?ID@?$DynamicVectorClass@PAVInfantryTypeClass@@@@UAEHABQAVInfantryTypeClass@@@Z=004dab20
// @ref ?ID@?$DynamicVectorClass@PAVInfantryTypeClass@@@@UAEHPBQAVInfantryTypeClass@@@Z=004d5640
// @ref ?ID@?$DynamicVectorClass@PAVIsometricTileTypeClass@@@@UAEHABQAVIsometricTileTypeClass@@@Z=004db240
// @ref ?ID@?$DynamicVectorClass@PAVIsometricTileTypeClass@@@@UAEHPBQAVIsometricTileTypeClass@@@Z=004d5760
// @ref ?ID@?$DynamicVectorClass@PAVObjectClass@@@@UAEHABQAVObjectClass@@@Z=0040cdf0
// @ref ?ID@?$DynamicVectorClass@PAVObjectClass@@@@UAEHPBQAVObjectClass@@@Z=0040cb90
// @ref ?ID@?$DynamicVectorClass@PAVOverlayClass@@@@UAEHABQAVOverlayClass@@@Z=004d7940
// @ref ?ID@?$DynamicVectorClass@PAVOverlayClass@@@@UAEHPBQAVOverlayClass@@@Z=004d4e60
// @ref ?ID@?$DynamicVectorClass@PAVOverlayTypeClass@@@@UAEHABQAVOverlayTypeClass@@@Z=004d9a80
// @ref ?ID@?$DynamicVectorClass@PAVOverlayTypeClass@@@@UAEHPBQAVOverlayTypeClass@@@Z=004d53a0
// @ref ?ID@?$DynamicVectorClass@PAVParticleClass@@@@UAEHABQAVParticleClass@@@Z=004d6720
// @ref ?ID@?$DynamicVectorClass@PAVParticleClass@@@@UAEHPBQAVParticleClass@@@Z=004d4bb0
// @ref ?ID@?$DynamicVectorClass@PAVParticleSystemClass@@@@UAEHABQAVParticleSystemClass@@@Z=004d7480
// @ref ?ID@?$DynamicVectorClass@PAVParticleSystemClass@@@@UAEHPBQAVParticleSystemClass@@@Z=004d4da0
// @ref ?ID@?$DynamicVectorClass@PAVParticleSystemTypeClass@@@@UAEHABQAVParticleSystemTypeClass@@@Z=004db700
// @ref ?ID@?$DynamicVectorClass@PAVParticleSystemTypeClass@@@@UAEHPBQAVParticleSystemTypeClass@@@Z=004d5820
// @ref ?ID@?$DynamicVectorClass@PAVParticleTypeClass@@@@UAEHABQAVParticleTypeClass@@@Z=004db4a0
// @ref ?ID@?$DynamicVectorClass@PAVParticleTypeClass@@@@UAEHPBQAVParticleTypeClass@@@Z=004d57c0
// @ref ?ID@?$DynamicVectorClass@PAVScriptTypeClass@@@@UAEHABQAVScriptTypeClass@@@Z=004d9820
// @ref ?ID@?$DynamicVectorClass@PAVScriptTypeClass@@@@UAEHPBQAVScriptTypeClass@@@Z=004d5340
// @ref ?ID@?$DynamicVectorClass@PAVSideClass@@@@UAEHABQAVSideClass@@@Z=004d8ea0
// @ref ?ID@?$DynamicVectorClass@PAVSideClass@@@@UAEHPBQAVSideClass@@@Z=004d51c0
// @ref ?ID@?$DynamicVectorClass@PAVSmudgeClass@@@@UAEHABQAVSmudgeClass@@@Z=004d7ba0
// @ref ?ID@?$DynamicVectorClass@PAVSmudgeClass@@@@UAEHPBQAVSmudgeClass@@@Z=004d4ec0
// @ref ?ID@?$DynamicVectorClass@PAVSmudgeTypeClass@@@@UAEHABQAVSmudgeTypeClass@@@Z=004d9ce0
// @ref ?ID@?$DynamicVectorClass@PAVSmudgeTypeClass@@@@UAEHPBQAVSmudgeTypeClass@@@Z=004d5400
// @ref ?ID@?$DynamicVectorClass@PAVSuperClass@@@@UAEHABQAVSuperClass@@@Z=004d6000
// @ref ?ID@?$DynamicVectorClass@PAVSuperClass@@@@UAEHPBQAVSuperClass@@@Z=004d4a90
// @ref ?ID@?$DynamicVectorClass@PAVSuperWeaponTypeClass@@@@UAEHABQAVSuperWeaponTypeClass@@@Z=004db960
// @ref ?ID@?$DynamicVectorClass@PAVSuperWeaponTypeClass@@@@UAEHPBQAVSuperWeaponTypeClass@@@Z=004d5880
// @ref ?ID@?$DynamicVectorClass@PAVTaskForceClass@@@@UAEHABQAVTaskForceClass@@@Z=004d9360
// @ref ?ID@?$DynamicVectorClass@PAVTaskForceClass@@@@UAEHPBQAVTaskForceClass@@@Z=004d5280
// @ref ?ID@?$DynamicVectorClass@PAVTeamClass@@@@UAEHABQAVTeamClass@@@Z=004d6980
// @ref ?ID@?$DynamicVectorClass@PAVTeamClass@@@@UAEHPBQAVTeamClass@@@Z=004d4c10
// @ref ?ID@?$DynamicVectorClass@PAVTeamTypeClass@@@@UAEHABQAVTeamTypeClass@@@Z=004d95c0
// @ref ?ID@?$DynamicVectorClass@PAVTeamTypeClass@@@@UAEHPBQAVTeamTypeClass@@@Z=004d52e0
// @ref ?ID@?$DynamicVectorClass@PAVTechnoClass@@@@UAEHABQAVTechnoClass@@@Z=0040baa0
// @ref ?ID@?$DynamicVectorClass@PAVTechnoClass@@@@UAEHPBQAVTechnoClass@@@Z=0040b5e0
// @ref ?ID@?$DynamicVectorClass@PAVTechnoTypeClass@@@@UAEHABQAVTechnoTypeClass@@@Z=0046d630
// @ref ?ID@?$DynamicVectorClass@PAVTechnoTypeClass@@@@UAEHPBQAVTechnoTypeClass@@@Z=0046cd10
// @ref ?ID@?$DynamicVectorClass@PAVTerrainClass@@@@UAEHABQAVTerrainClass@@@Z=004d7e00
// @ref ?ID@?$DynamicVectorClass@PAVTerrainClass@@@@UAEHPBQAVTerrainClass@@@Z=004d4f20
// @ref ?ID@?$DynamicVectorClass@PAVTerrainTypeClass@@@@UAEHABQAVTerrainTypeClass@@@Z=004d9f40
// @ref ?ID@?$DynamicVectorClass@PAVTerrainTypeClass@@@@UAEHPBQAVTerrainTypeClass@@@Z=004d5460
// @ref ?ID@?$DynamicVectorClass@PAVTriggerClass@@@@UAEHABQAVTriggerClass@@@Z=004d6d60
// @ref ?ID@?$DynamicVectorClass@PAVTriggerClass@@@@UAEHPBQAVTriggerClass@@@Z=004d4c80
// @ref ?ID@?$DynamicVectorClass@PAVTriggerTypeClass@@@@UAEHABQAVTriggerTypeClass@@@Z=004d6fc0
// @ref ?ID@?$DynamicVectorClass@PAVTriggerTypeClass@@@@UAEHPBQAVTriggerTypeClass@@@Z=004d4ce0
// @ref ?ID@?$DynamicVectorClass@PAVTubeClass@@@@UAEHABQAVTubeClass@@@Z=004d7220
// @ref ?ID@?$DynamicVectorClass@PAVTubeClass@@@@UAEHPBQAVTubeClass@@@Z=004d4d40
// @ref ?ID@?$DynamicVectorClass@PAVUnitClass@@@@UAEHABQAVUnitClass@@@Z=004d82c0
// @ref ?ID@?$DynamicVectorClass@PAVUnitClass@@@@UAEHPBQAVUnitClass@@@Z=004d4fe0
// @ref ?ID@?$DynamicVectorClass@PAVUnitTypeClass@@@@UAEHABQAVUnitTypeClass@@@Z=004da660
// @ref ?ID@?$DynamicVectorClass@PAVUnitTypeClass@@@@UAEHPBQAVUnitTypeClass@@@Z=004d5580
// @ref ?ID@?$DynamicVectorClass@PAVVoxelAnimTypeClass@@@@UAEHABQAVVoxelAnimTypeClass@@@Z=004dafe0
// @ref ?ID@?$DynamicVectorClass@PAVVoxelAnimTypeClass@@@@UAEHPBQAVVoxelAnimTypeClass@@@Z=004d5700
// @ref ?ID@?$DynamicVectorClass@PAVWaveClass@@@@UAEHABQAVWaveClass@@@Z=004d76e0
// @ref ?ID@?$DynamicVectorClass@PAVWaveClass@@@@UAEHPBQAVWaveClass@@@Z=004d4e00
// @ref ?ID@?$VectorClass@PAVAITriggerTypeClass@@@@UAEHABQAVAITriggerTypeClass@@@Z=004d6150
// @ref ?ID@?$VectorClass@PAVAITriggerTypeClass@@@@UAEHPBQAVAITriggerTypeClass@@@Z=004d6190
// @ref ?ID@?$VectorClass@PAVAbstractTypeClass@@@@UAEHABQAVAbstractTypeClass@@@Z=004dbab0
// @ref ?ID@?$VectorClass@PAVAbstractTypeClass@@@@UAEHPBQAVAbstractTypeClass@@@Z=004dbaf0
// @ref ?ID@?$VectorClass@PAVAircraftClass@@@@UAEHABQAVAircraftClass@@@Z=004d7f50
// @ref ?ID@?$VectorClass@PAVAircraftClass@@@@UAEHPBQAVAircraftClass@@@Z=004d7f90
// @ref ?ID@?$VectorClass@PAVAircraftTypeClass@@@@UAEHABQAVAircraftTypeClass@@@Z=004da2f0
// @ref ?ID@?$VectorClass@PAVAircraftTypeClass@@@@UAEHPBQAVAircraftTypeClass@@@Z=004da330
// @ref ?ID@?$VectorClass@PAVAnimClass@@@@UAEHABQAVAnimClass@@@Z=004d8670
// @ref ?ID@?$VectorClass@PAVAnimClass@@@@UAEHPBQAVAnimClass@@@Z=004d86b0
// @ref ?ID@?$VectorClass@PAVAnimTypeClass@@@@UAEHABQAVAnimTypeClass@@@Z=004da7b0
// @ref ?ID@?$VectorClass@PAVAnimTypeClass@@@@UAEHPBQAVAnimTypeClass@@@Z=004da7f0
// @ref ?ID@?$VectorClass@PAVBuildingClass@@@@UAEHABQAVBuildingClass@@@Z=004d5c90
// @ref ?ID@?$VectorClass@PAVBuildingClass@@@@UAEHPBQAVBuildingClass@@@Z=004d5cd0
// @ref ?ID@?$VectorClass@PAVBuildingLightClass@@@@UAEHABQAVBuildingLightClass@@@Z=004d63b0
// @ref ?ID@?$VectorClass@PAVBuildingLightClass@@@@UAEHPBQAVBuildingLightClass@@@Z=004d63f0
// @ref ?ID@?$VectorClass@PAVBuildingTypeClass@@@@UAEHABQAVBuildingTypeClass@@@Z=004da090
// @ref ?ID@?$VectorClass@PAVBuildingTypeClass@@@@UAEHPBQAVBuildingTypeClass@@@Z=004da0d0
// @ref ?ID@?$VectorClass@PAVBulletClass@@@@UAEHABQAVBulletClass@@@Z=004640c0
// @ref ?ID@?$VectorClass@PAVBulletClass@@@@UAEHPBQAVBulletClass@@@Z=00464100
// @ref ?ID@?$VectorClass@PAVBulletTypeClass@@@@UAEHABQAVBulletTypeClass@@@Z=004dac70
// @ref ?ID@?$VectorClass@PAVBulletTypeClass@@@@UAEHPBQAVBulletTypeClass@@@Z=004dacb0
// @ref ?ID@?$VectorClass@PAVCampaignClass@@@@UAEHABQAVCampaignClass@@@Z=004d8b30
// @ref ?ID@?$VectorClass@PAVCampaignClass@@@@UAEHPBQAVCampaignClass@@@Z=004d8b70
// @ref ?ID@?$VectorClass@PAVFactoryClass@@@@UAEHABQAVFactoryClass@@@Z=004d88d0
// @ref ?ID@?$VectorClass@PAVFactoryClass@@@@UAEHPBQAVFactoryClass@@@Z=004d8910
// @ref ?ID@?$VectorClass@PAVHouseClass@@@@UAEHABQAVHouseClass@@@Z=004d8410
// @ref ?ID@?$VectorClass@PAVHouseClass@@@@UAEHPBQAVHouseClass@@@Z=004d8450
// @ref ?ID@?$VectorClass@PAVHouseTypeClass@@@@UAEHABQAVHouseTypeClass@@@Z=004d8ff0
// @ref ?ID@?$VectorClass@PAVHouseTypeClass@@@@UAEHPBQAVHouseTypeClass@@@Z=004d9030
// @ref ?ID@?$VectorClass@PAVInfantryClass@@@@UAEHABQAVInfantryClass@@@Z=00454250
// @ref ?ID@?$VectorClass@PAVInfantryClass@@@@UAEHPBQAVInfantryClass@@@Z=00454290
// @ref ?ID@?$VectorClass@PAVInfantryTypeClass@@@@UAEHABQAVInfantryTypeClass@@@Z=004daa10
// @ref ?ID@?$VectorClass@PAVInfantryTypeClass@@@@UAEHPBQAVInfantryTypeClass@@@Z=004daa50
// @ref ?ID@?$VectorClass@PAVIsometricTileTypeClass@@@@UAEHABQAVIsometricTileTypeClass@@@Z=004db130
// @ref ?ID@?$VectorClass@PAVIsometricTileTypeClass@@@@UAEHPBQAVIsometricTileTypeClass@@@Z=004db170
// @ref ?ID@?$VectorClass@PAVObjectClass@@@@UAEHABQAVObjectClass@@@Z=0040cce0
// @ref ?ID@?$VectorClass@PAVObjectClass@@@@UAEHPBQAVObjectClass@@@Z=0040cd20
// @ref ?ID@?$VectorClass@PAVOverlayClass@@@@UAEHABQAVOverlayClass@@@Z=004d7830
// @ref ?ID@?$VectorClass@PAVOverlayClass@@@@UAEHPBQAVOverlayClass@@@Z=004d7870
// @ref ?ID@?$VectorClass@PAVOverlayTypeClass@@@@UAEHABQAVOverlayTypeClass@@@Z=004d9970
// @ref ?ID@?$VectorClass@PAVOverlayTypeClass@@@@UAEHPBQAVOverlayTypeClass@@@Z=004d99b0
// @ref ?ID@?$VectorClass@PAVParticleClass@@@@UAEHABQAVParticleClass@@@Z=004d6610
// @ref ?ID@?$VectorClass@PAVParticleClass@@@@UAEHPBQAVParticleClass@@@Z=004d6650
// @ref ?ID@?$VectorClass@PAVParticleSystemClass@@@@UAEHABQAVParticleSystemClass@@@Z=004d7370
// @ref ?ID@?$VectorClass@PAVParticleSystemClass@@@@UAEHPBQAVParticleSystemClass@@@Z=004d73b0
// @ref ?ID@?$VectorClass@PAVParticleSystemTypeClass@@@@UAEHABQAVParticleSystemTypeClass@@@Z=004db5f0
// @ref ?ID@?$VectorClass@PAVParticleSystemTypeClass@@@@UAEHPBQAVParticleSystemTypeClass@@@Z=004db630
// @ref ?ID@?$VectorClass@PAVParticleTypeClass@@@@UAEHABQAVParticleTypeClass@@@Z=004db390
// @ref ?ID@?$VectorClass@PAVParticleTypeClass@@@@UAEHPBQAVParticleTypeClass@@@Z=004db3d0
// @ref ?ID@?$VectorClass@PAVScriptTypeClass@@@@UAEHABQAVScriptTypeClass@@@Z=004d9710
// @ref ?ID@?$VectorClass@PAVScriptTypeClass@@@@UAEHPBQAVScriptTypeClass@@@Z=004d9750
// @ref ?ID@?$VectorClass@PAVSideClass@@@@UAEHABQAVSideClass@@@Z=004d8d90
// @ref ?ID@?$VectorClass@PAVSideClass@@@@UAEHPBQAVSideClass@@@Z=004d8dd0
// @ref ?ID@?$VectorClass@PAVSmudgeClass@@@@UAEHABQAVSmudgeClass@@@Z=004d7a90
// @ref ?ID@?$VectorClass@PAVSmudgeClass@@@@UAEHPBQAVSmudgeClass@@@Z=004d7ad0
// @ref ?ID@?$VectorClass@PAVSmudgeTypeClass@@@@UAEHABQAVSmudgeTypeClass@@@Z=004d9bd0
// @ref ?ID@?$VectorClass@PAVSmudgeTypeClass@@@@UAEHPBQAVSmudgeTypeClass@@@Z=004d9c10
// @ref ?ID@?$VectorClass@PAVSuperClass@@@@UAEHABQAVSuperClass@@@Z=004d5ef0
// @ref ?ID@?$VectorClass@PAVSuperClass@@@@UAEHPBQAVSuperClass@@@Z=004d5f30
// @ref ?ID@?$VectorClass@PAVSuperWeaponTypeClass@@@@UAEHABQAVSuperWeaponTypeClass@@@Z=004db850
// @ref ?ID@?$VectorClass@PAVSuperWeaponTypeClass@@@@UAEHPBQAVSuperWeaponTypeClass@@@Z=004db890
// @ref ?ID@?$VectorClass@PAVTaskForceClass@@@@UAEHABQAVTaskForceClass@@@Z=004d9250
// @ref ?ID@?$VectorClass@PAVTaskForceClass@@@@UAEHPBQAVTaskForceClass@@@Z=004d9290
// @ref ?ID@?$VectorClass@PAVTeamClass@@@@UAEHABQAVTeamClass@@@Z=004d6870
// @ref ?ID@?$VectorClass@PAVTeamClass@@@@UAEHPBQAVTeamClass@@@Z=004d68b0
// @ref ?ID@?$VectorClass@PAVTeamTypeClass@@@@UAEHABQAVTeamTypeClass@@@Z=004d94b0
// @ref ?ID@?$VectorClass@PAVTeamTypeClass@@@@UAEHPBQAVTeamTypeClass@@@Z=004d94f0
// @ref ?ID@?$VectorClass@PAVTechnoClass@@@@UAEHABQAVTechnoClass@@@Z=0040b990
// @ref ?ID@?$VectorClass@PAVTechnoClass@@@@UAEHPBQAVTechnoClass@@@Z=0040b9d0
// @ref ?ID@?$VectorClass@PAVTechnoTypeClass@@@@UAEHABQAVTechnoTypeClass@@@Z=0046d520
// @ref ?ID@?$VectorClass@PAVTechnoTypeClass@@@@UAEHPBQAVTechnoTypeClass@@@Z=0046d560
// @ref ?ID@?$VectorClass@PAVTerrainClass@@@@UAEHABQAVTerrainClass@@@Z=004d7cf0
// @ref ?ID@?$VectorClass@PAVTerrainClass@@@@UAEHPBQAVTerrainClass@@@Z=004d7d30
// @ref ?ID@?$VectorClass@PAVTerrainTypeClass@@@@UAEHABQAVTerrainTypeClass@@@Z=004d9e30
// @ref ?ID@?$VectorClass@PAVTerrainTypeClass@@@@UAEHPBQAVTerrainTypeClass@@@Z=004d9e70
// @ref ?ID@?$VectorClass@PAVTriggerClass@@@@UAEHABQAVTriggerClass@@@Z=004d6c50
// @ref ?ID@?$VectorClass@PAVTriggerClass@@@@UAEHPBQAVTriggerClass@@@Z=004d6c90
// @ref ?ID@?$VectorClass@PAVTriggerTypeClass@@@@UAEHABQAVTriggerTypeClass@@@Z=004d6eb0
// @ref ?ID@?$VectorClass@PAVTriggerTypeClass@@@@UAEHPBQAVTriggerTypeClass@@@Z=004d6ef0
// @ref ?ID@?$VectorClass@PAVTubeClass@@@@UAEHABQAVTubeClass@@@Z=004d7110
// @ref ?ID@?$VectorClass@PAVTubeClass@@@@UAEHPBQAVTubeClass@@@Z=004d7150
// @ref ?ID@?$VectorClass@PAVUnitClass@@@@UAEHABQAVUnitClass@@@Z=004d81b0
// @ref ?ID@?$VectorClass@PAVUnitClass@@@@UAEHPBQAVUnitClass@@@Z=004d81f0
// @ref ?ID@?$VectorClass@PAVUnitTypeClass@@@@UAEHABQAVUnitTypeClass@@@Z=004da550
// @ref ?ID@?$VectorClass@PAVUnitTypeClass@@@@UAEHPBQAVUnitTypeClass@@@Z=004da590
// @ref ?ID@?$VectorClass@PAVVoxelAnimTypeClass@@@@UAEHABQAVVoxelAnimTypeClass@@@Z=004daed0
// @ref ?ID@?$VectorClass@PAVVoxelAnimTypeClass@@@@UAEHPBQAVVoxelAnimTypeClass@@@Z=004daf10
// @ref ?ID@?$VectorClass@PAVWaveClass@@@@UAEHABQAVWaveClass@@@Z=004d75d0
// @ref ?ID@?$VectorClass@PAVWaveClass@@@@UAEHPBQAVWaveClass@@@Z=004d7610
// @ref ?Resize@?$DynamicVectorClass@PAVAITriggerTypeClass@@@@UAE_NHPBQAVAITriggerTypeClass@@@Z=004d61b0
// @ref ?Resize@?$DynamicVectorClass@PAVAbstractTypeClass@@@@UAE_NHPBQAVAbstractTypeClass@@@Z=004dbb10
// @ref ?Resize@?$DynamicVectorClass@PAVAircraftClass@@@@UAE_NHPBQAVAircraftClass@@@Z=004d7fb0
// @ref ?Resize@?$DynamicVectorClass@PAVAircraftTypeClass@@@@UAE_NHPBQAVAircraftTypeClass@@@Z=004da350
// @ref ?Resize@?$DynamicVectorClass@PAVAnimClass@@@@UAE_NHPBQAVAnimClass@@@Z=004d86d0
// @ref ?Resize@?$DynamicVectorClass@PAVAnimTypeClass@@@@UAE_NHPBQAVAnimTypeClass@@@Z=004da810
// @ref ?Resize@?$DynamicVectorClass@PAVBuildingClass@@@@UAE_NHPBQAVBuildingClass@@@Z=004d5cf0
// @ref ?Resize@?$DynamicVectorClass@PAVBuildingLightClass@@@@UAE_NHPBQAVBuildingLightClass@@@Z=004d6410
// @ref ?Resize@?$DynamicVectorClass@PAVBuildingTypeClass@@@@UAE_NHPBQAVBuildingTypeClass@@@Z=004da0f0
// @ref ?Resize@?$DynamicVectorClass@PAVBulletClass@@@@UAE_NHPBQAVBulletClass@@@Z=00464120
// @ref ?Resize@?$DynamicVectorClass@PAVBulletTypeClass@@@@UAE_NHPBQAVBulletTypeClass@@@Z=004dacd0
// @ref ?Resize@?$DynamicVectorClass@PAVCampaignClass@@@@UAE_NHPBQAVCampaignClass@@@Z=004d8b90
// @ref ?Resize@?$DynamicVectorClass@PAVFactoryClass@@@@UAE_NHPBQAVFactoryClass@@@Z=004d8930
// @ref ?Resize@?$DynamicVectorClass@PAVHouseClass@@@@UAE_NHPBQAVHouseClass@@@Z=004d8470
// @ref ?Resize@?$DynamicVectorClass@PAVHouseTypeClass@@@@UAE_NHPBQAVHouseTypeClass@@@Z=004d9050
// @ref ?Resize@?$DynamicVectorClass@PAVInfantryClass@@@@UAE_NHPBQAVInfantryClass@@@Z=004542b0
// @ref ?Resize@?$DynamicVectorClass@PAVInfantryTypeClass@@@@UAE_NHPBQAVInfantryTypeClass@@@Z=004daa70
// @ref ?Resize@?$DynamicVectorClass@PAVIsometricTileTypeClass@@@@UAE_NHPBQAVIsometricTileTypeClass@@@Z=004db190
// @ref ?Resize@?$DynamicVectorClass@PAVObjectClass@@@@UAE_NHPBQAVObjectClass@@@Z=0040cd40
// @ref ?Resize@?$DynamicVectorClass@PAVOverlayClass@@@@UAE_NHPBQAVOverlayClass@@@Z=004d7890
// @ref ?Resize@?$DynamicVectorClass@PAVOverlayTypeClass@@@@UAE_NHPBQAVOverlayTypeClass@@@Z=004d99d0
// @ref ?Resize@?$DynamicVectorClass@PAVParticleClass@@@@UAE_NHPBQAVParticleClass@@@Z=004d6670
// @ref ?Resize@?$DynamicVectorClass@PAVParticleSystemClass@@@@UAE_NHPBQAVParticleSystemClass@@@Z=004d73d0
// @ref ?Resize@?$DynamicVectorClass@PAVParticleSystemTypeClass@@@@UAE_NHPBQAVParticleSystemTypeClass@@@Z=004db650
// @ref ?Resize@?$DynamicVectorClass@PAVParticleTypeClass@@@@UAE_NHPBQAVParticleTypeClass@@@Z=004db3f0
// @ref ?Resize@?$DynamicVectorClass@PAVScriptTypeClass@@@@UAE_NHPBQAVScriptTypeClass@@@Z=004d9770
// @ref ?Resize@?$DynamicVectorClass@PAVSideClass@@@@UAE_NHPBQAVSideClass@@@Z=004d8df0
// @ref ?Resize@?$DynamicVectorClass@PAVSmudgeClass@@@@UAE_NHPBQAVSmudgeClass@@@Z=004d7af0
// @ref ?Resize@?$DynamicVectorClass@PAVSmudgeTypeClass@@@@UAE_NHPBQAVSmudgeTypeClass@@@Z=004d9c30
// @ref ?Resize@?$DynamicVectorClass@PAVSuperClass@@@@UAE_NHPBQAVSuperClass@@@Z=004d5f50
// @ref ?Resize@?$DynamicVectorClass@PAVSuperWeaponTypeClass@@@@UAE_NHPBQAVSuperWeaponTypeClass@@@Z=004db8b0
// @ref ?Resize@?$DynamicVectorClass@PAVTaskForceClass@@@@UAE_NHPBQAVTaskForceClass@@@Z=004d92b0
// @ref ?Resize@?$DynamicVectorClass@PAVTeamClass@@@@UAE_NHPBQAVTeamClass@@@Z=004d68d0
// @ref ?Resize@?$DynamicVectorClass@PAVTeamTypeClass@@@@UAE_NHPBQAVTeamTypeClass@@@Z=004d9510
// @ref ?Resize@?$DynamicVectorClass@PAVTechnoClass@@@@UAE_NHPBQAVTechnoClass@@@Z=0040b9f0
// @ref ?Resize@?$DynamicVectorClass@PAVTechnoTypeClass@@@@UAE_NHPBQAVTechnoTypeClass@@@Z=0046d580
// @ref ?Resize@?$DynamicVectorClass@PAVTerrainClass@@@@UAE_NHPBQAVTerrainClass@@@Z=004d7d50
// @ref ?Resize@?$DynamicVectorClass@PAVTerrainTypeClass@@@@UAE_NHPBQAVTerrainTypeClass@@@Z=004d9e90
// @ref ?Resize@?$DynamicVectorClass@PAVTriggerClass@@@@UAE_NHPBQAVTriggerClass@@@Z=004d6cb0
// @ref ?Resize@?$DynamicVectorClass@PAVTriggerTypeClass@@@@UAE_NHPBQAVTriggerTypeClass@@@Z=004d6f10
// @ref ?Resize@?$DynamicVectorClass@PAVTubeClass@@@@UAE_NHPBQAVTubeClass@@@Z=004d7170
// @ref ?Resize@?$DynamicVectorClass@PAVUnitClass@@@@UAE_NHPBQAVUnitClass@@@Z=004d8210
// @ref ?Resize@?$DynamicVectorClass@PAVUnitTypeClass@@@@UAE_NHPBQAVUnitTypeClass@@@Z=004da5b0
// @ref ?Resize@?$DynamicVectorClass@PAVVoxelAnimTypeClass@@@@UAE_NHPBQAVVoxelAnimTypeClass@@@Z=004daf30
// @ref ?Resize@?$DynamicVectorClass@PAVWaveClass@@@@UAE_NHPBQAVWaveClass@@@Z=004d7630
// @ref ?Resize@?$VectorClass@PAVAITriggerTypeClass@@@@UAE_NHPBQAVAITriggerTypeClass@@@Z=004d6070
// @ref ?Resize@?$VectorClass@PAVAbstractTypeClass@@@@UAE_NHPBQAVAbstractTypeClass@@@Z=004db9d0
// @ref ?Resize@?$VectorClass@PAVAircraftClass@@@@UAE_NHPBQAVAircraftClass@@@Z=004d7e70
// @ref ?Resize@?$VectorClass@PAVAircraftTypeClass@@@@UAE_NHPBQAVAircraftTypeClass@@@Z=004da210
// @ref ?Resize@?$VectorClass@PAVAnimClass@@@@UAE_NHPBQAVAnimClass@@@Z=004d8590
// @ref ?Resize@?$VectorClass@PAVAnimTypeClass@@@@UAE_NHPBQAVAnimTypeClass@@@Z=004da6d0
// @ref ?Resize@?$VectorClass@PAVBuildingClass@@@@UAE_NHPBQAVBuildingClass@@@Z=004d5bb0
// @ref ?Resize@?$VectorClass@PAVBuildingLightClass@@@@UAE_NHPBQAVBuildingLightClass@@@Z=004d62d0
// @ref ?Resize@?$VectorClass@PAVBuildingTypeClass@@@@UAE_NHPBQAVBuildingTypeClass@@@Z=004d9fb0
// @ref ?Resize@?$VectorClass@PAVBulletClass@@@@UAE_NHPBQAVBulletClass@@@Z=00463fe0
// @ref ?Resize@?$VectorClass@PAVBulletTypeClass@@@@UAE_NHPBQAVBulletTypeClass@@@Z=004dab90
// @ref ?Resize@?$VectorClass@PAVCampaignClass@@@@UAE_NHPBQAVCampaignClass@@@Z=004d8a50
// @ref ?Resize@?$VectorClass@PAVFactoryClass@@@@UAE_NHPBQAVFactoryClass@@@Z=004d87f0
// @ref ?Resize@?$VectorClass@PAVHouseClass@@@@UAE_NHPBQAVHouseClass@@@Z=004d8330
// @ref ?Resize@?$VectorClass@PAVHouseTypeClass@@@@UAE_NHPBQAVHouseTypeClass@@@Z=004d8f10
// @ref ?Resize@?$VectorClass@PAVInfantryClass@@@@UAE_NHPBQAVInfantryClass@@@Z=00454170
// @ref ?Resize@?$VectorClass@PAVInfantryTypeClass@@@@UAE_NHPBQAVInfantryTypeClass@@@Z=004da930
// @ref ?Resize@?$VectorClass@PAVIsometricTileTypeClass@@@@UAE_NHPBQAVIsometricTileTypeClass@@@Z=004db050
// @ref ?Resize@?$VectorClass@PAVObjectClass@@@@UAE_NHPBQAVObjectClass@@@Z=0040cc00
// @ref ?Resize@?$VectorClass@PAVOverlayClass@@@@UAE_NHPBQAVOverlayClass@@@Z=004d7750
// @ref ?Resize@?$VectorClass@PAVOverlayTypeClass@@@@UAE_NHPBQAVOverlayTypeClass@@@Z=004d9890
// @ref ?Resize@?$VectorClass@PAVParticleClass@@@@UAE_NHPBQAVParticleClass@@@Z=004d6530
// @ref ?Resize@?$VectorClass@PAVParticleSystemClass@@@@UAE_NHPBQAVParticleSystemClass@@@Z=004d7290
// @ref ?Resize@?$VectorClass@PAVParticleSystemTypeClass@@@@UAE_NHPBQAVParticleSystemTypeClass@@@Z=004db510
// @ref ?Resize@?$VectorClass@PAVParticleTypeClass@@@@UAE_NHPBQAVParticleTypeClass@@@Z=004db2b0
// @ref ?Resize@?$VectorClass@PAVScriptTypeClass@@@@UAE_NHPBQAVScriptTypeClass@@@Z=004d9630
// @ref ?Resize@?$VectorClass@PAVSideClass@@@@UAE_NHPBQAVSideClass@@@Z=004d8cb0
// @ref ?Resize@?$VectorClass@PAVSmudgeClass@@@@UAE_NHPBQAVSmudgeClass@@@Z=004d79b0
// @ref ?Resize@?$VectorClass@PAVSmudgeTypeClass@@@@UAE_NHPBQAVSmudgeTypeClass@@@Z=004d9af0
// @ref ?Resize@?$VectorClass@PAVSuperClass@@@@UAE_NHPBQAVSuperClass@@@Z=004d5e10
// @ref ?Resize@?$VectorClass@PAVSuperWeaponTypeClass@@@@UAE_NHPBQAVSuperWeaponTypeClass@@@Z=004db770
// @ref ?Resize@?$VectorClass@PAVTaskForceClass@@@@UAE_NHPBQAVTaskForceClass@@@Z=004d9170
// @ref ?Resize@?$VectorClass@PAVTeamClass@@@@UAE_NHPBQAVTeamClass@@@Z=004d6790
// @ref ?Resize@?$VectorClass@PAVTeamTypeClass@@@@UAE_NHPBQAVTeamTypeClass@@@Z=004d93d0
// @ref ?Resize@?$VectorClass@PAVTechnoClass@@@@UAE_NHPBQAVTechnoClass@@@Z=0040b8b0
// @ref ?Resize@?$VectorClass@PAVTechnoTypeClass@@@@UAE_NHPBQAVTechnoTypeClass@@@Z=0046d440
// @ref ?Resize@?$VectorClass@PAVTerrainClass@@@@UAE_NHPBQAVTerrainClass@@@Z=004d7c10
// @ref ?Resize@?$VectorClass@PAVTerrainTypeClass@@@@UAE_NHPBQAVTerrainTypeClass@@@Z=004d9d50
// @ref ?Resize@?$VectorClass@PAVTriggerClass@@@@UAE_NHPBQAVTriggerClass@@@Z=004d6b70
// @ref ?Resize@?$VectorClass@PAVTriggerTypeClass@@@@UAE_NHPBQAVTriggerTypeClass@@@Z=004d6dd0
// @ref ?Resize@?$VectorClass@PAVTubeClass@@@@UAE_NHPBQAVTubeClass@@@Z=004d7030
// @ref ?Resize@?$VectorClass@PAVUnitClass@@@@UAE_NHPBQAVUnitClass@@@Z=004d80d0
// @ref ?Resize@?$VectorClass@PAVUnitTypeClass@@@@UAE_NHPBQAVUnitTypeClass@@@Z=004da470
// @ref ?Resize@?$VectorClass@PAVVoxelAnimTypeClass@@@@UAE_NHPBQAVVoxelAnimTypeClass@@@Z=004dadf0
// @ref ?Resize@?$VectorClass@PAVWaveClass@@@@UAE_NHPBQAVWaveClass@@@Z=004d74f0
// @ref ?AITriggerTypes@@3V?$DynamicVectorClass@PAVAITriggerTypeClass@@@@A=00a3d260
// @ref ?Aircraft@@3V?$DynamicVectorClass@PAVAircraftClass@@@@A=00a40398
// @ref ?AircraftTypes@@3V?$DynamicVectorClass@PAVAircraftTypeClass@@@@A=00a3d278
// @ref ?unknown_AnimClass_list_00a35e60@@3V?$DynamicVectorClass@PAVAnimClass@@@@A=00a35e60
// @ref ?Anims@@3V?$DynamicVectorClass@PAVAnimClass@@@@A=00a40960
// @ref ?unknown_AnimTypeClass_list_008661e0@@3V?$DynamicVectorClass@PAVAnimTypeClass@@@@A=008661e0
// @ref ?unknown_BuildingClass_list_00a40af8@@3V?$DynamicVectorClass@PAVBuildingClass@@@@A=00a40af8
// @ref ?BuildingLights@@3V?$DynamicVectorClass@PAVBuildingLightClass@@@@A=00866220
// @ref ?BuildingTypes@@3V?$DynamicVectorClass@PAVBuildingTypeClass@@@@A=00a35cd8
// @ref ?unknown_BulletClass_list_00a40ce8@@3V?$DynamicVectorClass@PAVBulletClass@@@@A=00a40ce8
// @ref ?BulletTypes@@3V?$DynamicVectorClass@PAVBulletTypeClass@@@@A=00a35cf0
// @ref ?Campaigns@@3V?$DynamicVectorClass@PAVCampaignClass@@@@A=00a35d60
// @ref ?Factories@@3V?$DynamicVectorClass@PAVFactoryClass@@@@A=00a35e90
// @ref ?Houses@@3V?$DynamicVectorClass@PAVHouseClass@@@@A=00a32298
// @ref ?HouseTypes@@3V?$DynamicVectorClass@PAVHouseTypeClass@@@@A=00a35d08
// @ref ?Infantry@@3V?$DynamicVectorClass@PAVInfantryClass@@@@A=00a35e48
// @ref ?InfantryTypes@@3V?$DynamicVectorClass@PAVInfantryTypeClass@@@@A=00a40350
// @ref ?IsoTileTypes@@3V?$DynamicVectorClass@PAVIsometricTileTypeClass@@@@A=00a40cd0
// @ref ?unknown_OverlayClass_list_00a40c00@@3V?$DynamicVectorClass@PAVOverlayClass@@@@A=00a40c00
// @ref ?OverlayTypes@@3V?$DynamicVectorClass@PAVOverlayTypeClass@@@@A=00a35de8
// @ref ?unknown_ParticleClass_list_00a35e28@@3V?$DynamicVectorClass@PAVParticleClass@@@@A=00a35e28
// @ref ?ParticleSystems@@3V?$DynamicVectorClass@PAVParticleSystemClass@@@@A=00a32280
// @ref ?ParticleSystemTypes@@3V?$DynamicVectorClass@PAVParticleSystemTypeClass@@@@A=00a35dd0
// @ref ?ParticleTypes@@3V?$DynamicVectorClass@PAVParticleTypeClass@@@@A=00a35e00
// @ref ?ScriptTypes@@3V?$DynamicVectorClass@PAVScriptTypeClass@@@@A=00866258
// @ref ?Sides@@3V?$DynamicVectorClass@PAVSideClass@@@@A=008661b0
// @ref ?Smudges@@3V?$DynamicVectorClass@PAVSmudgeClass@@@@A=00a3d240
// @ref ?SmudgeTypes@@3V?$DynamicVectorClass@PAVSmudgeTypeClass@@@@A=00a40bc8
// @ref ?Supers@@3V?$DynamicVectorClass@PAVSuperClass@@@@A=00a35d28
// @ref ?unknown_SuperClass_list_00a35db8@@3V?$DynamicVectorClass@PAVSuperClass@@@@A=00a35db8
// @ref ?SuperWeaponTypes@@3V?$DynamicVectorClass@PAVSuperWeaponTypeClass@@@@A=00a40338
// @ref ?TaskForces@@3V?$DynamicVectorClass@PAVTaskForceClass@@@@A=00a40890
// @ref ?Teams@@3V?$DynamicVectorClass@PAVTeamClass@@@@A=00866178
// @ref ?TeamTypes@@3V?$DynamicVectorClass@PAVTeamTypeClass@@@@A=00a40c48
// @ref ?Technos@@3V?$DynamicVectorClass@PAVTechnoClass@@@@A=00a40c20
// @ref ?TechnoTypes@@3V?$DynamicVectorClass@PAVTechnoTypeClass@@@@A=00a40ab8
// @ref ?Terrains@@3V?$DynamicVectorClass@PAVTerrainClass@@@@A=00a40940
// @ref ?TerrainTypes@@3V?$DynamicVectorClass@PAVTerrainTypeClass@@@@A=00a40320
// @ref ?unknown_TriggerClass_list_00a40aa0@@3V?$DynamicVectorClass@PAVTriggerClass@@@@A=00a40aa0
// @ref ?TriggerTypes@@3V?$DynamicVectorClass@PAVTriggerTypeClass@@@@A=00866208
// @ref ?unknown_TubeClass_list_008661c8@@3V?$DynamicVectorClass@PAVTubeClass@@@@A=008661c8
// @ref ?Units@@3V?$DynamicVectorClass@PAVUnitClass@@@@A=00866198
// @ref ?UnitTypes@@3V?$DynamicVectorClass@PAVUnitTypeClass@@@@A=00a35d48
// @ref ?VoxelAnimTypes@@3V?$DynamicVectorClass@PAVVoxelAnimTypeClass@@@@A=00a40ae0
// @ref ?Waves@@3V?$DynamicVectorClass@PAVWaveClass@@@@A=00a40be8
// @ref ?unknown_math_4ba520@@YANN@Z=004ba520
// @ref ?unknown_math_4ba5b0@@YANN@Z=004ba5b0
// @ref ?unknown_objects_a40368@@3V?$DynamicVectorClass@PAVObjectClass@@@@A=00a40368
// @ref ?unknown_sqrt_4ba410@@YANN@Z=004ba410
// @ref _$E101=004d33d0
// @ref _$E106=004d3450
// @ref _$E111=004d34d0
// @ref _$E116=004d3550
// @ref _$E121=004d35d0
// @ref _$E126=004d3650
// @ref _$E131=004d36d0
// @ref _$E136=004d3750
// @ref _$E141=004d37d0
// @ref _$E146=004d3850
// @ref _$E151=004d38d0
// @ref _$E156=004d3950
// @ref _$E161=004d39d0
// @ref _$E166=004d3a50
// @ref _$E171=004d3ad0
// @ref _$E176=004d3b50
// @ref _$E181=004d3bd0
// @ref _$E186=004d3c50
// @ref _$E191=004d3cd0
// @ref _$E196=004d3d50
// @ref _$E201=004d3dd0
// @ref _$E206=004d3e50
// @ref _$E211=004d3ed0
// @ref _$E216=004d3f50
// @ref _$E221=004d3fd0
// @ref _$E226=004d4050
// @ref _$E231=004d40d0
// @ref _$E236=004d4150
// @ref _$E241=004d41d0
// @ref _$E246=004d4250
// @ref _$E251=004d42d0
// @ref _$E256=004d4350
// @ref _$E261=004d43d0
// @ref _$E266=004d4450
// @ref _$E271=004d44d0
// @ref _$E41=004d2dd0
// @ref _$E46=004d2e50
// @ref _$E51=004d2ed0
// @ref _$E56=004d2f50
// @ref _$E61=004d2fd0
// @ref _$E66=004d3050
// @ref _$E71=004d30d0
// @ref _$E76=004d3150
// @ref _$E81=004d31d0
// @ref _$E86=004d3250
// @ref _$E91=004d32d0
// @ref _$E96=004d3350
// @ref __CIpow=007821b0
// @ref __ftol=0077f110
// @ref __real@8@3ff78000000000000000=0079a730
// @ref __real@8@3ffe8000000000000000=0079a728
// @ref __real@8@3fff8000000000000000=0079a708
// @ref __real@8@40008000000000000000=0079a6f8
// @ref __real@8@4004b400000000000000=0079a710
// @ref __real@8@4004f000000000000000=0079a718
// @ref __real@8@4005b400000000000000=0079a720
// @ref __real@8@40078000000000000000=0079a700
// @ref _atexit=0078298a
// @ref _unknown_geometry_angle45=00a40ad8
// @ref _unknown_geometry_angle60=00a35e18
// @ref _unknown_geometry_angle90=008661f8
// @ref _unknown_geometry_b=00a40c40
// @ref _unknown_geometry_c=00a40b10
// @ref _unknown_geometry_deg_to_rad=007a2098
// @ref _unknown_geometry_diagonal=00a35da8
// @ref _unknown_geometry_g=00a40d00
// @ref _unknown_geometry_h=00a35e40
// @ref _unknown_geometry_i=00a40918
// @ref _unknown_geometry_j=00a40c3c
// @ref _unknown_geometry_k=00a35d40
// @ref _unknown_geometry_l=00a40388
// @ref _unknown_geometry_sixty=007a2090
// @ref _unknown_static_rect=00a35cc8
