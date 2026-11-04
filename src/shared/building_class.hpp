// BuildingClass: a structure (Building.CPP, 0x00438500-0x00454CEF; RTTI
// vtables 0x0079CBBC primary (293 slots: TechnoClass's 280 and 13 new),
// 0x0079CBA0 IRTTITypeInfo at +4, 0x0079CB98 INoticeSink at +8, 0x0079CB90
// INoticeSource at +0xC).
//
// Layout (constructor 0x00438CE0, NoInitClass constructor 0x00438C20,
// destructor 0x00439240, Load 0x0044EF90, Save 0x0044F2F0; Size_Of returns
// 0x5E0). Names are hypotheses unless they follow from the code:
//   +0x418  BuildingTypeClass *Type    the constructor's first argument
//   +0x41C  owned object (deleted by the destructor), swizzled
//   +0x420, +0x448, +0x4D8, +0x5A0  frame timers
//   +0x454  ObjectClass *[18], +0x49C ObjectClass *[8] (cleared, swizzled;
//           the destructor calls slot 60 on each of the eight)
//   +0x4C0  three swizzled pointers
//   +0x4E8  owned object (0x00537560 detaches it; deleted by the destructor)
//   +0x4F4  UnknownStage
//   +0x50C  Rect (unknown_static_rect), +0x51C CoordStruct
//   +0x53C, +0x554  DynamicVectorClass<InfantryClass *> (saved by count)
//   +0x570, +0x584  UnknownAudioController
//   +0x5C4  short (1000), +0x5C7 char (-1)
//   +0x5CC  CoordStruct (cleared by the constructor body)
// Every building joins Buildings (0x00A40AF8), the lists at 0x00AC0C80 and
// 0x00AC0BF8, and the techno index at 0x00ABFF58 (keyed by Fetch_ID).
// The class without shared/unknown_static_rect.hpp (see
// shared/building_type_class.hpp); shared/building.hpp adds the static.
#ifndef RA2_BUILDING_CLASS_HPP
#define RA2_BUILDING_CLASS_HPP

#include "shared/unknown_globals.hpp"
// The full class: shared/techno.hpp declares only a stub without this.
#define RA2_BUILDING_FULL
#include "shared/techno.hpp"
#include "shared/building_type_class.hpp"
#include "shared/super.hpp"
#include "shared/rect.hpp"
#include "shared/progress_timer.hpp"
#include "shared/light_source.hpp"

#ifdef RA2_BUILDING_TYPED_SPOTLIGHT
class BuildingLightClass;
#endif
class InfantryClass;
class Matrix3D;
class INIClass;
class BuildingClass;
class BulletClass;

extern bool unknown_flag_a3d340;        // 0x00A3D340 (slot 39)
// The original packed default Cell (0x0084ED10): BuildingClass slot 52 hands it to slots 289 and
// 291, 0x00452F50 copies it into a Cell; meaning unknown.
extern int unknown_84ed10;

// The object index (0x00ABFF58): shared/techno_index.hpp, shared/object_index.hpp.
#include "shared/techno_index.hpp"

// The sum of two cell offsets (an inline helper slots 264-266 expand;
// Point2D's own operator+ is out of line).
inline Point2D Point_Sum(Point2D const &a, Point2D const &b)
{
    return Point2D(a.X + b.X, a.Y + b.Y);
}

// Cell_At (the cell at a cell position, by value): shared/building_map.hpp
// (it needs Map; the Building unit includes gscreen.hpp after this header).

// The distance between two coordinates: shared/coord_distance.hpp.
#include "shared/coord_distance.hpp"

// A foot object's member BuildingClass reads (a view until shared/foot.hpp
// is installed): +0x494, a destination (cell or object; hypothesis).
struct UnknownBuildingFootView : TechnoClass {
    char unknown_418[0x494 - 0x418];
    AbstractClass *unknown_494;             // +0x494
};
// A unit's type (a view until shared/unit.hpp is installed).
class UnitTypeClass;
class FoggedObjectClass;
struct UnknownBuildingUnitView : TechnoClass {
    char unknown_418[0x5AC - 0x418];
    UnitTypeClass *Type;                    // +0x5AC
};

