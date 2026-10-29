// BuildingTypeClass: structure types (BuildingType.cpp, members
// 0x00457AC0-0x0045EFFF; RTTI vtables 0x0079D1F8 primary (49 slots),
// 0x0079D1DC IRTTITypeInfo at +4, 0x0079D1D4 INoticeSink, 0x0079D1CC
// INoticeSource).
//
// Layout from the constructor 0x00457AC0, the load constructor 0x00458160,
// the destructor 0x004581C0, Read_INI 0x00459A00 (INI keys name the
// members), Load 0x0045DD90 and Save 0x0045E020:
//   +0x000  TechnoTypeClass (0xB90)
//   +0xB90  int ArrayIndex, +0xB94 foundation cell list, +0xB98 Buildup image
//   +0xBA4, +0xBB0  CoordStruct HalfDamageSmokeLocation1/2
//   +0xC38  FreeUnit, +0xC78 Foundation, +0xC7C Height
//   +0xCD4  BuildingAnimStruct Anims[18] (0x44 each)
//   +0x11A0..+0x11D0  owned image pointers with their flags
//   +0x1344..+0x1368  type flags (Radar .. NODBarracks)
//   +0x1404  VectorClass<TPoint3D> DockingOffsets
//   size 0x1418 (Size_Of)
// Every type is added to BuildingTypes (0x00A35CD8) and removed when
// destroyed. Hypotheses throughout; widths and offsets are evidenced.
// The class without shared/unknown_static_rect.hpp: units that use
// BuildingTypeClass but whose original has no such initializer (Power.CPP)
// include this header; shared/building_type.hpp adds the static.
#ifndef RA2_SHARED_BUILDING_TYPE_HPP
#define RA2_SHARED_BUILDING_TYPE_HPP

#include "shared/techno_type.hpp"
#include "shared/building_type_list.hpp"
#include "shared/rect.hpp"

#ifndef E_POINTER
#define E_POINTER ((HRESULT)0x80004003L)
#endif

class BuildingClass;
class IsometricTileTypeClass;
class OverlayTypeClass;
class UnitTypeClass;

// Building AI categories DontCare, Tech, Power, Resource, Infrastructure,
// Combat ({name, value} pairs at 0x007CFC40).
enum BuildCat {
    BUILDCAT_DONTCARE
};
// The name/value table (original data).
struct UnknownBuildCatEntry {
    char const *Name;
    int Value;
};
extern UnknownBuildCatEntry unknown_buildcat_table_7cfc40[6];     // 0x007CFC40
char const *__fastcall Name_From_BuildCat(BuildCat category);   // 0x00457A50
BuildCat __fastcall BuildCat_From_Name(char const *name);       // 0x00457A80

// A 3D point (Westwood's TPoint3D<T>; RTTI names VectorClass<TPoint3D<int>>,
// vtable 0x0079D2C0).
template <class T>
struct TPoint3D {
    TPoint3D() {}
    TPoint3D(T x, T y, T z) : X(x), Y(y), Z(z) {}
    bool operator==(TPoint3D<T> const &point) const { return X == point.X && Y == point.Y && Z == point.Z; }
    bool operator!=(TPoint3D<T> const &point) const { return !(*this == point); }
    T X;
    T Y;
    T Z;
};

// A 16-byte animation name, cleared with memset by the constructor body.
struct BuildingAnimName {
    void Clear() { memset(Buffer, 0, sizeof(Buffer)); }
    char Buffer[16];
};

// One building animation: names for the normal, damaged and garrisoned
// states and its placement (Anim*X=, Y=, ZAdjust=, YSort=, Powered=,
// PoweredLight=; 0x44 bytes).
struct BuildingAnimStruct {
    BuildingAnimName Anim;              // +0x00
    BuildingAnimName Damaged;           // +0x10
    BuildingAnimName Garrisoned;        // +0x20
    Point2D Offset;                     // +0x30 X/Y animation offset (type hypothesis)
    int ZAdjust;                        // +0x38
    int YSort;                          // +0x3C
    bool Powered;                       // +0x40 (true)
    bool PoweredLight;                  // +0x41
};

// Three values set together (0x004584D0; meaning unknown).
struct BuildingTriple {
    int unknown_00;
    int unknown_04;
    int unknown_08;
};

// BuildingClass: shared/building.hpp (BuildingType.cpp includes it for the constructor).

