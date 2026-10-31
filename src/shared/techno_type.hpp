// TechnoTypeClass: the type layer shared by building, unit, infantry and
// aircraft types (TechnoType.cpp, members 0x006D9B40-0x006DFAA0; RTTI
// vtables 0x007AD080 primary (48 slots), 0x007AD064 IRTTITypeInfo at +4,
// 0x007AD05C INoticeSink, 0x007AD054 INoticeSource).
//
// Layout from the constructor 0x006D9B40, the NoInitClass constructor
// 0x006DA6E0, the destructor 0x006DA950, Save/GetSizeMax 0x006DEC10/
// 0x006DEEE0 and Read_INI 0x006DAF60. Member names are the rules INI keys
// Read_INI reads into each member (the key pushed before the INIClass call
// whose result is stored there); members no key names keep unknown_ names.
// All are hypotheses about meaning; offsets and widths are evidenced.
//   +0x000  ObjectTypeClass (0x264)
//   +0x264  WalkRate .. +0x2E0 CloakingSpeed (ints and doubles)
//   +0x26C, +0x27E  AbilitiesStruct (18 bools each, zeroed with memset)
//   +0x2E4  TypeList<VoxelAnimTypeClass *> DebrisTypes  (TypeList: 0x1C)
//   +0x300  TypeList<int> DebrisMaximums, +0x31C GUID Locomotor
//   +0x3AC  TypeList<BuildingTypeClass *> Dock
//   +0x3D0..+0x494  eight TypeList<int> voice/sound lists
//   +0x4B0..+0x4FC  twenty sound indexes (-1)
//   +0x510  TypeList<AnimTypeClass *> DebrisAnims
//   +0x560, +0x57C  TypeList<int> Prerequisite, PrerequisiteOverride
//   +0x5F2, +0x611  FixedString<25> cameo file names, +0x60C/+0x62C data
//   +0x644, +0x660  TypeList<AnimTypeClass *> Explosion, DestroyAnim
//   +0x68C, +0x6A8  TypeList<ParticleSystemTypeClass *>
//   +0x710  int unknown_710[15]   (-1)
//   +0x74C  WeaponStruct Weapon[15], +0x8F0 ClearAllWeapons,
//   +0x8F4  WeaponStruct EliteWeapon[15]
//   +0xA98..+0xB68  flags and jumpjet/spawn values
//   +0xB6C  palette file name (32 bytes), +0xB8C palette data
//   size 0xB90
// Every type is added to unknown_objects_ac0cb0 (0x00AC0CB0) and
// TechnoTypes (0x00A40AB8) and removed when destroyed.
#ifndef RA2_SHARED_TECHNO_TYPE_HPP
#define RA2_SHARED_TECHNO_TYPE_HPP

#include "shared/object_type.hpp"
#include "shared/palette_name.hpp"
#include "shared/leptons.hpp"
#include "shared/weapon_type.hpp"
class HouseClass;
#include "shared/crt_memory.hpp"
#include "shared/abilities.hpp"
#include "shared/ini_enums.hpp"

class VoxelAnimTypeClass;
class BuildingTypeClass;
class AnimTypeClass;
class ParticleSystemTypeClass;
class UnitTypeClass;
class AircraftTypeClass;
class TechnoTypeClass;

// WeaponTypeClass (Burst +0x9C; Techno.cpp reads +0xB4, +0x112, +0x126): shared/weapon_type.hpp.

// HouseClass and the player's house: shared/house.hpp.

// The veterancy abilities (VeteranAbilities=, EliteAbilities=): shared/abilities.hpp.

// One weapon slot: weapon, fire offset, barrel size, turret lock (0x1C).
struct WeaponStruct {
    WeaponTypeClass *WeaponType;        // +0x00
    CoordStruct FLH;                    // +0x04
    int BarrelLength;                   // +0x10
    int BarrelThickness;                // +0x14
    bool TurretLocked;                  // +0x18
};

// Recoil animation timing (TurretTravel=, BarrelTravel= ...; 0x14 bytes).
// No NoInitClass constructor: the load path rebuilds it too.
struct RecoilControl {
    RecoilControl() : Travel(2), CompressFrames(1), RecoverFrames(1), HoldFrames(1), unknown_10(false) {}
    int Travel;
    int CompressFrames;
    int RecoverFrames;
    int HoldFrames;
    bool unknown_10;
};