// The owned object at +0x4E8 (detached by 0x00537560, then deleted).
class UnknownBuilding4E8 : public AbstractClass {
public:
    void unknown_537540(int arg);       // 0x00537540
    void unknown_537560(int arg);       // 0x00537560
};

extern "C" GUID const CLSID_BuildingClass;  // 0x007A1C10

// A factory (a view of FactoryClass, shared/sidebar.hpp, which cannot be
// included with this header): the building's +0x41C and its house's
// factories.
class UnknownBuildingFactory {
public:
    void Unknown_004B97C0();                    // 0x004B97C0 (on removal from a strip)
    TechnoClass *Get_Object();                  // 0x004B9930 the object being built
};

// The members of a building animation the building code writes (a view of
// AnimClass, shared/anim.hpp, which cannot be included with this header).
struct UnknownBuildingAnimType {
    char unknown_000[0x318];
    bool unknown_318;                       // +0x318
};
struct UnknownBuildingAnim {
    char unknown_000[0xB0];
    UnknownBuildingAnimType *Type;          // +0xB0
    char unknown_0b4[0xBC - 0xB4];
    int unknown_bc;                         // +0xBC
    char unknown_0c0[0xE4 - 0xC0];
    int unknown_e4;                         // +0xE4
    char unknown_0e8[0x158 - 0xE8];
    char unknown_158;                       // +0x158 (layer)
    void unknown_422c10();                  // 0x00422C10 (AnimClass::unknown_func_422c10)
    void unknown_422c20();                  // 0x00422C20 (AnimClass::unknown_func_422c20)
};

// What slot 221 returns (a view; +0x138 is a countdown).
struct UnknownBuildingVictim {
    char unknown_000[0x138];
    unsigned int unknown_138;               // +0x138
};

// The cell slot 105 returns (+0x10A).
struct UnknownBuildingSlot105 {
    char unknown_000[0x10A];
    short unknown_10a;                      // +0x10A
};

class BuildingClass : public TechnoClass {
public:
    void Unknown_00450CB0(BulletClass *bullet, bool flag); // owner0200Z, declaration only
    void Update_Firestorm_Wall_00450950(); // 00450950 Firestorm wall state and crossing damage
    void Repair_AI_0044b9b0(); // 0044B9B0 AI repair/sale and paid repair ticks
    void Create_Damage_Fires_004395f0(); // 0x004395F0: damage-fire animations at art offsets
    void Factory_AI_0044b480(); // 0x0044B480: production completion and AI factory selection
    int Flush_For_Placement_0044a3d0(TechnoClass const *object, Cell const &cell); // original46-byte helper, nominal qualifiers hypothetical
    void Leave_Rubble_0043eba0(); // 0043EBA0: rubble footprint and crate beneath
    BuildingClass(BuildingTypeClass *type, HouseClass *house);         // 0x00438CE0
    void Set_Turret_Animation_Frame_0043bd40(int frame); // 0x0043BD40, nonvirtual
    BuildingClass(NoInitClass const &noinit);                         // 0x00438C20
    virtual ~BuildingClass();                                         // 0x00439240