// Foundation cell counts by Foundation= value (0x007CFC70 widths,
// 0x007CFCC8 heights) and the lists Load points at (0x0084EDE8 cells,
// 0x0084F848 outer cells; 30 cells each).
extern int const unknown_foundation_width_7cfc70[];
extern int const unknown_foundation_height_7cfcc8[];
extern Cell const unknown_foundation_cells_84ede8[][30];
extern Cell const unknown_foundation_outside_84f848[][30];
// The cell height unit slot 31 scales Height by (0x00850298).
extern int unknown_850298;
// The cloak circle surface (0x008502A0; sized by the largest CloakRadiusInCells).
class BSurface;
extern BSurface *unknown_cloak_surface_8502a0;
// The power-off and repair shapes (0x008502A4, 0x008502A8).
extern void const *unknown_poweroff_shape_8502a4;
extern void const *unknown_wrench_shape_8502a8;

// The scenario (pointer at 0x00A3D290): UnknownIDSource in shared/abstract.hpp
// (its Theater at +0x838 is read here).

// The class ID GetClassID reports (0x007A1B30).
extern "C" GUID const unknown_clsid_building_type_7a1b30;

class BuildingTypeClass : public TechnoTypeClass {
public:
    BuildingTypeClass(char const *ini_name);                            // 0x00457AC0
    BuildingTypeClass(NoInitClass const &noinit);                       // 0x00458160
    virtual ~BuildingTypeClass();                                       // 0x004581C0

    virtual HRESULT __stdcall GetClassID(GUID *clsid);                  // 0x0045E0A0
    virtual HRESULT __stdcall Load(IStream *stream);                    // 0x0045DD90
    virtual HRESULT __stdcall Save(IStream *stream, BOOL clear_dirty);  // 0x0045E020
    virtual int Kind_Of() const;                                        // 0x0045ED00 (7)
    virtual int Size_Of() const;                                        // 0x0045ED10
    virtual void Compute_CRC(WWCRCEngine &crc) const;                   // 0x0045D8F0
    virtual int unknown_slot16() const;                                 // 0x0045ED20 (ArrayIndex)
    virtual bool Read_INI(CCINIClass &ini);                             // 0x00459A00
    virtual CoordStruct unknown_slot27(CoordStruct const &coord) const; // 0x0045D830 (on the ground)
    virtual int unknown_slot29() const;                                 // 0x00458980 Max_Pips
    virtual CoordStruct unknown_slot30() const;                         // 0x00458840
    virtual CoordStruct unknown_slot31() const;                         // 0x0045D8B0
    virtual bool unknown_slot32(Cell const &cell, HouseClass *house) const; // 0x00458420
    virtual int unknown_slot33(int house) const;                        // 0x00458A70
    virtual ObjectClass *unknown_slot35(HouseClass *house) const;           // 0x004584A0 (new building)
    virtual Cell const *unknown_slot36(int arg1) const;           // 0x004588C0
    virtual void *unknown_slot39() const;                               // 0x00458CE0
    virtual bool unknown_slot40() const;                                // 0x0045E740
    virtual bool unknown_slot41() const;                                // 0x0045E750
    virtual bool unknown_slot42(Cell const &cell, HouseClass *house) const; // 0x0045D880
    virtual int Raw_Cost() const;                                       // 0x004589F0
    virtual void *unknown_slot48();                                     // 0x0045E790 (new slot; the buildup image +0xB98, loaded on demand)