// The tactical view (pointer at 0x0083996C): see shared/gscreen.hpp
// (Sidebar proposal: the UnknownTactical83996c view collided with
// gscreen.hpp's `Tactical *unknown_tactical_83996c`; units that need
// Unknown_006A2900 should declare it on Tactical).

// The default locomotor class ID (0x007A1FD0, {4A582747-9839-11D1-B709-00A024DDAFD1}).
extern "C" GUID const unknown_clsid_7a1fd0;

class TechnoTypeClass : public ObjectTypeClass {
public:
    TechnoTypeClass(char const *ini_name, int speed_type);             // 0x006D9B40
    TechnoTypeClass(NoInitClass const &noinit);                         // 0x006DA6E0
    virtual ~TechnoTypeClass();                                         // 0x006DA950

    virtual HRESULT __stdcall Load(IStream *stream);                    // 0x006DE260
    virtual HRESULT __stdcall Save(IStream *stream, BOOL clear_dirty);  // 0x006DEC10
    virtual HRESULT __stdcall GetSizeMax(ULARGE_INTEGER *size);         // 0x006DEEE0
    virtual void Compute_CRC(WWCRCEngine &crc) const;                   // 0x006DEFD0 slot 13
    virtual bool Read_INI(CCINIClass &ini);                             // 0x006DAF60 slot 25

    // Overrides of ObjectTypeClass slots (meanings from RA1's
    // TechnoTypeClass, hypotheses).
    virtual int unknown_slot28() const;         // 0x006DACF0 Get_Ownable
    virtual int unknown_slot29() const;         // 0x006DE220 Max_Pips
    virtual int unknown_slot33(int house) const; // 0x006DAD30 Cost_Of(HouseClass *)
    virtual int unknown_slot34() const;         // 0x006DAD10
    virtual int unknown_slot38() const;         // 0x006DAE40 Get_Cameo_Data

    virtual bool unknown_slot40() const;                                // 0x006DACB0 (true)
    virtual bool unknown_slot41() const;                                // 0x006DACC0
    virtual bool unknown_slot42(Cell const &cell, HouseClass *house) const; // 0x006DE0E0
    virtual int Raw_Cost() const;                                       // 0x006DACE0 slot 43
    virtual int Repair_Cost() const;                                    // 0x006DAEC0 slot 44
    virtual int Repair_Step() const;                                    // 0x006DAF10 slot 45
    virtual int unknown_slot46(HouseClass *house, bool full) const;     // 0x006DAD80 (refund)
    virtual int Flight_Level() const;                                   // 0x006DF600 slot 47

    bool Is_Two_Shooter() const;                                        // 0x006DAF20
    WeaponStruct *Get_Weapon(int index);                                // 0x006DF5C0
    WeaponStruct *Get_Elite_Weapon(int index);                          // 0x006DF5E0
    void Load_Palette();                                                // 0x006DF620
    static void __fastcall Load_Palettes();                                      // 0x006DF640
    bool Has_Turret_Weapons() const;                                    // 0x006DF680
    void Set_Turret_Weapon(int weapon, int index);                      // 0x006DF690
    int Get_Turret_Weapon(int index) const;                             // 0x006DF6B0
    CoordStruct Damage_Smoke_Offset() const;                            // 0x006DF6C0