    virtual HRESULT __stdcall GetClassID(GUID *clsid)                 // slot 3 0x00453C00 (inline)
    {
        if (clsid == 0) {
            return E_POINTER;
        }
        *clsid = CLSID_BuildingClass;
        return S_OK;
    }
    virtual HRESULT __stdcall Load(IStream *stream);                  // slot 5 0x0044EF90
    virtual HRESULT __stdcall Save(IStream *stream, BOOL clear_dirty);    // slot 6 0x0044F2F0
    virtual void Init();                                              // slot 9 0x0043F840
    virtual void Detach(AbstractClass *target, bool all = true);      // slot 10 0x00449E40
    virtual int Kind_Of() const { return 6; }                         // slot 11 0x00453C40 (inline)
    virtual int Size_Of() const { return sizeof(BuildingClass); }     // slot 12 0x00453BF0 (inline)
    virtual void Compute_CRC(WWCRCEngine &crc) const;                 // slot 13 0x0044F3C0
    virtual CoordStruct Center_Coord() const;                         // slot 18 0x00444080
    virtual CoordStruct unknown_slot19(TechnoClass *techno) const;    // slot 19 0x00444340
    virtual void AI();                                                // slot 23 0x0043C930
    virtual int unknown_slot25(bool arg1, int arg2);                   // slot 25 0x0044F600
    virtual void *unknown_slot26();                                   // slot 26 0x0044C5A0
    virtual int unknown_slot27(Cell const *cell, bool arg2, bool arg3);         // slot 27 0x00443BA0
    virtual int unknown_slot28(ObjectClass *object, bool arg2);        // slot 28 0x004438A0
    virtual bool unknown_slot31();                                    // slot 31 0x004527E0
    virtual ObjectTypeClass *Class_Of() const { return Type; }        // slot 33 0x00453C60 (inline)
    virtual wchar_t const *unknown_slot35() { return Type->UIName; }  // slot 35 0x00453C50 (inline)
    virtual bool unknown_slot36();                                    // slot 36 0x0044D8C0
    virtual bool unknown_slot37();                                    // slot 37 0x00445430
    virtual bool unknown_slot39();                                    // slot 39 0x0044A930
    virtual CoordStruct unknown_slot40();                              // slot 40 0x0044B430
    virtual CoordStruct unknown_slot41(int arg1) const;               // slot 41 0x004440E0
    virtual CoordStruct unknown_slot42() const;                       // slot 42 0x00453C70 (Coord less 128 in X and Y; best draft 47%)
    virtual CoordStruct unknown_slot43(int arg1);                   // slot 43 0x0044EA30
    virtual CoordStruct unknown_slot44(int arg1);                     // slot 44 0x0044A9A0
    virtual int unknown_slot45() const;                               // slot 45 0x00445380
    virtual bool unknown_slot52();                                     // slot 52 0x00442060
    virtual bool unknown_slot53(CoordStruct const *coord, int dir);    // slot 53 0x0043D3A0
    virtual void unknown_slot54(bool arg1);                            // slot 54 0x0044A080
    virtual void unknown_slot58(CoordStruct const &coord);                             // slot 58 0x0044EED0
    virtual void unknown_slot59(CoordStruct const &coord);                             // slot 59 0x0044EF30
    virtual int unknown_slot62(TechnoClass *techno);                   // slot 62 0x00440520
    virtual bool unknown_slot63(Rect *bounds, bool arg2, bool arg3);  // slot 63 0x0043A200
    virtual void unknown_slot67(int arg1, int arg2);                  // slot 67 0x0043A5E0
    virtual void unknown_slot68(int arg1, int arg2);                  // slot 68 0x0043A380
    virtual bool unknown_slot71(int arg1);                            // slot 71 0x0043BFC0
    virtual Rect unknown_slot73();                                    // slot 73 0x00450DD0
    virtual void unknown_slot74(int arg1);                            // slot 74 0x004519D0
    virtual bool unknown_slot77(int arg1, int arg2, int arg3, bool arg4);  // slot 77 0x0043FFE0
    virtual bool unknown_slot78(int arg1, int arg2, bool arg3);        // slot 78 0x0043FD30
    virtual void unknown_slot79(int arg1);                            // slot 79 0x00452060
    virtual void unknown_slot82(int arg1);                            // slot 82 0x00452E60
    virtual int unknown_slot86(int *damage, int distance, WarheadTypeClass *warhead, TechnoClass *source, bool forced, int arg6);  // slot 86 0x0043EE70
    virtual int unknown_slot95(RadioClass *radio, int message, long &param);         // slot 95 0x004397F0
    virtual bool unknown_slot96(HouseClass *house);                   // slot 96 0x00448FE0
    virtual void unknown_slot97(int arg1);                            // slot 97 0x00443680
    virtual void unknown_slot98(int arg1);                            // slot 98 0x004437A0
    virtual int unknown_slot101(CellClass *arg1, int arg2, int arg3, int arg4, bool arg5);   // slot 101 0x004453B0
    virtual bool unknown_slot122();                                   // slot 122 0x0044F3B0
    virtual int unknown_slot126();                                    // slot 126 0x00446920
    virtual int unknown_slot127();                                    // slot 127 0x00447240
    virtual int unknown_slot129();                                    // slot 129 0x00445620
    virtual int unknown_slot130();                                    // slot 130 0x00445940
    virtual int unknown_slot131();                                    // slot 131 0x00447250
    virtual int unknown_slot137();                                    // slot 137 0x00449290
    virtual int unknown_slot139();                                    // slot 139 0x00445950
    virtual int unknown_slot140();                                    // slot 140 0x00445B30
    virtual int unknown_slot141();                                    // slot 141 0x00447260
    virtual int unknown_slot142();                                    // slot 142 0x00448400
    virtual int unknown_slot143();                                    // slot 143 0x004499D0
    virtual bool unknown_slot153();                                   // slot 153 0x00450F50
    virtual bool unknown_slot160();                                     // slot 160 0x00452940
    virtual bool unknown_slot161();                                     // slot 161 0x00452A90
    virtual UnknownFacingDir unknown_slot162();                        // slot 162 0x004425A0
    virtual int unknown_slot166();                                    // slot 166 0x00449110
    virtual UnknownFacingDir unknown_slot170(AbstractClass *target);                  // slot 170 0x0043B7E0
    virtual int unknown_slot172();                                    // slot 172 0x0044C520
    virtual void unknown_slot173();                                   // slot 173 0x004528C0
    virtual int unknown_slot176();                                    // slot 176 0x0043B7A0
    virtual CoordStruct unknown_slot181(int arg1);                  // slot 181 0x0044EBF0
    virtual UnknownFacingDir unknown_slot183();                        // slot 183 0x004491E0
    virtual InfantryTypeClass *unknown_slot184();                     // slot 184 0x00449FB0
    virtual bool unknown_slot190(int *out_kind);                            // slot 190 0x00452220
    virtual bool unknown_slot195();                                   // slot 195 0x00450360
    virtual void unknown_slot216(int arg1);                            // slot 216 0x00449170
    virtual int unknown_slot218(AbstractClass *target, int weapon, bool check_range);        // slot 218 0x004443B0
    virtual AbstractClass *unknown_slot219(int arg1, CoordStruct const *coord, bool arg3); // slot 219 0x00442650
    virtual void unknown_slot220(AbstractClass *target);               // slot 220 0x00440450
    virtual bool unknown_slot222(HouseClass *house, int arg2);                  // slot 222 0x00444660
    virtual WeaponStruct *unknown_slot231(int index);                 // slot 231 0x0044D980
    virtual bool unknown_slot232();                                   // slot 232 0x0044D9D0
    virtual void unknown_slot234(int arg1);                           // slot 234 0x0044FB50
    virtual int unknown_slot254(int arg1);                            // slot 254 0x004521B0
    virtual void unknown_slot260(AbstractClass *target, int arg2);     // slot 260 0x00450F00
    virtual bool unknown_slot261(bool arg1, bool arg2);     // slot 261 0x004490B0
    virtual void unknown_slot264();                                   // slot 264 0x00451800
    virtual void unknown_slot265();                                   // slot 265 0x00451860
    virtual void unknown_slot266();                                   // slot 266 0x004518C0