    static int __fastcall From_Name(char const *name);                  // 0x004583D0 (by ID)
    static int __fastcall From_Full_Name(char const *name);             // 0x00458380 (by Name)
    void unknown_func_4584d0(int index, int value0, int value1, int value2); // 0x004584D0
    int Width() const;                                                  // 0x00458930
    int Foundation_Height(bool bib) const;                              // 0x00458940
    void unknown_func_459640();                                         // 0x00459640
    void unknown_func_45eaa0();                                         // 0x0045EAA0 (RulesClass::Objects calls it for every type)
    void unknown_func_458ea0(int theater);                              // 0x00458EA0
    static BuildingTypeClass *__fastcall Find_Or_Make(char const *name); // 0x0045E0E0
    void Free_Buildup();                                                // 0x0045E920
    void Free_unknown_11cc();                                           // 0x0045E960
    void Free_unknown_11a0();                                           // 0x0045E9A0
    void Free_unknown_11a8();                                           // 0x0045E9E0
    void Free_unknown_11b0();                                           // 0x0045EA20
    void Free_unknown_11b8();                                           // 0x0045EA60
    // Prepares the cloak surface and resolves each type's ToTile= (0x0045E170).
    static void unknown_func_45e170();
    static void __fastcall unknown_func_45ebd0();                                // 0x0045EBD0 (each type's "ToTile" isometric tile type)
    // Loads the type images and buildups for a theater (0x00458600).
    static void __fastcall Init(int theater);
    static void unknown_func_458510();                                  // 0x00458510 (BUILDNGZ.SHP)
    bool unknown_func_45ec50() const;                                   // 0x0045EC50 (sensor array, tick tank, ICBM launcher or artillery)
    bool unknown_func_458e00(void **image, int *frame) const;            // 0x00458E00 (rubble image and frame 3)
    bool unknown_func_458e50(void **image, int *frame) const;            // 0x00458E50 (rubble image and frame count / 2 + 3)
    void Read_Rest(CCINIClass &ini);
    void Read_Rest(CCINIClass *ini);
    void Read_Rest();
    void Read_Fire_Offsets();                                           // inline (Read_INI)
    Rect unknown_func_45e290();                                         // 0x0045E290 (the image bounds; cached in unknown_11ec)
    int unknown_func_45ec90() const;                                    // 0x0045EC90
    Cell const *unknown_45e270() const;                           // 0x0045E270 (the outer-cell list of the foundation; foundation 9 uses 6)

    int unknown_458b10(Cell const &origin,HouseClass *house) const; // complete00458B10

