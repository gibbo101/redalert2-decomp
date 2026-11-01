// RulesClass: the game rules (rules.ini) object. The name is Westwood's;
// there is no RTTI for it (the class has no virtual functions). The pointer
// at 0x00839848 is set at 0x00511714 from `new` of 0x14C0 bytes constructed
// by 0x00640B80 (7768 bytes; no vtable store). Formerly three views of the
// same object: shared/object.hpp's UnknownRules839848, shared/radsite.hpp's
// RadSiteRules and UnknownRulesView_004f3120 (0x004F3120). Field names are
// hypotheses (unknown_ names keep their offsets) unless stated.
#ifndef RA2_SHARED_RULES_HPP
#define RA2_SHARED_RULES_HPP

#include "shared/type_list.hpp"
#include "shared/rgb_class.hpp"
#include "shared/ini_enums.hpp"

class CCINIClass;
class NoInitClass;
class AbstractClass;
class AircraftTypeClass;
class BulletTypeClass;
class HouseTypeClass;
class InfantryTypeClass;
class OverlayTypeClass;
class ParticleTypeClass;
class SmudgeTypeClass;
class SuperWeaponTypeClass;
class TeamTypeClass;
class TerrainTypeClass;
class UnitTypeClass;
class VoxelAnimTypeClass;
class WeaponTypeClass;
class AnimTypeClass;
class BuildingTypeClass;
class ObjectClass;
class ObjectTypeClass;
class ParticleSystemTypeClass;
class TechnoTypeClass;
class WarheadTypeClass;

// 0x0053D820 (__fastcall): stores its argument at 0x007DFB34, a frame-rate threshold
// (RadarClass passes DetailMinFrameRateNormal or DetailMinFrameRateMovie; name hypothesis).
void __fastcall unknown_set_frame_rate_0053d820(int rate);
// 0x0053D830 (__fastcall): stores its argument at 0x007DFB38 (Fill_In_Data passes
// DetailBufferZoneWidth; name hypothesis).
void __fastcall unknown_set_buffer_zone_0053d830(int width);

// A rocket's flight model ([General] V3Rocket*= and DMisl*=; RulesClass::General).
struct RocketStruct {
    int PauseFrames;                // +0x00
    int TiltFrames;                 // +0x04
    float PitchInitial;             // +0x08
    float PitchFinal;               // +0x0C
    float TurnRate;                 // +0x10
    float Acceleration;             // +0x14
    int Altitude;                   // +0x18
    int Damage;                     // +0x1C
    int EliteDamage;                // +0x20
    int BodyLength;                 // +0x24
    bool LazyCurve;                 // +0x28
    AircraftTypeClass *Type;        // +0x2C
};

// The modifiers of one difficulty level (Westwood's DifficultyClass; [Easy], [Normal],
// [Difficult] in rules.ini, read by RulesClass::Difficulty).
struct DifficultyClass {
    double FirePower;       // +0x00
    double GroundSpeed;     // +0x08
    double AirSpeed;        // +0x10
    double Armor;           // +0x18
    double ROF;             // +0x20
    double Cost;            // +0x28
    double BuildTime;       // +0x30
    double RepairDelay;     // +0x38
    double BuildDelay;      // +0x40
    bool   BuildSlowdown;   // +0x48
    bool   DestroyWalls;    // +0x49
    bool   ContentScan;     // +0x4A
    char   unknown_4b[0x50 - 0x4B];
};