    // New virtuals (slots 280-292); parameters from ret N, placeholders.
    virtual Cell unknown_slot280(TechnoClass *object);                  // slot 280 0x0044A400
    virtual int unknown_slot281(ObjectClass *object);                 // slot 281 0x004442B0 (distance)
    virtual void unknown_slot282(bool captured);                           // slot 282 0x004426D0 (ret 4)
    virtual void unknown_slot283();                                    // slot 283 0x00441EB0
    virtual void unknown_slot284(Point2D const &point, Rect const &bounds);  // slot 284 0x0043ABD0 (draws; ret 8)
    virtual UnknownFacingDir unknown_slot285(AbstractClass *target);  // slot 285 0x0043BBD0 (ret 8: the direction to a target)
    virtual void unknown_slot286(TechnoClass *last_contact, TechnoClass *source, bool forced, Cell const *offset);  // slot 286 0x0043E270
    virtual bool unknown_slot287();                                    // slot 287 0x00444580
    virtual void unknown_slot288(Cell cell);                            // slot 288 0x00450550
    virtual void unknown_slot289(Cell cell);                            // slot 289 0x00450400
    virtual void unknown_slot290(Cell cell);                            // slot 290 0x004507B0
    virtual void unknown_slot291(Cell cell);                            // slot 291 0x004506B0
    virtual int unknown_slot292();                                    // slot 292 0x0044D3D0