    int ArrayIndex;                                  // +0xB90 index in BuildingTypes (slot 16)
    Cell const *FoundationData;                // +0xB94 occupation list (slot 36; set from Foundation= on load)
    void *BuildupData;                               // +0xB98 Buildup= image
    bool BuildupDataAllocated;                       // +0xB9C
    int BuildCat;                                    // +0xBA0
    CoordStruct HalfDamageSmokeLocation1;            // +0xBA4
    CoordStruct HalfDamageSmokeLocation2;            // +0xBB0
    int unknown_bbc;                                 // +0xBBC not constructed
    double GateCloseDelay;                           // +0xBC0 GateCloseDelay= (CRC hashes it as a double)
    int LightVisibility;                             // +0xBC8 5000
    int LightIntensity;                              // +0xBCC LightIntensity= x 1000
    int LightRedTint;                                // +0xBD0 1000000 (LightRedTint= x 1000)
    int LightGreenTint;                              // +0xBD4 LightGreenTint= x 1000
    int LightBlueTint;                               // +0xBD8 LightBlueTint= x 1000
    Point2D PrimaryFirePixelOffset;                  // +0xBDC 0xFFFF
    Point2D SecondaryFirePixelOffset;                // +0xBE4 0xFFFF
    OverlayTypeClass *ToOverlay;                     // +0xBEC ToOverlay= (art; swizzled by Load)
    IsometricTileTypeClass *unknown_bf0;             // +0xBF0 the "ToTile" isometric tile type (cleared by Load)
    char BuildupFile[16];                             // +0xBF4 Buildup= name (first byte cleared in the constructor body)
    int BuildupSound;                                // +0xC04 BuildupSound= (-1)
    int PackupSound;                                 // +0xC08 PackupSound= (-1)
    int CreateUnitSound;                             // +0xC0C CreateUnitSound= (-1)
    int UnitEnterSound;                              // +0xC10 UnitEnterSound= (-1)
    int UnitExitSound;                               // +0xC14 UnitExitSound= (-1)
    int WorkingSound;                                // +0xC18 WorkingSound= (-1)
    int NotWorkingSound;                             // +0xC1C NotWorkingSound= (-1)
    char PowersUpBuilding[24];                       // +0xC20 PowersUpBuilding= (first byte cleared in the constructor body)
    UnitTypeClass *FreeUnit;                         // +0xC38 FreeUnit= (swizzled by Load)
    int unknown_c3c;                                 // +0xC3C -1
    int Adjacent;                                    // +0xC40 3
    int Factory;                                     // +0xC44
    CoordStruct TargetCoordOffset;                   // +0xC48 TargetCoordOffset= (added to the center by BuildingClass slot 40)
    CoordStruct ExitCoord;                           // +0xC54 ExitCoord= (added to the coordinate by BuildingClass slot 44)
    Cell const *FoundationOutside;             // +0xC60 outer-cell list (set from Foundation= on load)
    int unknown_c64;                                 // +0xC64
    int Power;                                       // +0xC68
    int PowerDrain_c6c;                              // +0xC6C a negative Power= (name a hypothesis)
    int ExtraPower;                                  // +0xC70
    int ExtraPowerDrain_c74;                         // +0xC74 a negative ExtraPower= (name a hypothesis)
    int Foundation;                                  // +0xC78
    int Height;                                      // +0xC7C 2
    int OccupyHeight;                                // +0xC80 2
    int MidPoint;                                    // +0xC84
    int DoorStages;                                  // +0xC88
    BuildingTriple AnimFrames[6];                    // +0xC8C [0] buildup (Load_Images), [1] AnimIdle=, [2] AnimActive=,
                                                     //        [4] AnimAux1=, [5] AnimAux2= (art); 0x004584D0 sets one
    BuildingAnimStruct Anims[18];                    // +0xCD4 ActiveAnim .. IdleAnim (art INI)
    int Upgrades;                                    // +0x119C
    void *unknown_11a0;                              // +0x11A0
    bool unknown_11a4;                               // +0x11A4 11A0 owned
    void *unknown_11a8;                              // +0x11A8
    bool unknown_11ac;                               // +0x11AC
    void *unknown_11b0;                              // +0x11B0
    bool unknown_11b4;                               // +0x11B4
    void *unknown_11b8;                              // +0x11B8
    bool unknown_11bc;                               // +0x11BC
    void *DoorAnimData_11c0;                              // +0x11C0 DoorAnim image (hypothesis)
    void *SpecialZOverlayData_11c4;                              // +0x11C4 SpecialZOverlay image (hypothesis)
    int SpecialZOverlayZAdjust;                      // +0x11C8
    void *unknown_11cc;                              // +0x11CC
    bool unknown_11d0;                               // +0x11D0 11CC owned
    int NormalZAdjust;                               // +0x11D4
    int unknown_11d8;                                // +0x11D8
    int unknown_11dc;                                // +0x11DC
    int unknown_11e0;                                // +0x11E0
    Point2D ZShapePointMove;                         // +0x11E4
    Rect unknown_11ec;                               // +0x11EC copied from unknown_static_rect
    short ExtraLight;                                // +0x11FC
    bool TogglePower;                                // +0x11FE
    bool HasSpotlight;                               // +0x11FF
    bool IsTemple;                                   // +0x1200
    bool IsPlug;                                     // +0x1201
    bool HoverPad;                                   // +0x1202
    bool BaseNormal;                                 // +0x1203
    bool EligibileForAllyBuilding;                   // +0x1204
    bool EligibleForDelayKill;                       // +0x1205
    bool NeedsEngineer;                              // +0x1206
    int ProduceCashStartup;                          // +0x1208
    int ProduceCashAmount;                           // +0x120C
    int ProduceCashDelay;                            // +0x1210
    bool Bib;                                        // +0x1214
    bool Wall;                                       // +0x1215
    bool Capturable;                                 // +0x1216
    bool Powered;                                    // +0x1217
    bool Overpowerable;                              // +0x1218
    bool Spyable;                                    // +0x1219
    bool CanC4;                                      // +0x121A
    bool WantsExtraSpace;                            // +0x121B
    bool Unsellable;                                 // +0x121C
    bool ClickRepairable;                            // +0x121D
    bool CanBeOccupied;                              // +0x121E
    int MaxNumberOccupants;                          // +0x1220
    bool ShowOccupantPips;                           // +0x1224
    Point2D MuzzleFlash[10];                         // +0x1228 MuzzleFlash%d= (art; zero)
    Point2D DamageFireOffset[8];                     // +0x1278 DamageFireOffset%d= (art; zero)
    Point2D QueueingCell;                            // +0x12B8 QueueingCell= (art)
    int NumberImpassableRows;                        // +0x12C0 -1
    Point2D AddOccupy[8];                            // +0x12C4 AddOccupy%d= (art; not constructed)
    Point2D RemoveOccupy[8];                         // +0x1304 RemoveOccupy%d= (art; not constructed)
    bool Radar;                                      // +0x1344
    bool SpySat;                                     // +0x1345
    bool ChargeAnim;                                 // +0x1346
    bool IsAnimDelayedFire;                          // +0x1347
    bool SiloDamage;                                 // +0x1348
    bool UnitRepair;                                 // +0x1349
    bool UnitReload;                                 // +0x134A
    bool Cloning;                                    // +0x134B
    bool Flat;                                       // +0x134C
    bool DockUnload;                                 // +0x134D
    bool Recoilless;                                 // +0x134E
    bool HasStupidGuardMode;                         // +0x134F
    bool BridgeRepairHut;                            // +0x1350
    bool Gate;                                       // +0x1351
    bool SAM;                                        // +0x1352
    bool ConstructionYard;                           // +0x1353
    bool NukeSilo;                                   // +0x1354
    bool Refinery;                                   // +0x1355
    bool Weeder;                                     // +0x1356
    bool WeaponsFactory;                             // +0x1357
    bool LaserFencePost;                             // +0x1358
    bool LaserFence;                                 // +0x1359
    bool FirestormWall;                              // +0x135A
    bool Hospital;                                   // +0x135B
    bool Armory;                                     // +0x135C
    bool EMPulseCannon;                              // +0x135D
    bool TickTank;                                   // +0x135E
    bool TurretAnimIsVoxel;                          // +0x135F
    bool BarrelAnimIsVoxel;                          // +0x1360
    bool CloakGenerator;                             // +0x1361
    bool SensorArray;                                // +0x1362
    bool ICBMLauncher;                               // +0x1363
    bool Artillary;                                  // +0x1364
    bool Helipad;                                    // +0x1365
    bool OrePurifier;                                // +0x1366
    bool GDIBarracks;                                // +0x1367
    bool NODBarracks;                                // +0x1368
    float ChargedAnimTime;                           // +0x136C 999.0
    int DelayedFireDelay;                            // +0x1370
    int SuperWeapon;                                 // +0x1374 -1
    int SuperWeapon2;                                // +0x1378 -1
    int GateStages;                                  // +0x137C 9
    int PowersUpToLevel;                             // +0x1380 -1
    bool DamagedDoor;                                // +0x1384
    bool InvisibleInGame;                            // +0x1385
    bool TerrainPalette;                             // +0x1386
    bool PlaceAnywhere;                              // +0x1387
    bool ExtraDamageStage;                           // +0x1388
    bool AIBuildThis;                                // +0x1389
    bool IsBaseDefense;                              // +0x138A
    char CloakRadiusInCells;                         // +0x138B 20
    bool ConcentricRadialIndicator;                  // +0x138C
    int PsychicDetectionRadius;                      // +0x1390
    int BarrelStartPitch;                            // +0x1394 64
    char VoxelBarrelFile[16];                        // +0x1398 first byte cleared in the constructor body
    double unknown_13a8;                             // +0x13A8
    CoordStruct VoxelBarrelOffsetToPitchPivotPoint;  // +0x13B0 not constructed
    CoordStruct VoxelBarrelOffsetToRotatePivotPoint; // +0x13BC
    CoordStruct VoxelBarrelOffsetToBuildingPivotPoint; // +0x13C8
    CoordStruct VoxelBarrelOffsetToBarrelEnd;        // +0x13D4
    bool DemandLoad;                                 // +0x13E0
    bool DemandLoadBuildup;                          // +0x13E1
    bool FreeBuildup;                                // +0x13E2
    bool IsThreatRatingNode;                         // +0x13E3
    bool PrimaryFireDualOffset;                      // +0x13E4
    bool ProtectWithWall;                            // +0x13E5
    bool CanHideThings;                              // +0x13E6
    bool CanBeHidden;                                // +0x13E7
    bool CrateBeneath;                               // +0x13E8
    bool LeaveRubble;                                // +0x13E9
    bool CrateBeneathIsMoney;                        // +0x13EA
    char unknown_13eb[21];                           // +0x13EB first byte cleared in the constructor body
    int NumberOfDocks;                               // +0x1400 1
    VectorClass<TPoint3D<int> > DockingOffsets;            // +0x1404 DockingOffset%d= (one entry when constructed)
    int unknown_1414;                                // +0x1414 not constructed
};

typedef char BuildingTypeClass_size_check[(sizeof(BuildingTypeClass) == 0x1418) ? 1 : -1];


#endif