class RulesClass {
public:
    RulesClass(NoInitClass const &noinit);   // 0x00640460 (load: only the lists and colours are built)
    RulesClass();                            // 0x00640B80
    ~RulesClass();                           // 0x006429E0
    bool Addition(CCINIClass &ini);          // 0x006437F0 every section, in order
    void Process(CCINIClass &ini);           // 0x006433A0 the rules INI's sections (Read_Scenario_INI; name hypothesis)
    bool Special_Weapons(CCINIClass &ini);   // 0x00643B80 [SpecialWeapons]
    bool Audio_Visual(CCINIClass &ini);      // 0x00643E10 [AudioVisual]
    bool Crate_Rules(CCINIClass &ini);       // 0x006469B0 [CrateRules]
    bool Combat_Damage(CCINIClass &ini);     // 0x00646C60 [CombatDamage]
    bool Radiation(CCINIClass &ini);         // 0x00647B60 [Radiation]
    bool Elevation_Model(CCINIClass &ini);   // 0x00647D40 [ElevationModel]
    bool Wall_Model(CCINIClass &ini);        // 0x00647DE0 [WallModel]
    bool Colors(CCINIClass &ini);            // 0x00647E60 [Colors]
    bool General(CCINIClass &ini);           // 0x00647F40 [General]
    bool MPlayer(CCINIClass &ini);           // 0x0064B690 [MultiplayerDialogSettings]
    bool Heap_Maximums(CCINIClass &ini);     // 0x0064BA00 [Maximums]
    bool Infantry(CCINIClass &ini);          // 0x0064BA50 [InfantryTypes]
    bool Countries(CCINIClass &ini);         // 0x0064BAC0 [Countries]
    bool Vehicles(CCINIClass &ini);          // 0x0064BB30 [VehicleTypes]
    bool Aircraft(CCINIClass &ini);          // 0x0064BBA0 [AircraftTypes]
    bool Sides(CCINIClass &ini);             // 0x0064BC10 [Sides]
    bool Super_Weapons(CCINIClass &ini);     // 0x0064BDC0 [SuperWeaponTypes]
    bool Buildings(CCINIClass &ini);         // 0x0064BE30 [BuildingTypes]
    bool Terrains(CCINIClass &ini);          // 0x0064BEA0 [TerrainTypes]
    bool Teams(CCINIClass &ini);             // 0x0064BF10 [Teams]
    bool Smudges(CCINIClass &ini);           // 0x0064BFA0 [SmudgeTypes]
    bool Overlays(CCINIClass &ini);          // 0x0064C010 [OverlayTypes]
    bool Animations(CCINIClass &ini);        // 0x0064C080 [Animations]
    bool Voxel_Anims(CCINIClass &ini);       // 0x0064C0F0 [VoxelAnims]
    bool Warheads(CCINIClass &ini);          // 0x0064C160 [Warheads]
    bool Particles(CCINIClass &ini);         // 0x0064C1D0 [Particles]
    bool Particle_Systems(CCINIClass &ini);  // 0x0064C240 [ParticleSystems]
    bool AI(CCINIClass &ini);                // 0x0064C2B0 [AI]
    bool Movies(CCINIClass &ini);            // 0x0064DC90 [Movies]
    bool Advanced_Command_Bar(CCINIClass &ini, bool multiplayer);   // 0x0064DD90 [AdvancedCommandBar]
    bool Powerups(CCINIClass &ini);          // 0x0064D490 [Powerups]
    bool Land_Types(CCINIClass &ini);        // 0x0064D610 one section per land type
    bool IQ(CCINIClass &ini);                // 0x0064D850 [IQ]
    bool Jumpjet_Controls(CCINIClass &ini);  // 0x0064D9E0 [JumpjetControls]
    bool Difficulty(CCINIClass &ini);        // 0x0064DB10 [Easy] [Normal] [Difficult]
    bool Objects(CCINIClass &ini);           // 0x00652270 each type and mission reads its own section
    void Save(IStream *stream);              // 0x0064DE70 the object, then each list
    void Load(IStream *stream);              // 0x0064E6B0
    void Detach(AbstractClass const *target, bool all);   // 0x00651290 (TibSun signature)
    int                      DetailMinFrameRateNormal;   // +0x0 DetailMinFrameRateNormal; (radar: made current, 0x0053D820, after a restore)
    int                      DetailMinFrameRateMovie;   // +0x4 DetailMinFrameRateMovie; (radar mode-4 update)
    int                      DetailBufferZoneWidth;   // +0x8
    int                      AmmoCrateDamage;   // +0xC
    UnitTypeClass *          LargeVisceroid;   // +0x10
    UnitTypeClass *          SmallVisceroid;   // +0x14
    UnitTypeClass *          UnloadingHarvester;   // +0x18
    int                      AttackingAircraftSightRange;   // +0x1C
    double                   unknown_20;   // +0x20 TunnelSpeed; a speed scale (Tunnel.cpp; hypothesis)
    double                   TiberiumHeal;   // +0x28
    TypeList<BuildingTypeClass *> HSBuilding;   // +0x30
    bool                     FreeMCV;   // +0x4C
    bool                     BerzerkAllowed;   // +0x4D
    char unknown_04e[0x50 - 0x4E];
    int                      unknown_50;   // +0x50 PoseDir; a direction (AircraftClass::Landing_Direction)
    AnimTypeClass *          DropPodPuff;   // +0x54
    int                      WaypointAnimationSpeed;   // +0x58
    AnimTypeClass *          BarrelExplode;   // +0x5C
    TypeList<VoxelAnimTypeClass *> BarrelDebris;   // +0x60
    ParticleSystemTypeClass * BarrelParticle;   // +0x7C
    float                    RadarEventColorSpeed;   // +0x80
    int                      RadarEventMinRadius;   // +0x84
    float                    RadarEventSpeed;   // +0x88
    float                    RadarEventRotationSpeed;   // +0x8C
    int                      FlashFrameTime;   // +0x90
    int                      RadarCombatFlashTime;   // +0x94
    int                      unknown_98;   // +0x98 MaxWaypointPathLength; (0x004F3120: a slot readiness count)
    AnimTypeClass *          unknown_09c;   // +0x9C Wake; (a falling-aircraft smoke animation; AircraftClass::AI)
    AnimTypeClass *          NukeTakeOff;   // +0xA0
    AnimTypeClass *          InfantryExplode;   // +0xA4
    AnimTypeClass *          FlamingInfantry;   // +0xA8
    AnimTypeClass *          InfantryHeadPop;   // +0xAC
    AnimTypeClass *          InfantryNuked;   // +0xB0
    AnimTypeClass *          Behind;   // +0xB4
    double                   unknown_b8;   // +0xB8 AITriggerSuccessWeightDelta; AI trigger weight bonus on success (AITriggerType 0x0041DFB0; hypothesis)
    double                   unknown_c0;   // +0xC0 AITriggerFailureWeightDelta; AI trigger weight change on failure (0x0041E070; hypothesis)
    double                   unknown_c8;   // +0xC8 AITriggerTrackRecordCoefficient; AI trigger failure scale (0x0041E070; hypothesis)
    int                      VeinholeMonsterStrength;   // +0xD0
    int                      unknown_d4;   // +0xD4 MaxVeinholeGrowth; vein nodes per veinhole monster (VeinholeMonsterClass)
    int                      VeinholeGrowthRate;   // +0xD8
    int                      VeinholeShrinkRate;   // +0xDC
    AnimTypeClass *          VeinAttack;   // +0xE0
    int                      unknown_e4;   // +0xE4 VeinDamage; vein damage (AnimClass 0x00422F50)
    int                      MaximumQueuedObjects;   // +0xE8
    int                      unknown_ec;   // +0xEC AircraftFogReveal; a sight range (AircraftClass slot 70)
    OverlayTypeClass *       unknown_f0;   // +0xF0 WoodCrateImg; (OverlayClass slot 71: an overlay type placed without a house; hypothesis)
    OverlayTypeClass *       unknown_f4;   // +0xF4 CrateImg
    OverlayTypeClass *       unknown_f8;   // +0xF8 WaterCrateImg
    TypeList<AnimTypeClass *> DropPod;   // +0xFC
    TypeList<AnimTypeClass *> DeadBodies;   // +0x118
    TypeList<AnimTypeClass *> MetallicDebris;   // +0x134
    TypeList<AnimTypeClass *> BridgeExplosions;   // +0x150
    int                      unknown_16c;   // +0x16C DigSound; a sound (Tunnel.cpp: a unit surfaces)
    int                      CreateUnitSound;   // +0x170
    int                      CreateInfantrySound;   // +0x174
    int                      CreateAircraftSound;   // +0x178
    int                      BaseUnderAttackSound;   // +0x17C
    int                      unknown_180;   // +0x180 GUIMainButtonSound; sound: sidebar shown/hidden (SidebarClass::AI; hypothesis)
    int                      unknown_184;   // +0x184 GUIBuildSound
    int                      unknown_188;   // +0x188 GUITabSound; sound: sidebar tab/scroll click (SidebarClass::AI)
    int                      unknown_18c;   // +0x18C GUIOpenSound; sound: the tab bar opens (TabClass::AI)
    int                      unknown_190;   // +0x190 GUICloseSound; sound: the tab bar closes (TabClass::AI)
    int                      GUIMoveOutSound;   // +0x194
    int                      GUIMoveInSound;   // +0x198
    int                      GUIComboOpenSound;   // +0x19C
    int                      GUIComboCloseSound;   // +0x1A0
    int                      GUICheckboxSound;   // +0x1A4
    int                      ScoreAnimSound;   // +0x1A8
    int                      IFVTransformSound;   // +0x1AC
    int                      PsychicSensorDetectSound;   // +0x1B0
    int                      BuildingGarrisonedSound;   // +0x1B4
    int                      BuildingAbandonedSound;   // +0x1B8
    int                      unknown_1bc;   // +0x1BC BuildingRepairedSound; a sound (TechnoClass slot 233 plays it for buildings)
    int                      CheerSound;   // +0x1C0
    int                      PlaceBeaconSound;   // +0x1C4
    int                      DefaultChronoSound;   // +0x1C8
    int                      unknown_1cc;   // +0x1CC StartPlanningModeSound; a sound: planning mode starts (Planning.cpp; hypothesis)
    int                      unknown_1d0;   // +0x1D0 AddPlanningModeCommandSound; a sound: a planned order is taken (Planning.cpp; hypothesis)
    int                      ExecutePlanSound;   // +0x1D4
    int                      unknown_1d8;   // +0x1D8 EndPlanningModeSound; a sound: planning mode ends (Planning.cpp; hypothesis)
    int                      CrateMoneySound;   // +0x1DC
    int                      CrateRevealSound;   // +0x1E0
    int                      CrateFireSound;   // +0x1E4
    int                      CrateArmourSound;   // +0x1E8
    int                      CrateSpeedSound;   // +0x1EC
    int                      CrateUnitSound;   // +0x1F0
    int                      CratePromoteSound;   // +0x1F4
    int                      ImpactWaterSound;   // +0x1F8
    int                      ImpactLandSound;   // +0x1FC
    int                      unknown_200;   // +0x200 SinkingSound; a sound: a unit starts sinking (FootClass::AI; hypothesis)
    int                      BombTickingSound;   // +0x204
    int                      BombAttachSound;   // +0x208
    int                      YuriMindControlSound;   // +0x20C
    int                      ChronoInSound;   // +0x210
    int                      ChronoOutSound;   // +0x214
    int                      SpySatActivationSound;   // +0x218
    int                      SpySatDeactivationSound;   // +0x21C
    int                      UpgradeVeteranSound;   // +0x220
    int                      UpgradeEliteSound;   // +0x224
    AnimTypeClass *          unknown_228;   // +0x228 Dig; an animation (Tunnel.cpp: dust where a unit digs in or out)
    AnimTypeClass *          IonBlast;   // +0x22C
    AnimTypeClass *          IonBeam;   // +0x230
    TypeList<AnimTypeClass *> DamageFireTypes;   // +0x234
    TypeList<AnimTypeClass *> WeatherConClouds;   // +0x250
    TypeList<AnimTypeClass *> WeatherConBolts;   // +0x26C
    AnimTypeClass *          WeatherConBoltExplosion;   // +0x288
    AnimTypeClass *          ChronoBlast;   // +0x28C
    AnimTypeClass *          ChronoBlastDest;   // +0x290
    AnimTypeClass *          ChronoPlacement;   // +0x294
    AnimTypeClass *          ChronoBeam;   // +0x298
    AnimTypeClass *          WarpIn;   // +0x29C
    AnimTypeClass *          WarpOut;   // +0x2A0
    AnimTypeClass *          WarpAway;   // +0x2A4
    AnimTypeClass *          unknown_2a8;   // +0x2A8 ChronoSparkle1; (a damaged-aircraft animation every 24 frames; AircraftClass::AI)
    AnimTypeClass *          IronCurtainInvokeAnim;   // +0x2AC
    AnimTypeClass *          WeaponNullifyAnim;   // +0x2B0
    AnimTypeClass *          AtmosphereEntry;   // +0x2B4
    TypeList<int>            PrerequisitePower;   // +0x2B8
    TypeList<int>            PrerequisiteFactory;   // +0x2D4
    TypeList<int>            PrerequisiteBarracks;   // +0x2F0
    TypeList<int>            PrerequisiteRadar;   // +0x30C
    TypeList<int>            PrerequisiteTech;   // +0x328
    TypeList<int>            PrerequisiteProc;   // +0x344
    int                      GateUp;   // +0x360
    int                      GateDown;   // +0x364
    int                      unknown_368;   // +0x368 TurnRate; jumpjet turn rate (Loco; hypothesis)
    int                      Speed;   // +0x36C
    double                   Climb;   // +0x370
    int                      unknown_378;   // +0x378 CruiseHeight
    char unknown_37c[0x380 - 0x37C];
    double                   Acceleration;   // +0x380
    double                   WobblesPerSecond;   // +0x388
    int                      WobbleDeviation;   // +0x390
    TypeList<int>            RadarEventSuppressionDistances;   // +0x394
    TypeList<int>            RadarEventVisibilityDurations;   // +0x3B0
    TypeList<int>            RadarEventDurations;   // +0x3CC
    int                      IonCannonDamage;   // +0x3E8
    int                      RailgunDamageRadius;   // +0x3EC
    BuildingTypeClass *      PrismType;   // +0x3F0
    int                      PrismSupportModifier;   // +0x3F4
    int                      PrismSupportMax;   // +0x3F8
    int                      PrismSupportDelay;   // +0x3FC
    int                      PrismSupportDuration;   // +0x400
    int                      PrismSupportHeight;   // +0x404
    RocketStruct             V3Rocket;   // +0x408
    RocketStruct             DMisl;   // +0x438
    int                      unknown_468;   // +0x468 ParadropRadius; a distance (Aircraft.cpp slots 146/147)
    char unknown_46c[0x470 - 0x46C];
    double                   ZoomInFactor;   // +0x470
    double                   ConditionRedSparkingProbability;   // +0x478
    double                   ConditionYellowSparkingProbability;   // +0x480
    int                      unknown_488;   // +0x488 TiberiumExplosionDamage; tiberium chain-reaction damage (AnimClass 0x004226D0; hypothesis)
    int                      TiberiumStrength;   // +0x48C
    float                    MinLowPowerProductionSpeed;   // +0x490
    float                    MaxLowPowerProductionSpeed;   // +0x494
    float                    LowPowerPenaltyModifier;   // +0x498
    float                    MultipleFactory;   // +0x49C
    int                      MaximumCheerRate;   // +0x4A0
    char unknown_4a4[0x4A8 - 0x4A4];
    double                   TreeFlammability;   // +0x4A8
    double                   MissileSpeedVar;   // +0x4B0
    double                   MissileROTVar;   // +0x4B8
    int                      MissileSafetyAltitude;   // +0x4C0
    WeaponTypeClass *        DropPodWeapon;   // +0x4C4
    int                      DropPodHeight;   // +0x4C8
    int                      DropPodSpeed;   // +0x4CC
    double                   DropPodAngle;   // +0x4D0
    double                   ScrollMultiplier;   // +0x4D8
    double                   CrewEscape;   // +0x4E0
    int                      unknown_4e8;   // +0x4E8 ShakeScreen; (UnitClass 0x006FD3A0: a strength threshold for the death shake)
    int                      HoverHeight;   // +0x4EC
    double                   HoverBob;   // +0x4F0
    double                   HoverBoost;   // +0x4F8
    double                   HoverAcceleration;   // +0x500
    double                   HoverBrake;   // +0x508
    double                   HoverDampen;   // +0x510
    double                   PlacementDelay;   // +0x518
    TypeList<VoxelAnimTypeClass *> ExplosiveVoxelDebris;   // +0x520
    VoxelAnimTypeClass *     TireVoxelDebris;   // +0x53C
    VoxelAnimTypeClass *     ScrapVoxelDebris;   // +0x540
    int                      BridgeVoxelMax;   // +0x544
    int                      unknown_548;   // +0x548 CloakingStages; cloak stage count (TechnoClass slot 252)
    int                      RevealTriggerRadius;   // +0x54C
    double                   ShipSinkingWeight;   // +0x550
    double                   IceCrackingWeight;   // +0x558
    double                   IceBreakingWeight;   // +0x560
    TypeList<int>            IceCrackSounds;   // +0x568
    char                     CliffBackImpassability;   // +0x584
    char unknown_585[0x588 - 0x585];
    double                   VeteranRatio;   // +0x588
    double                   VeteranCombat;   // +0x590
    double                   unknown_598;   // +0x598 VeteranSpeed; a veteran speed factor (FootClass slot 303; hypothesis)
    double                   unknown_5a0;   // +0x5A0 VeteranSight; sight factor for the veteran/elite sight ability (TechnoClass slot 70; 0 = none)
    double                   VeteranArmor;   // +0x5A8
    double                   VeteranROF;   // +0x5B0
    double                   VeteranCap;   // +0x5B8
    int                      unknown_5c0;   // +0x5C0 CloakSound; a sound (TechnoClass slots 252/253)
    int                      unknown_5c4;   // +0x5C4 SellSound; a sound (FootClass slot 98 plays it when a unit is sold)
    int                      GameClosed;   // +0x5C8
    int                      IncomingMessage;   // +0x5CC
    int                      SystemError;   // +0x5D0
    int                      OptionsChanged;   // +0x5D4
    int                      GameForming;   // +0x5D8
    int                      PlayerLeft;   // +0x5DC
    int                      PlayerJoined;   // +0x5E0
    int                      MessageCharTyped;   // +0x5E4
    int                      Construction;   // +0x5E8
    TypeList<int>            CreditTicks;   // +0x5EC
    int                      BuildingDieSound;   // +0x608
    int                      BuildingSlam;   // +0x60C
    int                      unknown_610;   // +0x610 RadarOn; sound: radar activates (RadarClass 0x00632F30)
    int                      unknown_614;   // +0x614 RadarOff; sound: radar deactivates
    int                      unknown_618;   // +0x618 MovieOn
    int                      MovieOff;   // +0x61C
    int                      unknown_620;   // +0x620 ScoldSound; sound: sidebar scroll refused (SidebarClass::AI)
    int                      TeslaCharge;   // +0x624
    int                      TeslaZap;   // +0x628
    int                      unknown_62c;   // +0x62C GenericClick; sound: repair toggled (BuildingClass slot 97/98)
    int                      GenericBeep;   // +0x630
    int                      BuildingDamageSound;   // +0x634
    int                      HealCrateSound;   // +0x638
    int                      ChuteSound;   // +0x63C
    int                      unknown_640;   // +0x640 StopSound; a sound (UICmnds.cpp 0x006F5BC0)
    int                      unknown_644;   // +0x644 GuardSound; a sound (UICmnds.cpp 0x006F5B10)
    int                      unknown_648;   // +0x648 ScatterSound; a sound (UICmnds.cpp 0x006F5D10: the group command refused)
    int                      unknown_64c;   // +0x64C
    int                      StormSound;   // +0x650
    TypeList<int>            LightningSounds;   // +0x654
    int                      ShellButtonSlideSound;   // +0x670
    char unknown_674[0x678 - 0x674];
    double                   WallBuildSpeedCoefficient;   // +0x678
    double                   ChargeToDrainRatio;   // +0x680
    double                   DamageToFirestormDamageCoefficient;   // +0x688
    double                   TrackedUphill;   // +0x690
    double                   TrackedDownhill;   // +0x698
    double                   WheeledUphill;   // +0x6A0
    double                   WheeledDownhill;   // +0x6A8
    int                      unknown_6b0;   // +0x6B0 SpotlightMovementRadius; search light: far range (BuildingLightClass 0x00434610; hypothesis)
    int                      unknown_6b4;   // +0x6B4 SpotlightLocationRadius; search light: near range
    double                   SpotlightSpeed;   // +0x6B8
    double                   SpotlightAcceleration;   // +0x6C0
    double                   SpotlightAngle;   // +0x6C8
    int                      unknown_6d0;   // +0x6D0 SpotlightRadius; search light: base value (0x00434530)
    int                      unknown_6d4;   // +0x6D4 WindDirection; wind direction (0..7; Particle.cpp)
    int                      CameraRange;   // +0x6D8
    int                      unknown_6dc;   // +0x6DC FlightLevel; default flight level (TechnoType slot 47)
    int                      ParachuteMaxFallRate;   // +0x6E0
    int                      NoParachuteMaxFallRate;   // +0x6E4
    int                      BuildingDrop;   // +0x6E8
    TypeList<SmudgeTypeClass *> Scorches;   // +0x6EC
    TypeList<SmudgeTypeClass *> Scorches1;   // +0x708
    TypeList<SmudgeTypeClass *> Scorches2;   // +0x724
    TypeList<SmudgeTypeClass *> Scorches3;   // +0x740
    TypeList<SmudgeTypeClass *> Scorches4;   // +0x75C
    BuildingTypeClass *      unknown_778;   // +0x778 RepairBay; a building type (AircraftClass slot 28)
    BuildingTypeClass *      unknown_77c;   // +0x77C GDIGateOne; (BuildingClass slot 52: a type whose X neighbours are refreshed)
    BuildingTypeClass *      unknown_780;   // +0x780 GDIGateTwo; (Y neighbours)
    BuildingTypeClass *      unknown_784;   // +0x784 NodGateOne; (X neighbours)
    BuildingTypeClass *      unknown_788;   // +0x788 NodGateTwo; (Y neighbours)
    BuildingTypeClass *      unknown_78c;   // +0x78C WallTower; (the surrounding cells' wall overlays)
    TypeList<BuildingTypeClass *> Shipyard;   // +0x790
    BuildingTypeClass *      GDIPowerPlant;   // +0x7AC
    BuildingTypeClass *      GDIPowerTurbine;   // +0x7B0
    BuildingTypeClass *      NodRegularPower;   // +0x7B4
    BuildingTypeClass *      NodAdvancedPower;   // +0x7B8
    BuildingTypeClass *      unknown_7bc;   // +0x7BC GDIFirestormGenerator; a building type (BuildingClass 0x0044D530: powering it down tells the house)
    UnitTypeClass *          GDIHunterSeeker;   // +0x7C0
    UnitTypeClass *          NodHunterSeeker;   // +0x7C4
    TypeList<BuildingTypeClass *> unknown_7c8;   // +0x7C8 BuildConst; building types a deployed unit may become (UnitClass slot 132; hypothesis: BuildConst)
    TypeList<BuildingTypeClass *> BuildPower;   // +0x7E4
    TypeList<BuildingTypeClass *> BuildRefinery;   // +0x800
    TypeList<BuildingTypeClass *> BuildBarracks;   // +0x81C
    TypeList<BuildingTypeClass *> BuildTech;   // +0x838
    TypeList<BuildingTypeClass *> BuildWeapons;   // +0x854
    TypeList<BuildingTypeClass *> BuildDefense;   // +0x870
    TypeList<BuildingTypeClass *> BuildPDefense;   // +0x88C
    TypeList<BuildingTypeClass *> BuildAA;   // +0x8A8
    TypeList<BuildingTypeClass *> BuildHelipad;   // +0x8C4
    TypeList<BuildingTypeClass *> BuildRadar;   // +0x8E0
    TypeList<BuildingTypeClass *> ConcreteWalls;   // +0x8FC
    TypeList<BuildingTypeClass *> NSGates;   // +0x918
    TypeList<BuildingTypeClass *> EWGates;   // +0x934
    TypeList<BuildingTypeClass *> BuildNavalYard;   // +0x950
    TypeList<BuildingTypeClass *> BuildDummy;   // +0x96C
    TypeList<BuildingTypeClass *> NeutralTechBuildings;   // +0x988
    char unknown_9a4[0x9A8 - 0x9A4];
    double                   GDIWallDefense;   // +0x9A8
    double                   GDIWallDefenseCoefficient;   // +0x9B0
    double                   NodBaseDefenseCoefficient;   // +0x9B8
    double                   GDIBaseDefenseCoefficient;   // +0x9C0
    int                      ComputerBaseDefenseResponse;   // +0x9C8
    int                      MaximumBaseDefenseValue;   // +0x9CC
    TypeList<UnitTypeClass *> BaseUnit;   // +0x9D0
    TypeList<UnitTypeClass *> unknown_9ec;   // +0x9EC HarvesterUnit; objects a VehicleThief may always take (InfantryClass slot 28; element type hypothesis)
    TypeList<AircraftTypeClass *> PadAircraft;   // +0xA08
    TypeList<AnimTypeClass *> OnFire;   // +0xA24
    TypeList<AnimTypeClass *> TreeFire;   // +0xA40
    AnimTypeClass *          Smoke;   // +0xA5C
    AnimTypeClass *          unknown_a60;   // +0xA60
    AnimTypeClass *          FirestormActiveAnim;   // +0xA64
    AnimTypeClass *          FirestormIdleAnim;   // +0xA68
    AnimTypeClass *          FirestormAirAnim;   // +0xA6C
    AnimTypeClass *          FirestormGroundAnim;   // +0xA70
    AnimTypeClass *          unknown_a74;   // +0xA74 MoveFlash; the move-flash animation type (FootClass slot 77; hypothesis)
    AnimTypeClass *          unknown_a78;   // +0xA78 BombParachute; an animation for kind 8 placed by ObjectClass slot 56
    AnimTypeClass *          unknown_a7c;   // +0xA7C Parachute; an animation for the other kinds (ObjectClass slot 56, 0x4B above)
    TypeList<AnimTypeClass *> SplashList;   // +0xA80
    AnimTypeClass *          SmallFire;   // +0xA9C
    AnimTypeClass *          LargeFire;   // +0xAA0
    InfantryTypeClass *      Paratrooper;   // +0xAA4
    int                      EliteFlashTimer;   // +0xAA8
    int                      ChronoDelay;   // +0xAAC
    int                      ChronoReinfDelay;   // +0xAB0
    int                      ChronoDistanceFactor;   // +0xAB4
    bool                     ChronoTrigger;   // +0xAB8
    char unknown_ab9[0xABC - 0xAB9];
    int                      ChronoMinimumDelay;   // +0xABC
    int                      ChronoRangeMinimum;   // +0xAC0
    TypeList<InfantryTypeClass *> AmerParaDropInf;   // +0xAC4
    TypeList<int>            AmerParaDropNum;   // +0xAE0
    TypeList<InfantryTypeClass *> AllyParaDropInf;   // +0xAFC
    TypeList<int>            AllyParaDropNum;   // +0xB18
    TypeList<InfantryTypeClass *> SovParaDropInf;   // +0xB34
    TypeList<int>            SovParaDropNum;   // +0xB50
    InfantryTypeClass *      unknown_b6c;   // +0xB6C AlliedDisguise; (InfantryClass slot 256, house +0x130 clear)
    InfantryTypeClass *      unknown_b70;   // +0xB70 SovietDisguise; (InfantryClass slot 256, house +0x130 set)
    int                      SpyPowerBlackout;   // +0xB74
    float                    SpyMoneyStealPercent;   // +0xB78
    bool                     AttackCursorOnDisguise;   // +0xB7C
    char unknown_b7d[0xB80 - 0xB7D];
    float                    unknown_b80;   // +0xB80 AIMinorSuperReadyPercent; the recharge fraction AI triggers wait for (AITriggerType conditions)
    int                      AISafeDistance;   // +0xB84
    int                      HarvesterTooFarDistance;   // +0xB88
    int                      ChronoHarvTooFarDistance;   // +0xB8C
    TypeList<int>            AlliedBaseDefenseCounts;   // +0xB90
    TypeList<int>            SovietBaseDefenseCounts;   // +0xBAC
    TypeList<int>            AIPickWallDefensePercent;   // +0xBC8
    int                      AIRestrictReplaceTime;   // +0xBE4
    int                      unknown_be8;   // +0xBE8 ThreatPerOccupant; TechnoClass slot 168
    int                      unknown_bec;   // +0xBEC ApproachTargetResetMultiplier; (Building)
    int                      CampaignMoneyDeltaEasy;   // +0xBF0
    int                      CampaignMoneyDeltaHard;   // +0xBF4
    int                      GuardAreaTargetingDelay;   // +0xBF8
    int                      NormalTargetingDelay;   // +0xBFC
    int                      AINavalYardAdjacency;   // +0xC00
    TypeList<int>            DisabledDisguiseDetectionPercent;   // +0xC04
    TypeList<int>            AIAutoDeployFrameDelay;   // +0xC20
    int                      MaximumBuildingPlacementFailures;   // +0xC3C
    float                    PurifierBonus;   // +0xC40
    InfantryTypeClass *      Technician;   // +0xC44 (TechnoClass slot 184: the default crew)
    InfantryTypeClass *      Engineer;   // +0xC48 (BuildingClass slot 184: a factory-type-7 building's crew)
    InfantryTypeClass *      Pilot;   // +0xC4C
    InfantryTypeClass *      AlliedCrew;   // +0xC50 (slot 184: crew for house +0x130 = 0)
    InfantryTypeClass *      SovietCrew;   // +0xC54 (slot 184: crew for house +0x130 = 1)
    WarheadTypeClass *       FlameDamage;   // +0xC58
    WarheadTypeClass *       FlameDamage2;   // +0xC5C
    WarheadTypeClass *       unknown_c60;   // +0xC60 NukeWarhead; (AnimClass 0x00422BA0)
    BulletTypeClass *        NukeProjectile;   // +0xC64
    BulletTypeClass *        NukeDown;   // +0xC68
    WarheadTypeClass *       EMPulseWarhead;   // +0xC6C
    BulletTypeClass *        EMPulseProjectile;   // +0xC70
    WarheadTypeClass *       unknown_c74;   // +0xC74 C4Warhead; the warhead that kills a defeated house's units (House.cpp; hypothesis)
    WarheadTypeClass *       V3Warhead;   // +0xC78
    WarheadTypeClass *       DMislWarhead;   // +0xC7C
    WarheadTypeClass *       V3EliteWarhead;   // +0xC80
    WarheadTypeClass *       DMislEliteWarhead;   // +0xC84
    WarheadTypeClass *       IvanWarhead;   // +0xC88
    int                      IvanDamage;   // +0xC8C
    int                      IvanTimedDelay;   // +0xC90
    bool                     CanDetonateTimeBomb;   // +0xC94
    bool                     CanDetonateDeathBomb;   // +0xC95
    char unknown_c96[0xC98 - 0xC96];
    int                      IvanIconFlickerRate;   // +0xC98
    WeaponTypeClass *        DeathWeapon;   // +0xC9C
    void const *             BombCursorShape;   // +0xCA0
    int                      IronCurtainDuration;   // +0xCA4
    WarheadTypeClass *       IonCannonWarhead;   // +0xCA8
    WarheadTypeClass *       unknown_cac;   // +0xCAC FirestormWarhead; a warhead (AircraftClass slot 86)
    WarheadTypeClass *       unknown_cb0;   // +0xCB0 VeinholeWarhead; the veins' warhead (AnimClass 0x00422F50)
    TerrainTypeClass *       unknown_cb4;   // +0xCB4 VeinholeTypeClass; the veinhole monster's type (VeinholeMonsterClass slot 33)
    TypeList<TerrainTypeClass *> DefaultMirageDisguises;   // +0xCB8
    int                      InfantryBlinkDisguiseTime;   // +0xCD4
    ParticleSystemTypeClass * DefaultLargeGreySmokeSystem;   // +0xCD8
    ParticleSystemTypeClass * DefaultSmallGreySmokeSystem;   // +0xCDC
    ParticleSystemTypeClass * unknown_ce0;   // +0xCE0 DefaultSparkSystem; particle system created by EBolt setup
    ParticleSystemTypeClass * DefaultLargeRedSmokeSystem;   // +0xCE4
    ParticleSystemTypeClass * DefaultSmallRedSmokeSystem;   // +0xCE8
    ParticleSystemTypeClass * DefaultDebrisSmokeSystem;   // +0xCEC
    ParticleSystemTypeClass * DefaultFireStreamSystem;   // +0xCF0
    ParticleSystemTypeClass * unknown_cf4;   // +0xCF4 DefaultFirestormExplosionSystem; the particle system that warhead makes
    ParticleSystemTypeClass * DefaultTestParticleSystem;   // +0xCF8
    ParticleSystemTypeClass * DefaultRepairParticleSystem;   // +0xCFC
    double                   unknown_d00;   // +0xD00 MyEffectivenessCoefficientDefault; default MyEffectivenessCoefficient (TechnoType Read_INI)
    double                   unknown_d08;   // +0xD08 TargetEffectivenessCoefficientDefault; default TargetEffectivenessCoefficient
    double                   unknown_d10;   // +0xD10 TargetSpecialThreatCoefficientDefault; default TargetSpecialThreatCoefficient
    double                   unknown_d18;   // +0xD18 TargetStrengthCoefficientDefault; default TargetStrengthCoefficient
    double                   unknown_d20;   // +0xD20 TargetDistanceCoefficientDefault; default TargetDistanceCoefficient
    double                   DumbMyEffectivenessCoefficient;   // +0xD28
    double                   DumbTargetEffectivenessCoefficient;   // +0xD30
    double                   DumbTargetSpecialThreatCoefficient;   // +0xD38
    double                   DumbTargetStrengthCoefficient;   // +0xD40
    double                   DumbTargetDistanceCoefficient;   // +0xD48
    double                   EnemyHouseThreatBonus;   // +0xD50
    int                      HunterSeekerDetonateProximity;   // +0xD58
    int                      HunterSeekerDescendProximity;   // +0xD5C
    int                      HunterSeekerDescentSpeed;   // +0xD60
    int                      HunterSeekerAscentSpeed;   // +0xD64
    int                      HunterSeekerEmergeSpeed;   // +0xD68
    char unknown_d6c[0xD70 - 0xD6C];
    double                   TurboBoost;   // +0xD70
    double                   AttackInterval;   // +0xD78
    double                   AttackDelay;   // +0xD80
    double                   PowerEmergency;   // +0xD88
    double                   AirstripRatio;   // +0xD90
    int                      AirstripLimit;   // +0xD98
    char unknown_d9c[0xDA0 - 0xD9C];
    double                   HelipadRatio;   // +0xDA0
    int                      HelipadLimit;   // +0xDA8
    char unknown_dac[0xDB0 - 0xDAC];
    double                   TeslaRatio;   // +0xDB0
    int                      TeslaLimit;   // +0xDB8
    char unknown_dbc[0xDC0 - 0xDBC];
    double                   AARatio;   // +0xDC0
    int                      AALimit;   // +0xDC8
    char unknown_dcc[0xDD0 - 0xDCC];
    double                   DefenseRatio;   // +0xDD0
    int                      DefenseLimit;   // +0xDD8
    char unknown_ddc[0xDE0 - 0xDDC];
    double                   WarRatio;   // +0xDE0
    int                      WarLimit;   // +0xDE8
    char unknown_dec[0xDF0 - 0xDEC];
    double                   BarracksRatio;   // +0xDF0
    int                      BarracksLimit;   // +0xDF8
    int                      RefineryLimit;   // +0xDFC
    double                   RefineryRatio;   // +0xE00
    int                      BaseSizeAdd;   // +0xE08
    int                      PowerSurplus;   // +0xE0C
    int                      InfantryReserve;   // +0xE10
    int                      InfantryBaseMult;   // +0xE14
    int                      SoloCrateMoney;   // +0xE18
    int                      unknown_e1c;   // +0xE1C TreeStrength; default terrain strength (TerrainTypeClass::Read_INI)
    UnitTypeClass *          UnitCrateType;   // +0xE20
    char unknown_e24[0xE28 - 0xE24];
    double                   unknown_e28;   // +0xE28 PatrolScan; minutes (TeamClass script handler 0x006BB0F0: how often a team re-aims, times 900 frames; hypothesis)
    TypeList<int>            TeamDelays;   // +0xE30
    TypeList<int>            AIHateDelays;   // +0xE4C
    int                      DissolveUnfilledTeamDelay;   // +0xE68
    TypeList<int>            AIIonCannonConYardValue;   // +0xE6C
    TypeList<int>            AIIonCannonWarFactoryValue;   // +0xE88
    TypeList<int>            AIIonCannonPowerValue;   // +0xEA4
    TypeList<int>            AIIonCannonEngineerValue;   // +0xEC0
    TypeList<int>            AIIonCannonThiefValue;   // +0xEDC
    TypeList<int>            AIIonCannonHarvesterValue;   // +0xEF8
    TypeList<int>            AIIonCannonMCVValue;   // +0xF14
    TypeList<int>            AIIonCannonAPCValue;   // +0xF30
    TypeList<int>            AIIonCannonBaseDefenseValue;   // +0xF4C
    TypeList<int>            AIIonCannonPlugValue;   // +0xF68
    TypeList<int>            AIIonCannonHelipadValue;   // +0xF84
    TypeList<int>            AIIonCannonTempleValue;   // +0xFA0
    int                      AIAlternateProductionCreditCutoff;   // +0xFBC
    TypeList<int>            MultiplayerAICM;   // +0xFC0
    TypeList<int>            AIVirtualPurifiers;   // +0xFDC
    TypeList<int>            MinimumAIDefensiveTeams;   // +0xFF8
    TypeList<int>            MaximumAIDefensiveTeams;   // +0x1014
    TypeList<int>            TotalAITeamCap;   // +0x1030
    char unknown_104c[0x1050 - 0x104C];
    double                   AIUseTurbineUpgradeProbability;   // +0x1050
    TypeList<int>            FillEarliestTeamProbability;   // +0x1058
    char unknown_1074[0x1078 - 0x1074];
    double                   CloakDelay;   // +0x1078
    double                   GameSpeedBias;   // +0x1080
    double                   BaseBias;   // +0x1088
    double                   ExpSpread;   // +0x1090
    int                      FireSupress;   // +0x1098
    int                      MaxIQ;   // +0x109C
    int                      IQSuperWeapons;   // +0x10A0
    int                      IQProduction;   // +0x10A4
    int                      unknown_10a8;   // +0x10A8 IQGuardArea; (UnitClass slot 261: compared with the house +0x194)
    int                      IQRepairSell;   // +0x10AC
    int                      unknown_10b0;   // +0x10B0 IQCrush; (UnitClass 0x00707170: a minimum house value)
    int                      IQScatter;   // +0x10B4
    int                      unknown_10b8;   // +0x10B8 IQContentScan; (TechnoClass slot 90: compared with the house +0x194)
    int                      IQAircraft;   // +0x10BC
    int                      IQHarvester;   // +0x10C0
    int                      IQSellBack;   // +0x10C4
    int                      AIBaseSpacing;   // +0x10C8
    CrateType                SilverCrate;   // +0x10CC
    CrateType                WoodCrate;   // +0x10D0
    CrateType                WaterCrate;   // +0x10D4
    int                      CrateMinimum;   // +0x10D8
    int                      CrateMaximum;   // +0x10DC
    int                      unknown_10e0;   // +0x10E0
    AnimTypeClass *          DropZoneAnim;   // +0x10E4
    int                      MinMoney;   // +0x10E8
    int                      Money;   // +0x10EC
    int                      MaxMoney;   // +0x10F0
    int                      MoneyIncrement;   // +0x10F4
    int                      MinUnitCount;   // +0x10F8
    int                      UnitCount;   // +0x10FC
    int                      MaxUnitCount;   // +0x1100
    int                      TechLevel;   // +0x1104
    int                      GameSpeed;   // +0x1108
    int                      AIDifficulty;   // +0x110C
    int                      AIPlayers;   // +0x1110
    bool                     BridgeDestruction;   // +0x1114
    bool                     ShadowGrow;   // +0x1115
    bool                     Shroud;   // +0x1116
    bool                     Bases;   // +0x1117
    bool                     TiberiumGrows;   // +0x1118
    bool                     Crates;   // +0x1119
    bool                     CaptureTheFlag;   // +0x111A
    bool                     HarvesterTruce;   // +0x111B
    bool                     MultiEngineer;   // +0x111C
    bool                     unknown_111d;   // +0x111D AlliesAllowed; computers ally against the humans (House.cpp; hypothesis)
    bool                     ShortGame;   // +0x111E
    bool                     FogOfWar;   // +0x111F
    bool                     MCVRedeploys;   // +0x1120
    bool                     SuperWeaponsAllowed;   // +0x1121
    bool                     BuildOffAlly;   // +0x1122
    char unknown_1123[0x1124 - 0x1123];
    int                      DropZoneRadius;   // +0x1124
    double                   MessageDelay;   // +0x1128
    double                   SavourDelay;   // +0x1130
    int                      MaxPlayers;   // +0x1138
    char unknown_113c[0x1140 - 0x113C];
    double                   BaseDefenseDelay;   // +0x1140
    int                      SuspendPriority;   // +0x1148
    char unknown_114c[0x1150 - 0x114C];
    double                   unknown_1150;   // +0x1150 SuspendDelay; minutes (TeamClass 0x006BA8E0: a team's leaving timer, times 900 frames; hypothesis)
    double                   SurvivorRate;   // +0x1158
    int                      unknown_1160;   // +0x1160 AlliedSurvivorDivisor; BuildingClass slot 172
    int                      unknown_1164;   // +0x1164 SovietSurvivorDivisor; BuildingClass slot 172, owner index 1
    double                   ReloadRate;   // +0x1168
    double                   AutocreateTime;   // +0x1170
    double                   unknown_1178;   // +0x1178 BuildupTime; buildup time in minutes (BuildingType slot 48; hypothesis)
    int                      unknown_1180;   // +0x1180 HarvesterLoadRate; (UnitClass 0x007013A0: a harvesting pause in frames)
    char unknown_1184[0x1188 - 0x1184];
    double                   HarvesterDumpRate;   // +0x1188
    int                      unknown_1190;   // +0x1190 AtomDamage; damage (AnimClass 0x00422BA0)
    char unknown_1194[0x1198 - 0x1194];
    DifficultyClass          Diff[3];   // +0x1198
    char unknown_1288[0x1298 - 0x1288];
    double                   GrowthRate;   // +0x1298
    double                   ShroudRate;   // +0x12A0
    double                   FogRate;   // +0x12A8
    double                   IceGrowthRate;   // +0x12B0
    double                   VeinGrowthRate;   // +0x12B8
    int                      IceSolidifyFrameTime;   // +0x12C0
    char unknown_12c4[0x12C8 - 0x12C4];
    double                   AmbientChangeRate;   // +0x12C8
    double                   AmbientChangeStep;   // +0x12D0
    double                   CrateRegen;   // +0x12D8
    double                   TimerWarning;   // +0x12E0
    int                      TiberiumTransmogrify;   // +0x12E8
    char unknown_12ec[0x12F0 - 0x12EC];
    double                   unknown_12f0;   // +0x12F0
    double                   unknown_12f8;   // +0x12F8
    double                   unknown_1300;   // +0x1300
    double                   unknown_1308;   // +0x1308
    double                   SpeakDelay;   // +0x1310
    double                   DamageDelay;   // +0x1318
    int                      unknown_1320;   // +0x1320 Gravity; WeaponTypeClass speed default; hypothesis
    int                      unknown_1324;   // +0x1324 LeptonsPerSightIncrease; height per level step (TechnoClass slot 70: Z / this * 10)
    int                      unknown_1328;   // +0x1328 Incoming; Infantry firing range threshold (00507530)
    int                      MinDamage;   // +0x132C
    int                      MaxDamage;   // +0x1330
    int                      unknown_1334;   // +0x1334 RepairStep; repair step (TechnoType slots 44, 45; hypothesis)
    double                   unknown_1338;   // +0x1338 RepairPercent; repair cost factor (slot 44; hypothesis)
    int                      unknown_1340;   // +0x1340 IRepairStep; InfantryType repair step (slot 45)
    char unknown_1344[0x1348 - 0x1344];
    double                   unknown_1348;   // +0x1348 RepairRate; self-heal interval in minutes (TechnoClass slot 157)
    double                   URepairRate;   // +0x1350
    double                   IRepairRate;   // +0x1358
    double                   unknown_1360;   // +0x1360
    double                   unknown_1368;   // +0x1368 ConditionYellow; health-ratio thresholds (hypothesis: the condition yellow/red values)
    double                   unknown_1370;   // +0x1370 ConditionRed
    double                   IdleActionFrequency;   // +0x1378
    int                      unknown_1380;   // +0x1380 CloseEnough; how far a unit outside a team may stray when pathing (FootClass 0x004C3000; hypothesis)
    int                      unknown_1384;   // +0x1384 Stray; (TeamClass 0x006BE6A0: a distance for team scripts; hypothesis)
    int                      unknown_1388;   // +0x1388 RelaxedStray; (TeamClass 0x006BE6A0)
    int                      GuardModeStray;   // +0x138C
    int                      unknown_1390;   // +0x1390 Crush; a distance (UnitClass slot 304: crush range; hypothesis)
    int                      CrateRadius;   // +0x1394
    int                      HomingScatter;   // +0x1398
    int                      unknown_139c;   // +0x139C BallisticScatter; a scatter distance (BulletClass slot 118: twice it bounds a flak bullet's random miss; hypothesis: BallisticScatter)
    double                   unknown_13a0;   // +0x13A0 RefundPercent; refund factor (TechnoType slot 46; hypothesis)
    int                      unknown_13a8;   // +0x13A8 BridgeStrength; damage (InfantryClass slot 93: a C4 charge)
    char unknown_13ac[0x13B0 - 0x13AC];
    double                   unknown_13b0;   // +0x13B0 BuildSpeed; cost factor (TechnoType slot 34)
    double                   unknown_13b8;   // +0x13B8 C4Delay; C4 delay in minutes (InfantryClass slot 93; hypothesis)
    int                      CreditReserve;   // +0x13C0
    char unknown_13c4[0x13C8 - 0x13C4];
    double                   unknown_13c8;   // +0x13C8 PathDelay; minutes to wait after a failed path (FootClass 0x004C3000)
    int                      unknown_13d0;   // +0x13D0 BlockagePathDelay; frames of the movement timer (FootClass slot 260)
    char unknown_13d4[0x13D8 - 0x13D4];
    double                   MovieTime;   // +0x13D8
    int                      TiberiumNearScan;   // +0x13E0
    int                      TiberiumFarScan;   // +0x13E4
    int                      unknown_13e8;   // +0x13E8 LightningDeferment; (TeamClass script handler 0x006BC460)
    int                      LightningDamage;   // +0x13EC
    int                      LightningStormDuration;   // +0x13F0
    int                      LightningHitDelay;   // +0x13F4
    int                      LightningScatterDelay;   // +0x13F8
    int                      LightningCellSpread;   // +0x13FC
    int                      LightningSeparation;   // +0x1400
    bool                     LightningPrintText;   // +0x1404
    char unknown_1405[0x1408 - 0x1405];
    WarheadTypeClass *       LightningWarhead;   // +0x1408
    int                      unknown_140c;   // +0x140C CollapseChance; signed random threshold (Wave damage)
    int                      unknown_1410;   // +0x1410 WeedCapacity; silo storage (House.cpp; BuildingType slot 29 weeder)
    int                      HarvestersPerRefinery;   // +0x1414
    int                      ExtraUnitLight;   // +0x1418
    int                      ExtraInfantryLight;   // +0x141C
    int                      ExtraAircraftLight;   // +0x1420
    bool                     Paranoid;   // +0x1424
    bool                     CurleyShuffle;   // +0x1425
    bool                     BlendedFog;   // +0x1426
    bool                     CompEasyBonus;   // +0x1427
    bool                     FineDiffControl;   // +0x1428
    bool                     unknown_1429;   // +0x1429 TiberiumExplosive; (UnitClass 0x006FD3A0)
    bool                     EnemyHealth;   // +0x142A
    bool                     unknown_142b;   // +0x142B AllyReveal; (DisplayClass 0x0049E110/0x0049E000: allied buildings too)
    bool                     unknown_142c;   // +0x142C SeparateAircraft; BuildingType slots 33/43: no harvester discount
    bool                     unknown_142d;   // +0x142D TreeTargeting; (TechnoClass slot 208: any weapon may target kind 36)
    bool                     NamedCivilians;   // +0x142E
    bool                     unknown_142f;   // +0x142F PlayerAutoCrush; (UnitClass 0x00707170)
    bool                     PlayerReturnFire;   // +0x1430
    bool                     unknown_1431;   // +0x1431 PlayerScatter; (InfantryClass slot 87: scatter freely)
    bool                     RevealByHeight;   // +0x1432
    bool                     AllowShroudedSubteranneanMoves;   // +0x1433
    bool                     ShroudGrow;   // +0x1434
    bool                     NodAIBuildsWalls;   // +0x1435
    bool                     AIBuildsWalls;   // +0x1436
    bool                     unknown_1437;   // +0x1437 UseMinDefenseRule; AI triggers wait for the minimum (AITriggerType 0x0041C990; hypothesis)
    AnimTypeClass const *    unknown_1438;   // +0x1438 EMPulseSparkles; EMPulse animation, observed 004B4E30
    float                    unknown_143c;   // +0x143C EngineerCaptureLevel; an Engineer captures a building above this health ratio (InfantryClass slot 28)
    float                    EngineerCaptureLevel;   // +0x1440
    unsigned int             TalkBubbleTime;   // +0x1444
    int                      RadDurationMultiple;   // +0x1448 RadDurationMultiple; (RadSiteClass; hypothesis)
    int                      unknown_144c;   // +0x144C RadApplicationDelay; frames between tiberium damage checks (FootClass::AI; hypothesis)
    int                      RadLevelMax;   // +0x1450
    int                      RadLevelDelay;   // +0x1454 RadLevelDelay; (RadSiteClass; hypothesis)
    int                      RadLightDelay;   // +0x1458 RadLightDelay; (RadSiteClass; hypothesis)
    char unknown_145c[0x1460 - 0x145C];
    double                   unknown_1460;   // +0x1460 RadLevelFactor; tiberium damage factor (FootClass::AI)
    double                   RadLightFactor;   // +0x1468
    double                   RadTintFactor;   // +0x1470
    RGBClass                 RadColor;   // +0x1478
    char unknown_147b[0x147C - 0x147B];
    WarheadTypeClass *       unknown_147c;   // +0x147C RadSiteWarhead; the tiberium damage warhead (FootClass::AI)
    int                      unknown_1480;   // +0x1480 ElevationIncrement; (divisor of a height difference; TechnoClass 0x006C4A70)
    char unknown_1484[0x1488 - 0x1484];
    double                   unknown_1488;   // +0x1488 ElevationIncrementBonus; (scale)
    double                   unknown_1490;   // +0x1490 ElevationBonusCap; (limit)
    bool                     unknown_1498;   // +0x1498 AlliedWallTransparency; observed condition in wall-transition helper004BBE60
    char unknown_1499[0x14A0 - 0x1499];
    double                   WallPenetratorThreshold;   // +0x14A0
    RGBClass                 LocalRadarColor;   // +0x14A8
    RGBClass                 LineTrailColorOverride;   // +0x14AB
    RGBClass                 ChronoBeamColor;   // +0x14AE
    char unknown_14b1[0x14B4 - 0x14B1];
    int                      OreTwinkleChance;   // +0x14B4
    AnimTypeClass const *    OreTwinkle;   // +0x14B8
    char unknown_14bc[0x14C0 - 0x14BC];
};

// Ground (the land types' movement costs): shared/ground_type.hpp.
#include "shared/ground_type.hpp"

// The crate kinds' [Powerups] values (RulesClass::Powerups; Westwood's names):
// the relative chance, the animation, whether the crate may appear on water
// and the kind's value. CrateNames: shared/ini_enums.hpp.
extern int CrateShares[19];                     // 0x007D38DC
extern int CrateAnims[19];                      // 0x007D3928
extern bool CrateWater[19];                     // 0x00851118
extern double CrateData[19];                    // 0x00851080

extern RulesClass *Rules;                       // 0x00839848

#endif