    bool unknown_44d880();                                            // 0x0044D880 (not a gate, or a gate in mission 24 whose +0x2A8 is done)
    int unknown_452800();                                             // 0x00452800 (SuperWeapon, or -1 while its AuxBuilding is missing)
    int unknown_452860();                                             // 0x00452860 (the same for SuperWeapon2)
    // The techno's +0x1A0/+0x1A4 pair as a cell offset (hypothesis: its map cell).
    Point2D const &unknown_cell_1a0() const { return *(Point2D const *)&unknown_1a0; }
    void unknown_44ca60(char const *name, int index, bool damaged, bool garrisoned, int arg5);  // 0x0044CA60 (starts the animation of an Anims index; hypothesis)
    void unknown_44cce0(AbstractClass *anim);                         // 0x0044CCE0 (Detach, for an animation not in unknown_49c)
    void unknown_443d60(int arg1);                                   // 0x00443D60 (Receive_Message 3 passes true)
    int unknown_4532f0();                                             // 0x004532F0 (TechnoClass slot 168)
    bool Unknown_00452EB0(TechnoClass *techno);                       // 0x00452EB0 (whether techno may enter; InfantryClass slot 132)
    void unknown_453300(); // complete00453300, original source-name hypothesis
    void unknown_452f50(int control); // complete00452F50, raw DWORD-control/void spelling hypothesis
    void Unknown_004536D0(InfantryClass *infantry);                   // 0x004536D0 (an Assaulter enters; InfantryClass slot 93)
    void Unknown_00452390(HouseClass *house);                         // 0x00452390 (an Agent infiltrates for house; InfantryClass slot 93)
    void unknown_44d070(bool damaged);                                // 0x0044D070 (TechnoClass slot 233: health at or below the rules' +0x1368)
    void unknown_4397c0();                                            // 0x004397C0 (slot 60 on each of unknown_49c, then clears them)
    void unknown_440140(Cell const *cell, bool arg2);           // 0x00440140 (slot 77, action 1)
    CoordStruct unknown_44ed60(int weapon, bool arg2);                // 0x0044ED60 (the voxel barrel's fire coordinate; slot 43)
#ifdef RA2_BUILDING_BARREL_MATRIX_VALUE
    Matrix3D unknown_453900(); // 00453900, hidden result, RET4
#else
    Matrix3D &unknown_453900(Matrix3D &result); // 00453900: writes/returns48-byte transform output, ABI hypothesis
#endif
    void Draw_Selection_Overlay_0043b660(Point2D const &point, Rect const &bounds); // 0043B660, observed ret8
    int unknown_43be20();                                             // 0x0043BE20 selects SHP frame from stage/state, health and occupants
    bool unknown_4454b0();                                            // 0x004454B0 (weapons factory guard step; slot 129)
    BuildingClass *unknown_44ddb0(int facing, bool through_fences, int max_range); // 0x0044DDB0, RET12; arg2 read as byte
    void unknown_44dc40(int arg1);                                    // 0x0044DC40 (laser fence post; slot 52)
    void Create_Fogged_Copy_00452c70(DynamicVectorClass<FoggedObjectClass *> *replacement_list, CellClass *replacement_cell, bool arg); // new owned RET12 helper
    void Reserve_Base_Area_004510d0(bool skip_inner_cells); // 004510D0, original RET4 and byte predicate
    void unknown_4513b0();                                            // 0x004513B0 (slot 52, when slot 31 fails)
    void unknown_44cfd0(int index);                                   // 0x0044CFD0 (-2: all of unknown_454)
    bool unknown_4538d0(ObjectTypeClass *type);                       // 0x004538D0 (whether slot 62 accepts a new object of the type for the house; hypothesis)
    void unknown_453850();                                            // 0x00453850 (restarts the ProduceCash timer unknown_5a0; pays the house ProduceCashAmount)
    void unknown_44d2d0(int layer);                                   // 0x0044D2D0 (the layer of every animation in unknown_454: 0x10 instead of 0xF when slot 25 answers 5)
    int unknown_449dd0();                                             // 0x00449DD0 (the type's +0xC6C, with +0xC74 when unknown_539, and that of each upgrade in unknown_4c0; 0 when slot 111 holds or unknown_530 is clear)
    void unknown_44dfc0(int arg1);                                    // 0x0044DFC0 (called with 0, 2, 4, 6 by unknown_44dbe0)
    void unknown_44e5a0(int arg1);                                    // 0x0044E5A0
    void unknown_44dbe0();                                            // 0x0044DBE0 (a laser fence post, outside a movie, refreshes its four links and the field)
    bool unknown_445ab0();                                            // 0x00445AB0 (an undeploying type: true for a sensor, tick tank, ICBM or artillery type, or per the game mode and the owner)
    void unknown_44a000(UnknownBuildingFactory *factory);             // 0x0044A000 (abandons the factory's production when no building can build it)
    void unknown_44c920(int index, bool damaged, bool garrisoned, int arg4);   // 0x0044C920 (starts the animation of an Anims index in the chosen state)
    bool unknown_44d900(BuildingTypeClass const *upgrade, HouseClass *house);        // 0x0044D900 (whether the upgrade type may power up this building; PowersUpToLevel)
    static void __fastcall Read_INI(CCINIClass &ini);                 // 0x0044AB80 ([Structures] entries)
    static void __fastcall unknown_44df40();
    void Update_Animations_0044BD40(); // owned Building animation-update hypothesis                                     // 0x0044DF40 (unknown_44dbe0's work for every laser fence post)
    void unknown_44ab00();                                            // 0x0044AB00 (the house's flags: the OR of the +0x1A8 of its Radar buildings)
    void unknown_44e260(int facing, bool enabled); // 0x0044E260, nonvirtual RET8
    bool Advance_Upgrade_Animation_0044c5d0(); // 0x0044C5D0, nonvirtual hypothesis
    void Write_Structure_INI_0044b250(INIClass &ini); // 0x0044B250, nonvirtual
    bool unknown_44c860();                                            // 0x0044C860 (removes the last upgrade; true when there was one)
    void unknown_44d0f0(int value, int frame);                        // 0x0044D0F0 (the animations whose type has +0x318 take the value and frame; all take the layer)
    bool unknown_44d7d0();                                            // 0x0044D7D0 (a gate not in mission 24, or not settled, is sent to mission 24; true for a non-gate or an open gate)
    void unknown_44d600();                                            // 0x0044D600 (sets unknown_5ba; refreshes the house's buildings, the owned object, the field and the powered animations)
    void unknown_44f8e0();                                            // 0x0044F8E0
    void unknown_44da20(InfantryClass *infantry);                     // 0x0044DA20 (moves the infantry to the end of unknown_53c)
    void unknown_44b870(int arg1, CoordStruct const &coord);          // 0x0044B870 (stores arg1, the type's DelayedFireDelay and the coordinate in unknown_5c8, unknown_5d8 and unknown_5cc; restarts animation 3 and 10)
    void unknown_44b910();                                            // 0x0044B910 (drops the infantry in unknown_53c that no longer head here; sets unknown_531)
    void unknown_44b770();                                            // 0x0044B770 (counts unknown_5d8 down; at zero runs the delayed action unknown_5c8: 1 fires at the target, 2 starts 0x00446820)
    void unknown_446820(CoordStruct coord);                           // 0x00446820 (creates an object at a coordinate; extent not yet bound)
    void unknown_44c9a0();                                            // 0x0044C9A0 (places each animation at the building's slot 42 coordinate plus its Anims offset)
    void unknown_44d6c0();                                            // 0x0044D6C0 (the reverse of unknown_44d600: clears unknown_5ba, starts the cloak and the powered animations)
    bool unknown_44daa0(ObjectClass *object);                         // 0x0044DAA0 (whether the object's centre is within the type's PsychicDetectionRadius cells)
    void Spawn_Survivors_0043f8e0(ObjectClass *attacker); // private owned hypothesis, RET4
    bool unknown_44db40(CellClass *cell);                             // 0x0044DB40 (the same for a cell's centre)
    void unknown_44d190();                                            // 0x0044D190 (slot 79's animation refresh: the slot 115 value and the cell's height level to every animation with +0x318, then the layer)
    void unknown_44d3e0();                                            // 0x0044D3E0 (powers the building on)
    void unknown_44d530();                                            // 0x0044D530 (powers the building off)
    Cell Offset_Toward_Map_Center_0044aa40(int mode); // private nominal class hypothesis, RET8 hidden Cell result
    bool unknown_449930();                                            // 0x00449930 (whether another object stands in a cell of the foundation)
    bool unknown_4444b0(bool take);                                   // 0x004444B0 (makes this the primary of its factory type among the house's buildings; true when unknown_32b changed)
    int unknown_449d40();                                             // 0x00449D40 (the power the building supplies: Power, ExtraPower when unknown_538, and the upgrades', times the health; 0 when off)
    int unknown_451710();                                             // 0x00451710 (the type's +0x11D8 if positive, else the first upgrade's)
    int unknown_451760();                                             // 0x00451760 (the same for +0x11DC)
    int unknown_4517b0();                                             // 0x004517B0 (the same for +0x11E0)
    int unknown_4508c0();                                             // 0x004508C0 (a mask of the FirestormWall buildings next to this one, bit per facing/2)
    bool unknown_450cb0(ObjectClass *object, bool damage); // 00450CB0; AL0/1, RET8, collision effects/damage
    void unknown_44f730();                                            // 0x0044F730 (power restored: starts the Powered animations, creates the PoweredLight ones that are missing)
    void unknown_44f800();                                            // 0x0044F800 (power lost: stops the Powered animations, removes the PoweredLight ones)
    bool Cell_Is_Impassable_Row_00453af0(CellClass const *cell); // 0x00453AF0, nonvirtual
    bool unknown_452be0();                                            // 0x00452BE0 (whether every cell of the foundation has the cell flag 0x400000)
    int unknown_451930();                                             // 0x00451930 (a radius in cells: PsychicDetectionRadius, a gap generator's, a sensor/cloak's, else the weapon's range)
    int unknown_4521e0(int arg1);                                     // 0x004521E0 (slot 254, then 0x006D86F0 when slot 203 holds)