    int WalkRate;                               // +0x264
    int IdleRate;                               // +0x268
    AbilitiesStruct VeteranAbilities;           // +0x26C
    AbilitiesStruct EliteAbilities;             // +0x27E
    double SpecialThreatValue;                  // +0x290
    double MyEffectivenessCoefficient;          // +0x298
    double TargetEffectivenessCoefficient;      // +0x2A0
    double TargetSpecialThreatCoefficient;      // +0x2A8
    double TargetStrengthCoefficient;           // +0x2B0
    double TargetDistanceCoefficient;           // +0x2B8
    double ThreatAvoidanceCoefficient;          // +0x2C0
    int SlowdownDistance;                       // +0x2C8
    int unknown_2cc;                            // +0x2CC (not constructed)
    double DeaccelerationFactor;                // +0x2D0
    double AccelerationFactor;                  // +0x2D8
    int CloakingSpeed;                          // +0x2E0
    TypeList<VoxelAnimTypeClass *> DebrisTypes; // +0x2E4
    TypeList<int> DebrisMaximums;               // +0x300
    GUID Locomotor;                             // +0x31C
    int unknown_32c;                            // +0x32C (not constructed)
    double unknown_330;                         // +0x330
    double unknown_338;                         // +0x338
    double Weight;                              // +0x340
    double PhysicalSize;                        // +0x348
    double Size;                                // +0x350
    double SizeLimit;                           // +0x358
    bool HoverAttack;                           // +0x360
    int VHPScan;                                // +0x364
    int unknown_368;                            // +0x368
    int unknown_36c;                            // +0x36C (not constructed)
    double RollAngle;                           // +0x370
    double PitchSpeed;                          // +0x378
    double PitchAngle;                          // +0x380
    int BuildLimit;                             // +0x388
    int Category;                               // +0x38C
    int unknown_390;                            // +0x390 (cleared by the load path)
    int unknown_394;                            // +0x394 (not constructed)
    double DeployTime;                          // +0x398
    int FireAngle;                              // +0x3A0
    int PipScale;                               // +0x3A4
    int PipWrap;                                // +0x3A8
    TypeList<BuildingTypeClass *> Dock;         // +0x3AC
    BuildingTypeClass *DeploysInto;             // +0x3C8
    UnitTypeClass *UndeploysInto;               // +0x3CC
    TypeList<int> VoiceSelect;                  // +0x3D0
    TypeList<int> VoiceMove;                    // +0x3EC
    TypeList<int> VoiceAttack;                  // +0x408
    TypeList<int> VoiceSpecialAttack;           // +0x424
    TypeList<int> VoiceDie;                     // +0x440
    TypeList<int> VoiceFeedback;                // +0x45C
    TypeList<int> MoveSound;                    // +0x478
    TypeList<int> DieSound;                     // +0x494
    int AuxSound1;                              // +0x4B0
    int AuxSound2;                              // +0x4B4
    int CreateSound;                            // +0x4B8
    int DamageSound;                            // +0x4BC
    int ImpactWaterSound;                       // +0x4C0
    int ImpactLandSound;                        // +0x4C4
    int CrashingSound;                          // +0x4C8
    int SinkingSound;                           // +0x4CC
    int VoiceFalling;                           // +0x4D0
    int VoiceCrashing;                          // +0x4D4
    int VoiceSinking;                           // +0x4D8
    int VoiceEnter;                             // +0x4DC
    int VoiceCapture;                           // +0x4E0
    int TurretRotateSound;                      // +0x4E4
    int EnterTransportSound;                    // +0x4E8
    int LeaveTransportSound;                    // +0x4EC
    int DeploySound;                            // +0x4F0
    int UndeploySound;                          // +0x4F4
    int ChronoInSound;                          // +0x4F8
    int ChronoOutSound;                         // +0x4FC
    int MovementZone;                           // +0x500
    Leptons GuardRange;                         // +0x504
    int MaxDebris;                              // +0x508
    int MinDebris;                              // +0x50C
    TypeList<AnimTypeClass *> DebrisAnims;      // +0x510
    int Passengers;                             // +0x52C
    int Sight;                                  // +0x530
    bool RevealToAll;                           // +0x534
    int SensorsSight;                           // +0x538
    int DetectDisguiseRange;                    // +0x53C
    int BombSight;                              // +0x540
    int LeadershipRating;                       // +0x544
    int NavalTargeting;                         // +0x548
    int LandTargeting;                          // +0x54C
    int Cost;                                   // +0x550
    int Soylent;                                // +0x554
    int FlightLevel;                            // +0x558
    int TechLevel;                              // +0x55C
    TypeList<int> Prerequisite;                 // +0x560
    TypeList<int> PrerequisiteOverride;         // +0x57C
    int ThreatPosed;                            // +0x598
    int unknown_59c;                            // +0x59C
    int Speed;                                  // +0x5A0
    int SpeedType;                              // +0x5A4 (constructor argument)
    int InitialAmmo;                            // +0x5A8
    int Ammo;                                   // +0x5AC
    int IFVMode;                                // +0x5B0
    int AirRangeBonus;                          // +0x5B4
    int Reload;                                 // +0x5B8
    int EmptyReload;                            // +0x5BC
    int ReloadIncrement;                        // +0x5C0
    int RadialFireSegments;                     // +0x5C4
    int DeployFireWeapon;                       // +0x5C8
    bool DeployFire;                            // +0x5CC
    bool MobileFire;                            // +0x5CD
    bool OpportunityFire;                       // +0x5CE
    bool DistributedFire;                       // +0x5CF
    bool DamageReducesReadiness;                // +0x5D0
    float ReadinessReductionMultiplier;         // +0x5D4
    UnitTypeClass *UnloadingClass;              // +0x5D8
    bool AttackFriendlies;                      // +0x5DC
    bool AttackCursorOnFriendlies;              // +0x5DD
    int UndeployDelay;                          // +0x5E0
    bool PreventAttackMove;                     // +0x5E4
    int Owner;                                  // +0x5E8 (house bit set)
    int AIBasePlanningSide;                     // +0x5EC
    bool StupidHunt;                            // +0x5F0
    bool AllowedToStartInMultiplayer;           // +0x5F1
    FixedString<25> CameoFile;                  // +0x5F2
    void *CameoData;                            // +0x60C
    bool CameoAllocated;                        // +0x610 CameoData is owned
    FixedString<25> AltCameoFile;               // +0x611
    void *AltCameoData;                         // +0x62C
    bool AltCameoAllocated;                     // +0x630
    int RotCount;                               // +0x634
    int ROT;                                    // +0x638
    int TurretOffset;                           // +0x63C
    int Points;                                 // +0x640
    TypeList<AnimTypeClass *> Explosion;        // +0x644
    TypeList<AnimTypeClass *> DestroyAnim;      // +0x660
    ParticleSystemTypeClass *NaturalParticleSystem;            // +0x67C
    CoordStruct NaturalParticleLocation;                       // +0x680
    TypeList<ParticleSystemTypeClass *> DamageParticleSystems;  // +0x68C
    TypeList<ParticleSystemTypeClass *> DestroyParticleSystems; // +0x6A8
    CoordStruct DamageSmokeOffset;              // +0x6C4
    bool DamSmkOffScrnRel;                      // +0x6D0
    CoordStruct DestroySmokeOffset;             // +0x6D4
    CoordStruct RefnSmokeOffsetOne;             // +0x6E0
    CoordStruct RefnSmokeOffsetTwo;             // +0x6EC
    int ShadowIndex;                            // +0x6F8
    int Storage;                                // +0x6FC
    bool TurretNotExportedOnGround;             // +0x700
    bool Gunner;                                // +0x701
    bool HasTurretTooltips;                     // +0x702
    int TurretCount;                            // +0x704
    int WeaponCount;                            // +0x708 (not constructed)
    bool IsChargeTurret;                        // +0x70C
    int unknown_710[15];                        // +0x710 turret weapon indexes (-1)
    WeaponStruct Weapon[15];                    // +0x74C
    bool ClearAllWeapons;                       // +0x8F0
    WeaponStruct EliteWeapon[15];               // +0x8F4
    bool TypeImmune;                            // +0xA98
    bool MoveToShroud;                          // +0xA99
    bool Trainable;                             // +0xA9A
    bool unknown_a9b;                           // +0xA9B
    bool TargetLaser;                           // +0xA9C
    bool ImmuneToVeins;                         // +0xA9D
    bool TiberiumHeal;                          // +0xA9E
    bool CloakStop;                             // +0xA9F
    bool IsTrain;                               // +0xAA0
    bool IsDropship;                            // +0xAA1
    bool ToProtect;                             // +0xAA2
    bool Disableable;                           // +0xAA3
    bool unknown_aa4;                           // +0xAA4
    bool DoubleOwned;                           // +0xAA5
    bool Invisible;                             // +0xAA6
    bool RadarVisible;                          // +0xAA7
    bool unknown_aa8;                           // +0xAA8
    bool Sensors;                               // +0xAA9
    bool Nominal;                               // +0xAAA
    bool Turret;                                // +0xAAB
    bool TurretRecoil;                          // +0xAAC
    RecoilControl TurretAnimData;               // +0xAB0
    RecoilControl BarrelAnimData;               // +0xAC4
    bool Repairable;                            // +0xAD8
    bool Crewed;                                // +0xAD9
    bool Naval;                                 // +0xADA
    bool Remapable;                             // +0xADB
    bool Cloakable;                             // +0xADC
    bool GapGenerator;                          // +0xADD
    char GapRadiusInCells;                      // +0xADE
    char SuperGapRadiusInCells;                 // +0xADF
    bool Teleporter;                            // +0xAE0
    bool SelfHealing;                           // +0xAE1
    bool Explodes;                              // +0xAE2
    WeaponTypeClass *DeathWeapon;               // +0xAE4
    float DeathWeaponDamageModifier;            // +0xAE8
    bool NoAutoFire;                            // +0xAEC
    bool TurretSpins;                           // +0xAED
    bool Normalized;                            // +0xAEE
    bool ManualReload;                          // +0xAEF
    bool VisibleLoad;                           // +0xAF0
    bool LightningRod;                          // +0xAF1
    bool HunterSeeker;                          // +0xAF2
    bool Crusher;                               // +0xAF3
    bool TiltsWhenCrushes;                      // +0xAF4
    bool unknown_af5;                           // +0xAF5
    bool AutoCrush;                             // +0xAF6
    bool CanDisguise;                           // +0xAF7
    bool PermaDisguise;                         // +0xAF8
    bool DetectDisguise;                        // +0xAF9
    bool DisguiseWhenStill;                     // +0xAFA
    bool CanApproachTarget;                     // +0xAFB
    bool CanRecalcApproachTarget;               // +0xAFC
    bool ImmuneToPsionics;                      // +0xAFD (not constructed)
    bool ImmuneToRadiation;                     // +0xAFE
    bool Parasiteable;                          // +0xAFF (not constructed)
    bool DefaultToGuardArea;                    // +0xB00
    bool Warpable;                              // +0xB01
    bool ReselectIfLimboed;                     // +0xB02
    bool RejoinTeamIfLimboed;                   // +0xB03
    bool Spawned;                               // +0xB04
    AircraftTypeClass *Spawns;                  // +0xB08
    int SpawnsNumber;                           // +0xB0C
    int SpawnRegenRate;                         // +0xB10
    int SpawnReloadRate;                        // +0xB14
    bool MissileSpawn;                          // +0xB18
    bool Underwater;                            // +0xB19
    bool BalloonHover;                          // +0xB1A
    int SuppressionThreshold;                   // +0xB1C
    int JumpjetTurnRate;                        // +0xB20
    int JumpjetSpeed;                           // +0xB24
    float JumpjetClimb;                         // +0xB28
    float JumpjetCrash;                         // +0xB2C
    int JumpjetHeight;                          // +0xB30
    float JumpjetAccel;                         // +0xB34
    float JumpjetWobbles;                       // +0xB38
    bool JumpjetNoWobbles;                      // +0xB3C
    int JumpjetDeviation;                       // +0xB40
    bool JumpJet;                               // +0xB44
    bool Crashable;                             // +0xB45
    bool ConsideredAircraft;                    // +0xB46 (not constructed)
    bool Organic;                               // +0xB47 (not constructed)
    bool NoShadow;                              // +0xB48
    bool CanPassiveAquire;                      // +0xB49
    bool CanRetaliate;                          // +0xB4A
    bool RequiresStolenSovietTech;              // +0xB4B
    bool RequiresStolenAlliedTech;              // +0xB4C
    int RequiredHouses;                         // +0xB50
    int ForbiddenHouses;                        // +0xB54
    bool IsSelectableCombatant;                 // +0xB58
    bool Accelerates;                           // +0xB59
    bool DisableVoxelCache;                     // +0xB5A
    bool DisableShadowCache;                    // +0xB5B
    int ZFudgeCliff;                            // +0xB5C
    int ZFudgeColumn;                           // +0xB60
    int ZFudgeTunnel;                           // +0xB64
    int ZFudgeBridge;                           // +0xB68
    PaletteName PaletteFile;                    // +0xB6C
    void *Palette;                              // +0xB8C
};



typedef char TechnoTypeClass_size_check[(sizeof(TechnoTypeClass) == 0xB90) ? 1 : -1];

extern DynamicVectorClass<TechnoTypeClass *> TechnoTypes;   // 0x00A40AB8

#endif