    void Refresh_State_Animations_00453450(); // refreshes present idle/active names for current damage/occupants


    BuildingTypeClass *Type;                // +0x418
    AbstractClass *unknown_41c;             // +0x41C (owned; swizzled)
    CDTimerClass<FrameTimerClass> unknown_420;  // +0x420
    int unknown_42c;                        // +0x42C (-1)
    int unknown_430;                        // +0x430 (-1)
    int unknown_434;                        // +0x434
    AbstractClass *unknown_438;             // +0x438 (swizzled)
    int unknown_43c;                        // +0x43C (compared with Strength)
    AbstractClass *unknown_440;             // +0x440 (swizzled)
    AbstractClass *unknown_444;             // +0x444 (swizzled)
    CDTimerClass<FrameTimerClass> unknown_448;  // +0x448
    AbstractClass *unknown_454[18];         // +0x454 (swizzled)
    ObjectClass *unknown_49c[8];            // +0x49C (swizzled)
    bool unknown_4bc;                       // +0x4BC
    TechnoTypeClass *unknown_4c0[3];        // +0x4C0 (swizzled; unknown_5c6 of them are used)
    int unknown_4cc;                        // +0x4CC (-1)
    int unknown_4d0;                        // +0x4D0 (-1)
#ifdef RA2_BUILDING_TYPED_SPOTLIGHT
    BuildingLightClass *unknown_4d4;         // +0x4D4 native spotlight behavior00434370
#else
    AbstractClass *unknown_4d4;             // +0x4D4 (swizzled)
#endif
    ProgressTimerClass<FrameTimerClass> GateTimer; // +0x4D8, total duration +0x4E4
    LightSourceClass *unknown_4e8;        // +0x4E8 (owned)
    int unknown_4ec;                        // +0x4EC
    int unknown_4f0;                        // +0x4F0
    UnknownStage unknown_4f4;               // +0x4F4
    Rect unknown_50c;                       // +0x50C (unknown_static_rect)
    CoordStruct unknown_51c;                // +0x51C
    Point2D unknown_528;                    // +0x528 (from the object at 0x0083996C +0xB0; slot 73)
    bool unknown_530;                       // +0x530 (true)
    bool unknown_531;                       // +0x531
    int unknown_534;                        // +0x534
    bool unknown_538;                       // +0x538
    bool unknown_539;                       // +0x539
    DynamicVectorClass<InfantryClass *> unknown_53c;    // +0x53C
    DynamicVectorClass<InfantryClass *> unknown_554;    // +0x554
    int unknown_56c;                        // +0x56C
    UnknownAudioController unknown_570;     // +0x570
    UnknownAudioController unknown_584;     // +0x584
    bool unknown_598;                       // +0x598
    bool unknown_599;                       // +0x599
    bool unknown_59a;                       // +0x59A
    bool unknown_59b;                       // +0x59B
    bool unknown_59c;                       // +0x59C
    CDTimerClass<FrameTimerClass> unknown_5a0;  // +0x5A0
    bool unknown_5ac;                       // +0x5AC (true)
    bool unknown_5ad;                       // +0x5AD (slot 122 tests it)
    bool unknown_5ae;                       // +0x5AE
    bool unknown_5af;                       // +0x5AF
    bool unknown_5b0;                       // +0x5B0
    bool unknown_5b1;                       // +0x5B1
    bool unknown_5b2;                       // +0x5B2
    bool unknown_5b3;                       // +0x5B3
    bool unknown_5b4;                       // +0x5B4
    bool unknown_5b5;                       // +0x5B5
    bool unknown_5b6;                       // +0x5B6
    bool unknown_5b7;                       // +0x5B7
    bool unknown_5b8;                       // +0x5B8
    bool unknown_5b9;                       // +0x5B9
    bool unknown_5ba;                       // +0x5BA (true)
    char unknown_5bb;                       // +0x5BB
    char unknown_5bc;                       // +0x5BC (a cloak radius in cells, or 1)
    char unknown_5bd;                       // +0x5BD (a count; slot 25 compares it with 5 and 10)
    int unknown_5c0;                        // +0x5C0
    short unknown_5c4;                      // +0x5C4 (1000)
    char unknown_5c6;                       // +0x5C6 (count of unknown_4c0)
    char unknown_5c7;                       // +0x5C7 (-1)
    int unknown_5c8;                        // +0x5C8
#ifdef RA2_BUILDING_DELAY_POINT
    TPoint3D<int> unknown_5cc;
#else
    CoordStruct unknown_5cc;
#endif                // +0x5CC
    int unknown_5d8;                        // +0x5D8
    int unknown_5dc;                        // +0x5DC
};

// Every infantry (0x00A35E48): shared/techno.hpp. The one infantry member
// BuildingClass slot 173 reads (a view until infantry.hpp is installed):
struct UnknownBuildingInfantryView : TechnoClass {
    char unknown_418[0x494 - 0x418];
    ObjectClass *unknown_494;               // +0x494 (the building it heads for; hypothesis)
};

// Every building (0x00A40AF8): shared/techno.hpp.
// unknown_abstracts_ac0c80 (0x00AC0C80): shared/object_lists.hpp.

// Writes [Structures] (0x0044B200; takes the INI by pointer; Write_Scenario_INI
// 0x0065F980 passes its CCINIClass).
class INIClass;
void __fastcall Building_Write_All_INI_0044b200(INIClass *ini);

#endif
