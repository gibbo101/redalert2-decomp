// HouseClass: a player or computer side (House.cpp, unit 0x004E13F0; RTTI
// vtables 0x007A2DE0 primary (24 slots), 0x007A2DC4 IRTTITypeInfo at +4,
// 0x007A2DBC INoticeSink, 0x007A2DB4 INoticeSource, 0x007A2D74 IHouse at
// +0x24 (15 slots), 0x007A2D4C IPublicHouse at +0x28 (9 slots), 0x007A2D34
// IConnectionPointContainer at +0x2C (5 slots)). Replaces the stand-in in
// techno_type.hpp, whose member names (unknown_30, unknown_130,
// unknown_206/207, Cost_Multiplier, Unknown_004F52B0/Unknown_004F52F0) are
// kept.
//
// Partial layout (from the constructors 0x004E18C0 / 0x004E1680 and the
// interface methods; names are hypotheses, the interface method names
// follow Westwood's public IHouse; unknown spans are padding):
//   +0x0000  AbstractClass (0x24), +0x24 IHouse, +0x28 IPublicHouse,
//            +0x2C IConnectionPointContainer
//   +0x0030  int ArrayIndex          (the index in Houses; ID_Number)
//   +0x0034  HouseTypeClass *Type
//   +0x0038  six lists (0x18 bytes each; Buildings at +0x68)
//   +0x0130  int unknown_130
//   +0x0206  bool unknown_206, +0x207 bool unknown_207
//   +0x0230  int CurBuildings
//   +0x023C  StorageClass Tiberium (four float amounts)
//   +0x024C  int Balance, +0x250 int Capacity
//   +0x52D0  int Power, +0x52D4 int Drain
//   +0x53BC  CoordStruct BaseCenter
//   size 0x15F90 (slot 12)
#ifndef RA2_SHARED_HOUSE_HPP
#define RA2_SHARED_HOUSE_HPP

#include "shared/unknown_globals.hpp"
#include "shared/win32_api.hpp"   // MultiByteToWideChar
#include "shared/abstract_type.hpp"
#include "shared/cd_timer.hpp"
#include "shared/house_type.hpp"
#include "shared/rgb_class.hpp"

class TechnoTypeClass;
class TechnoClass;
class ObjectClass;
class BuildingClass;
class BuildingTypeClass;
class SuperClass;
class TagClass;
class ConnectionPointClass;
class FactoryClass;
typedef wchar_t *BSTR;

extern "C" char *__cdecl strcpy(char *destination, char const *source);
#pragma intrinsic(strcpy)
extern "C" __declspec(dllimport) BSTR __stdcall SysAllocString(wchar_t const *string);

// HouseTypeClass: shared/house_type.hpp.

// StorageClass: shared/storage_class.hpp.
#include "shared/storage_class.hpp"

// Subobjects whose code lives in other units (sizes from the constructor;
// names are hypotheses).
#include "shared/house_nodes.hpp"
class UnknownHouseTracker {
public:
    UnknownHouseTracker();                  // 0x0070C440
    UnknownHouseTracker(NoInitClass const &noinit) {}
    void unknown_func_70c4d0(int count);    // 0x0070C4D0 (sized by a type count)
    void Unknown_0070C490(int index);       // 0x0070C490 (counts one of a type; TechnoClass slot 55)
    ~UnknownHouseTracker();                 // 0x0070C480
    char unknown_000[0x808];
};
class UnknownHouseCounter {
public:
    UnknownHouseCounter();                  // 0x00491C00
    ~UnknownHouseCounter();                 // 0x00491C20
    int unknown_func_491d10(int index);     // 0x00491D10 (a count by type index)
    int Sum() const;                        // 0x00491D90 (the total of every type's count)
    void Increment(int index);              // 0x00491C50 (one more of a type; grows the counts; name hypothesis)
    void Decrement(int index);              // 0x00491CB0 (one fewer; name hypothesis)
    void Save(IStream *stream);             // 0x00491DB0
    void Load(IStream *stream);             // 0x00491E10
    char unknown_00[0x10];
};
class UnknownHouseBase {
public:
    UnknownHouseBase();                     // 0x004A6910
    ~UnknownHouseBase();                    // 0x004A6930
    void unknown_func_4a6b10();             // 0x004A6B10 (after loading)
    char unknown_00[0x2C];
};
class HouseClass;
// A base plan: shared/base.hpp.
#include "shared/base.hpp"

// Members of other classes read here, as views until their headers exist.
class TiberiumClass;
extern DynamicVectorClass<TiberiumClass *> unknown_TiberiumClass_list_00ac0b30;   // 0x00AC0B30
struct UnknownTiberiumView {
    char unknown_00[0xB8];
    int Value;                              // +0xB8 credits per unit (hypothesis)
};
// The rules fields House.cpp reads (+0xC74, +0x111D, +0x1410) are in shared/rules.hpp's RulesClass.
// WaypointClass and WaypointPathClass: shared/waypoint_path.hpp (the house keeps
// pointers only).
struct WaypointClass;
class WaypointPathClass;

class IApplication;
#include "shared/connection_points.hpp"
#define CONNECT_E_CANNOTCONNECT ((HRESULT)0x80040202L)

// The scripting interfaces (COM; slot order from the vtables).
struct __declspec(novtable) IHouse : public IUnknown {
    virtual long __stdcall ID_Number() = 0;                             // slot 3
    virtual BSTR __stdcall Name() = 0;                                  // slot 4
    virtual IApplication *__stdcall Get_Application() = 0;              // slot 5
    virtual long __stdcall Available_Money() = 0;                       // slot 6
    virtual long __stdcall Available_Storage() = 0;                     // slot 7
    virtual long __stdcall Power_Output() = 0;                          // slot 8
    virtual long __stdcall Power_Drain() = 0;                           // slot 9
    virtual long __stdcall Category_Quantity(int category) = 0;         // slot 10
    virtual long __stdcall Category_Power(int category) = 0;            // slot 11
    virtual Cell __stdcall Base_Center() = 0;                     // slot 12
    virtual HRESULT __stdcall Fire_Sale() = 0;                          // slot 13
    virtual HRESULT __stdcall All_To_Hunt() = 0;                        // slot 14
};

struct __declspec(novtable) IPublicHouse : public IUnknown {
    virtual long __stdcall ID_Number() = 0;                             // slot 3
    virtual BSTR __stdcall Name() = 0;                                  // slot 4
    virtual long __stdcall Public_Category_Quantity(int category) = 0;  // slot 5
    virtual long __stdcall Public_Category_Power(int category) = 0;     // slot 6
    virtual Cell __stdcall Public_Base_Center() = 0;              // slot 7
    virtual bool __stdcall Is_Powered() = 0;                            // slot 8
};



extern "C" GUID const CLSID_HouseClass;         // 0x007A1AD0

extern "C" GUID const IID_IHouse;                   // 0x007A2CA8
extern "C" GUID const IID_IPublicHouse;             // 0x007A2040
extern "C" GUID const IID_IConnectionPointContainer;   // 0x007AFD20 (UUID.LIB)

// The application object the scripting interfaces return (0x0084C7DC).
extern IUnknown *unknown_application_84c7dc;
extern "C" GUID const IID_IApplication_79c3d0;  // 0x0079C3D0 (hypothesis)
// Query helper (0x00426C60): object, iid, result.
void __stdcall Unknown_00426C60(IUnknown **object, GUID const &iid, void **result);

class HouseClass;
class FootClass;

class TeamTypeClass;
class HouseClass : public AbstractClass, public IHouse, public IPublicHouse, public IConnectionPointContainer {
public:
    bool Can_Build_Team(TeamTypeClass *team);                   // 0x004F3630 (name hypothesis)
    int Team_Count(TeamTypeClass *team);                        // 0x004F35F0 (name hypothesis)
    // A production choice (layout not recovered); the unit keeps every
    // choice in BuildChoiceClass::Array (0x00A40F20, a guarded class static).
    struct BuildChoiceClass {
        static DynamicVectorClass<BuildChoiceClass *> Array;
    };

    HouseClass(HouseTypeClass *type);                                   // 0x004E18C0
    // Clears the per-cell values (+0x56D0; the constructor clears them twice).
    void Clear_Cells() { memset(unknown_56d0, 0, sizeof(unknown_56d0)); }
    HouseClass(NoInitClass const &noinit);                              // 0x004E1680

    virtual HRESULT __stdcall QueryInterface(GUID const &iid, void **object);   // 0x004E29D0
    virtual unsigned long __stdcall AddRef();                           // 0x004F6B60
    virtual unsigned long __stdcall Release();                          // 0x004F6B70

    // IHouse
    virtual long __stdcall ID_Number();                                 // 0x004E2DE0
    virtual BSTR __stdcall Name();                                      // 0x004E2AF0
    virtual IApplication *__stdcall Get_Application();                  // 0x004E2AD0
    virtual long __stdcall Available_Money();                           // 0x004E2B30
    virtual long __stdcall Available_Storage();                         // 0x004E2B70
    virtual long __stdcall Power_Output();                              // 0x004E2BA0
    virtual long __stdcall Power_Drain();                               // 0x004E2BB0
    virtual long __stdcall Category_Quantity(int category);             // 0x004E2BC0
    virtual long __stdcall Category_Power(int category);                // 0x004E2C80
    virtual Cell __stdcall Base_Center();                         // 0x004E2D60
    virtual HRESULT __stdcall Fire_Sale();                              // 0x004EC3C0
    virtual HRESULT __stdcall All_To_Hunt();                            // 0x004EC420
    // IPublicHouse (ID_Number and Name through adjustor thunks)
    virtual long __stdcall Public_Category_Quantity(int category);      // 0x004E2C20
    virtual long __stdcall Public_Category_Power(int category);         // 0x004E2CF0
    virtual Cell __stdcall Public_Base_Center();                  // 0x004E2DA0
    virtual bool __stdcall Is_Powered();                                // 0x004E2AB0
    // IConnectionPointContainer
    virtual HRESULT __stdcall EnumConnectionPoints(IEnumConnectionPoints **points);              // 0x004ED340
    virtual HRESULT __stdcall FindConnectionPoint(GUID const &iid, IConnectionPoint **point);   // 0x004ED3A0

    virtual HRESULT __stdcall GetClassID(GUID *clsid);                  // 0x004EE850 slot 3
    virtual HRESULT __stdcall Load(IStream *stream);                    // 0x004EDA60 slot 5
    virtual HRESULT __stdcall Save(IStream *stream, BOOL clear_dirty);  // 0x004EE440 slot 6
    virtual ~HouseClass();                                              // (scalar deleting 0x004F6BA0)
    virtual void Detach(AbstractClass *target, bool all = true);        // 0x004E71E0 slot 10
    virtual int Kind_Of() const;                                        // 0x004F6B80 slot 11
    virtual int Size_Of() const;                                        // 0x004EE890 slot 12
    virtual void Compute_CRC(WWCRCEngine &crc) const;                   // 0x004ED790 slot 13
    virtual int unknown_slot16() const;                                 // 0x004F6B90
    virtual void AI();                                                  // 0x004E4110 slot 23

    float Cost_Multiplier(TechnoTypeClass const *type);    // 0x004F5960
    bool Unknown_004F52B0();                               // 0x004F52B0 (TechnoClass slots 24, 38, 39, 80; ObjectClass slot 80 tests al; local player or human flag)
    bool Unknown_004F52F0();                               // 0x004F52F0
    void Unknown_004EF5A0();                               // 0x004EF5A0 (UnitClass 0x006FDFC0 after moving BaseCenter; result unused)
    void Unknown_004F6310();                               // 0x004F6310 (UnitClass 0x006FDFC0 after moving the base plan; reads BaseCenter)
    float Unknown_004F5B30();                              // 0x004F5B30 (a float of the owner type, +0x148; UnitClass 0x00707130 scales the load value by it)
    void Unknown_004E5280(int amount);                      // 0x004E5280 (spends credits; TechnoClass slot 95 repair)
    void unknown_4e76a0(Cell const &cell, int arg2);          // 0x004E76A0 (UnitClass slot 52: a unit leaving a cell; hypothesis)
    void Unknown_004ED610(TechnoClass *techno, bool arg2);   // 0x004ED610 (TechnoClass slot 53: the object enters the map)
    void Unknown_004ED440(TechnoClass *techno, bool arg2);   // 0x004ED440 (TechnoClass slot 52: the object leaves the map)
    double Unknown_004F5A20(TechnoTypeClass *type);       // 0x004F5A20 (a speed factor for a type; FootClass slot 303)
    Cell Unknown_004EB270(FootClass *foot);          // 0x004EB270 (a cell for a unit to guard; FootClass slot 144)
    bool Unknown_0051FC80();                               // 0x0051FC80 (FootClass slot 53: the locomotor powers off when it holds; hypothesis: ion storm)
    double Tiberium_Fraction() const;                      // 0x004E2DF0 (stored tiberium over capacity)
    void Refund_Money(int amount);                         // 0x004E5440
    bool Is_Ally(int house) const;                         // 0x004E5500 (by index)
    bool Is_Ally(HouseClass const *house) const;           // 0x004E5540
    bool Is_Ally(TechnoClass const *techno) const;         // 0x004E5580 (its owning house)
    bool Is_Ally(ObjectClass const *object) const;         // 0x004E55E0 (active objects only)
    void Make_Ally(int house, bool announce);              // 0x004E5640
    void Make_Ally(HouseClass *house, bool announce);      // 0x004E5660
    void Make_Enemy(int house, bool announce);             // 0x004E5A50
    void Make_Enemy(HouseClass *house, bool announce);     // 0x004E5A70
    void unknown_func_4e8300(int color, int arg2, int balance);   // 0x004E8300
    double Power_Fraction() const;                         // 0x004E8330 (1 when power covers the drain)
    float unknown_func_4f5a70(TechnoTypeClass *type);       // 0x004F5A70 (the owner type's build time multiplier for the type's kind; TechnoClass 0x006C22A0)
    float unknown_func_4f58a0(TechnoTypeClass *type);       // 0x004F58A0 (the owner type's armor multiplier against the type's kind; TechnoClass 0x006CA6C0)
    // Index in Houses of the house with this name, or -1 (0x004F5B40).
    static int __fastcall Find_Index(char const *name);
    int unknown_4e3660(TechnoTypeClass const *type, int arg2, int arg3);// 0x004E3660 (-1: none left; hypothesis; AircraftClass destructor)
    void unknown_4ea7f0(TechnoClass *object); // proposedacceptedLeafownership/typecorrection,0x004EA7F0
    void unknown_4ea800(TechnoClass *techno);              // 0x004EA800 (AircraftClass/InfantryClass destructors)
    void unknown_4ea970(TechnoClass *techno);              // 0x004EA970 (AircraftClass::Init)
    void unknown_func_4f4b20();                            // 0x004F4B20 (BuildingClass destructor, for a building with a usable super weapon)
    // The first unit type of the list this house can own (0x004EF6F0; the
    // multiplayer base unit from Rules BaseUnit, Create_Units 0x00660320).
    UnitTypeClass *Unknown_004EF6F0(TypeList<UnitTypeClass *> const &list);
    bool unknown_func_4f52f0();                            // 0x004F52F0 (hypothesis)
    static HouseClass *__fastcall As_Pointer(int type);    // 0x004ED760 (the house of a house type index)
    float Harvested(float amount, int type);                // 0x004E5100 (credits for harvested tiberium)
    void Place_Tiberium(int count, int type);              // 0x004E51F0
    double unknown_func_4e5240() const;                    // 0x004E5240 (weed fraction; hypothesis)
    void Make_Ally(ObjectClass *object, bool announce);    // 0x004ECF50 (its owning house)
    void Make_Enemy(ObjectClass *object, bool announce);   // 0x004ECF80
    void Add_Waypoint(CoordStruct const &coord);           // 0x004ED0E0 (selects the waypoint in the current path; name hypothesis)
    void unknown_func_4f5880();                            // 0x004F5880 (the local player's house tells the map)
    int unknown_func_4f30d0();                             // 0x004F30D0 (the first waypoint path without waypoints, else -1)
    void Make_Waypoint_Path(int index);                    // 0x004EE8A0
    void unknown_func_4e7150();                            // 0x004E7150 (deletes the house, its technos and triggers)
    void Silo_Redraw_Check(int tiberium, int capacity);    // 0x004E5460
    BuildingClass *Find_Building(int type, int zone);      // 0x004E8560 (zone -1: any)
    int Which_Zone(CoordStruct const &coord) const;        // 0x004EAD40
    int Which_Zone(ObjectClass const *object) const;       // 0x004EAEB0
    int Which_Zone(Cell const &cell) const;          // 0x004EAEF0
    bool unknown_func_4e90c0(int arg1);                    // 0x004E90C0
    void unknown_func_4e5dc0(int cell, int amount);        // 0x004E5DC0
    bool unknown_func_4e7580(ObjectClass *object, bool arg2);   // 0x004E7580
    bool unknown_func_4e77a0(ObjectClass *object, bool arg2);   // 0x004E77A0
    bool unknown_func_4e7440(int type);                    // 0x004E7440
    TechnoTypeClass *unknown_func_4e74c0(int kind, bool naval);   // 0x004E74C0
    void unknown_func_4e4ef0();                            // 0x004E4EF0
    int unknown_func_4e8d20();                             // 0x004E8D20
    int *unknown_func_4eab10(int kind, bool naval);         // 0x004EAB10
    int unknown_func_4eb980(int kind, bool naval);          // 0x004EB980
    bool unknown_func_4e68d0(int index, Cell const &cell);        // 0x004E68D0
    void unknown_func_4ec9b0();                            // 0x004EC9B0 (a member: its callers pass this)
    bool unknown_func_4ed2b0(WaypointClass *waypoint, int *path, char *position);   // 0x004ED2B0
    void unknown_func_4ecfb0(CoordStruct const &coord);    // 0x004ECFB0
    void unknown_func_4eeba0(int amount, HouseClass *house);   // 0x004EEBA0 (anger)
    bool unknown_func_4f5320(BuildingTypeClass *type, Cell const &cell);   // 0x004F5320 (the widened foundation touches a cell with this house's bit)
    void Just_Built(TechnoClass *techno);                  // 0x004E6F10 (TS name; the factory finished an object)
    void Attacked(TechnoClass *source);                    // 0x004E4F60 (TS name; an object of the house was attacked)
    void unknown_func_4f3420();                            // 0x004F3420 (rebuilds the threat map +0x56D0; after an alliance changes)
    // The cell of this house's building of the type an upgrade powers up,
    // the least upgraded one (or one without upgrades) that takes it; cell
    // 0, 0 when there is none (0x004F0E30; BuildingClass 0x00440520).
    Cell unknown_func_4f0e30(BuildingTypeClass *upgrade);
    // Adds an object's influence to a grid over an area: within six cells of
    // its cell, strength / ((distance - 1) * 0.1 + 1) (0x004F0FF0; 0x004F1190).
    void unknown_func_4f0ff0(ObjectClass const *object, int strength, int *grid, Rect const &area);
    // A computer house's money mode (+0x12C) in a skirmish or network game,
    // by Available_Money against Rules AIAlternateProductionCreditCutoff
    // (0x004F3720; BuildingClass 0x00440520).
    void unknown_func_4f3720(int arg1);
    void unknown_func_4e67a0(int index);                   // 0x004E67A0 (0x004E68D0 at the best enemy building by slot 90, each passing a 90% roll)
    // Whether the player controls the house: in the campaign a human or
    // player-controlled house, otherwise the player's own house (inline; YRpp
    // calls it ControlledByPlayer).
    bool Is_Player_Control() const
    {
        if (unknown_game_mode_a3d298 == 0) {
            return unknown_134 || unknown_135;
        }
        return this == unknown_player_a35db4;
    }
    // Whether a human controls the house: the human flag, in the campaign also
    // the player-control flag (inline; YRpp calls it ControlledByHuman).
    bool Is_Human_Control() const
    {
        if (unknown_game_mode_a3d298 == 0) {
            bool result = unknown_134 || unknown_135;
            return result;
        }
        return unknown_134;
    }
    void unknown_func_4f3c50(SuperClass *super);          // 0x004F3C50 (fires a super weapon near the base of house +0x54F0, or at the +0x541C target)
    void unknown_func_4f3e00(SuperClass *super);          // 0x004F3E00 (fires a super weapon at the best building of house +0x54F0)
    void unknown_func_4ef890();                            // 0x004EF890 (plans the base; Unknown_004EF5A0)
    Cell unknown_func_4eca30(int arg1, int arg2);           // 0x004ECA30 (always cell 0, 0; no caller references it)
    Cell Random_Cell_In_Zone(int zone);                    // 0x004ECA50 (RA's Random_Cell_In_Zone)
    // Sells the wall overlay at a cell for its owner (RA's Sell_Wall; 0x004E8380).
    void Sell_Wall(Cell const &cell, bool quiet);
    void unknown_func_4ee8f0();                            // 0x004EE8F0 (turns the house's firestorm walls on)
    void unknown_func_4eea40();                            // 0x004EEA40 (turns them off)
    // The team types the house may make now (0x004E5CF0; RA's name, whose version
    // returned one type; HouseClass::AI expands it).
    TypeList<TeamTypeClass const *> Suggested_New_Team(bool alerted);
    void unknown_func_4f2fc0();                            // 0x004F2FC0 (HouseClass::AI: the player's spy satellite view)
    void unknown_func_4f2e50();                            // 0x004F2E50 (HouseClass::AI: the player's radar)
    bool unknown_func_4f64c0(BaseNodeClass const &node);   // 0x004F64C0 (the node may be built now; BaseClass::Next_Buildable_Index)
    bool unknown_func_4ed140(Cell const &cell);      // 0x004ED140 (no other path has a waypoint there)
    WaypointClass *unknown_func_4ed200(Cell const &cell);   // 0x004ED200 (a waypoint in the cell, else 0)
    void unknown_func_4eaba0(TechnoClass *techno);         // 0x004EABA0
    void unknown_func_4e8640();                            // 0x004E8640 (BuildingClass slot 52)
    AbstractClass *unknown_func_4eb360(CoordStruct const &coord);   // 0x004EB360 (a target near a coordinate; AircraftClass slot 129)
    void unknown_func_4f3f40(BuildingClass *building);     // 0x004F3F40 (BuildingClass slot 52: a building left)
    void unknown_func_4f3160();                            // 0x004F3160 (BuildingClass slot 52, threat-rating node)
    void unknown_func_4f3170(int kind, bool naval, int arg3);  // 0x004F3170 (BuildingClass slot 52, a factory left)
    void unknown_func_4eeb90();                            // 0x004EEB90 (BuildingClass 0x0044D530)
    void unknown_func_4eac70(TechnoClass *techno);         // 0x004EAC70
    bool Is_Allowed_To_Ally(HouseClass *house);            // 0x004EC4E0 (name hypothesis)
    static void unknown_func_4ec5e0();                     // 0x004EC5E0
    static int __fastcall unknown_func_4eb550(int kind, int index);   // 0x004EB550 (a building type's +0xBA0)
    int unknown_func_4e63f0(int kind, int index, bool naval);   // 0x004E63F0
    // RA's Abandon_Production: 0, or 3 when the house has no factory for the
    // type (0x004E64F0; EventClass::Execute, BuildingClass).
    int Abandon_Production(int kind, int index, bool naval);
    bool unknown_func_4e7070(TechnoClass *builder, BuildingClass *building);   // 0x004E7070
    void Write_INI(CCINIClass &ini);                       // 0x004EC230
    // Makes the houses listed in [Houses] (or one per house type when there
    // are none) and reads each house's section (0x004EBA20; name hypothesis).
    static void __fastcall Read_Scenario_INI(CCINIClass &ini);
    void Read_INI(CCINIClass &ini);                        // 0x004EBBB0 (the house's own section)
    // Derives the laser colour (+0x55EC) from the house colour (+0x55E9): scaled to length
    // 240, channels under 96 dropped, scaled again (0x004F5570; name hypothesis).
    void Update_Laser_Color();
    void unknown_func_4f33e0(HouseClass *house);           // 0x004F33E0 (forgets the anger at a house)
    void Cheer();                                          // 0x004F62B0 (every techno cheers; name hypothesis)
    void unknown_func_4f3b70(SuperClass *super);          // 0x004F3B70 (fires a super weapon at unknown_cell_a40f10)
    void unknown_func_4f3ae0(SuperClass *super);          // 0x004F3AE0 (fires a super weapon at a picked cell)
    void unknown_func_4f3bb0(SuperClass *super);          // 0x004F3BB0 (the same code as 0x004F3AE0)
    Cell unknown_func_4f65a0();                            // 0x004F65A0 (a target cell; +0x541C == 1)
    BuildingTypeClass *unknown_func_4ef600(DynamicVectorClass<BuildingTypeClass *> const &types);   // 0x004EF600 (the first building type of the list this house may build)
    Cell unknown_func_4f6a80(int mode);                    // 0x004F6A80 (a target cell by +0x541C)
    void unknown_func_4f3d70(SuperClass *super);          // 0x004F3D70 (0x004F3AE0 unless 0x0051FC50's flag)
    void unknown_func_4f3320(HouseClass *house);          // 0x004F3320 (marks a country seen; reveals to the player)
    void Update_Color();                                   // 0x004F5400 (+0x55E9 from the colour scheme; name hypothesis)
    void unknown_func_4f5800(long delay);                  // 0x004F5800 (sets +0x5668, restarts +0x1EC)
    void unknown_func_4f5840(long delay);                  // 0x004F5840 (sets +0x5669, restarts +0x1F8)
    int Assign_Handicap(int difficulty);                   // 0x004E2E40 (sets +0xC8; returns the old value; name after TS)
    static void __fastcall Write_Scenario_INI(CCINIClass &ini);   // 0x004EC180
    BuildingClass *unknown_func_4e5160();                  // 0x004E5160 (the storage building with most free room)
    void unknown_func_4e7df0();                            // 0x004E7DF0 (destroys every techno the house owns)
    bool unknown_func_4e7e80();                            // 0x004E7E80
    bool Flag_To_Win(bool quiet);                          // 0x004E7EE0 (RA's name)
    void unknown_func_4e82c0();                            // 0x004E82C0
    bool Flag_To_Lose(bool quiet);                         // 0x004E80D0 (RA's name)
    // Hands a human player's house to the computer (0x004F4070; Destroy_Null_Connection calls it when a
    // serial player leaves).
    void unknown_func_4f4070();
    void unknown_func_4f5be0();                            // 0x004F5BE0 (the base building action when the base plan is empty)
    FactoryClass *unknown_func_4eb580(int kind, bool naval, int arg3); // 0x004EB580 (the factory per kind)
    // Starts producing a type in the house's factory for its kind (made when
    // missing): 0 on success, 3 when refused (0x004E5E30; name after TS, from
    // its "Request to Begin_Production" messages).
    int Begin_Production(int kind, int index, bool naval, bool resume);
    void Set_Factory(FactoryClass *factory, int kind, bool naval, int buildcat);   // 0x004EB8C0 (name after TS)
    // Adds to the power output / drain; when the house turns under- or
    // re-powered, every sink of its outgoing interface is told (names after TS).
    void Adjust_Power(int amount);                         // 0x004EC6E0
    void Adjust_Drain(int amount);                         // 0x004EC850
    void unknown_func_4e64f0(int kind, int index, int arg3);   // 0x004E64F0 (abandons production of a type; BuildingClass slot 54)
    void unknown_func_4eb620(int kind, bool naval, int arg3); // 0x004EB620
    void unknown_func_4eb6d0(int kind, bool naval, int arg3); // 0x004EB6D0
    bool unknown_func_4eb770(int kind, bool naval, int arg3); // 0x004EB770
    void unknown_func_4eb810(int kind, bool naval, int arg3, bool value); // 0x004EB810

    int ArrayIndex;                                       // +0x00030 the index in Houses (ID_Number; TechnoClass::Owner)
    HouseTypeClass *Type;                                 // +0x00034
    DynamicVectorClass<TagClass *> unknown_38;            // +0x00038 (vtable 0x007A2AE4)
    DynamicVectorClass<BuildingClass *> unknown_50;       // +0x00050 (vtable 0x007A2364)
    DynamicVectorClass<BuildingClass *> Buildings;        // +0x00068 (vtable 0x007A2364)
    DynamicVectorClass<BuildingClass *> unknown_80;       // +0x00080 (vtable 0x007A2364)
    DynamicVectorClass<BuildingClass *> unknown_98;       // +0x00098 (vtable 0x007A2364)
    DynamicVectorClass<BuildingClass *> unknown_b0;       // +0x000B0 (vtable 0x007A2364)
    int unknown_c8;                                       // +0x000C8 the scenario's computer difficulty when made
    int unknown_cc;                                       // +0x000CC
    double unknown_d0;                                    // +0x000D0 (1.0)
    double unknown_d8;                                    // +0x000D8 (1.0)
    double unknown_e0;                                    // +0x000E0 (1.0)
    double unknown_e8;                                    // +0x000E8 (1.0)
    double unknown_f0;                                    // +0x000F0 (1.0)
    double unknown_f8;                                    // +0x000F8 (1.0)
    double unknown_100;                                   // +0x00100 (1.0)
    double unknown_108;                                   // +0x00108
    double unknown_110;                                   // +0x00110
    int unknown_118;                                      // +0x00118
    int unknown_11c;                                      // +0x0011C (1)
    int unknown_120;                                      // +0x00120
    int unknown_124;                                      // +0x00124
    int unknown_128;                                      // +0x00128
    int unknown_12c;                                      // +0x0012C
    int unknown_130;                                      // +0x00130 (TechnoClass constructor)
    bool unknown_134;                                     // +0x00134
    bool unknown_135;                                     // +0x00135
    bool unknown_136;                                     // +0x00136
    bool unknown_137;                                     // +0x00137
    bool unknown_138;                                     // +0x00138 (true)
    bool unknown_139;                                     // +0x00139
    bool unknown_13a;                                     // +0x0013A
    bool unknown_13b;                                     // +0x0013B
    bool unknown_13c;                                     // +0x0013C
    bool unknown_13d;                                     // +0x0013D
    bool unknown_13e;                                     // +0x0013E
    bool unknown_13f;                                     // +0x0013F
    bool unknown_140;                                     // +0x00140
    bool unknown_141;                                     // +0x00141
    bool unknown_142;                                     // +0x00142
    bool unknown_143;                                     // +0x00143
    bool unknown_144;                                     // +0x00144 (true)
    int unknown_148;                                      // +0x00148
    int unknown_14c;                                      // +0x0014C
    bool unknown_150;                                     // +0x00150
    int unknown_154;                                      // +0x00154 (-1; the current waypoint path)
    WaypointPathClass *WaypointPaths[12];                 // +0x00158 (made on demand, 0x004EE8A0)
    bool unknown_188;                                     // +0x00188
    bool unknown_189;                                     // +0x00189
    bool unknown_18a;                                     // +0x0018A
    bool unknown_18b;                                     // +0x0018B
    bool unknown_18c;                                     // +0x0018C
    bool unknown_18d;                                     // +0x0018D
    bool unknown_18e;                                     // +0x0018E
    bool unknown_18f;                                     // +0x0018F
    bool unknown_190;                                     // +0x00190
    bool unknown_191;                                     // +0x00191
    bool unknown_192;                                     // +0x00192 (true)
    int unknown_194;                                      // +0x00194
    int unknown_198;                                      // +0x00198
    DynamicVectorClass<SuperClass *> Supers;              // +0x0019C (vtable 0x007A2A24)
    int unknown_1b4;                                      // +0x001B4 (-1)
    int unknown_1b8;                                      // +0x001B8 (-1)
    int unknown_1bc;                                      // +0x001BC (-1)
    int unknown_1c0;                                      // +0x001C0 (-1)
    int unknown_1c4;                                      // +0x001C4 a count the tag destructor lowers
    CDTimerClass<FrameTimerClass> unknown_1c8;            // +0x001C8
    CDTimerClass<FrameTimerClass> unknown_1d4;            // +0x001D4
    CDTimerClass<FrameTimerClass> unknown_1e0;            // +0x001E0 (restarted at 60 by the tag destructor)
    CDTimerClass<FrameTimerClass> unknown_1ec;            // +0x001EC
    CDTimerClass<FrameTimerClass> unknown_1f8;            // +0x001F8
    bool unknown_204;                                     // +0x00204
    bool unknown_205;                                     // +0x00205
    bool unknown_206;                                     // +0x00206 (Get_Cameo_Data: infantry alt cameo)
    bool unknown_207;                                     // +0x00207 (Get_Cameo_Data: unit alt cameo)
    int unknown_208;                                      // +0x00208
    int unknown_20c;                                      // +0x0020C
    int unknown_210;                                      // +0x00210
    int unknown_214;                                      // +0x00214
    int unknown_218;                                      // +0x00218
    int unknown_21c;                                      // +0x0021C
    int unknown_220;                                      // +0x00220
    int unknown_224;                                      // +0x00224
    int unknown_228;                                      // +0x00228
    int unknown_22c;                                      // +0x0022C
    int CurBuildings;                                     // +0x00230
    int unknown_234;                                      // +0x00234
    int unknown_238;                                      // +0x00238
    StorageClass Tiberium;                                // +0x0023C
    int Balance;                                          // +0x0024C
    int Capacity;                                         // +0x00250
    StorageClass unknown_254;                             // +0x00254
    int unknown_264;                                      // +0x00264
    UnknownHouseTracker unknown_268;                      // +0x00268 (0x808 bytes; constructor 0x0070C440)
    UnknownHouseTracker unknown_a70;                      // +0x00A70 (0x808 bytes; constructor 0x0070C440)
    UnknownHouseTracker unknown_1278;                     // +0x01278 (0x808 bytes; constructor 0x0070C440)
    UnknownHouseTracker unknown_1a80;                     // +0x01A80 (0x808 bytes; constructor 0x0070C440)
    UnknownHouseTracker unknown_2288;                     // +0x02288 (0x808 bytes; constructor 0x0070C440)
    UnknownHouseTracker unknown_2a90;                     // +0x02A90 (0x808 bytes; constructor 0x0070C440)
    UnknownHouseTracker unknown_3298;                     // +0x03298 (0x808 bytes; constructor 0x0070C440)
    UnknownHouseTracker unknown_3aa0;                     // +0x03AA0 (0x808 bytes; constructor 0x0070C440)
    UnknownHouseTracker unknown_42a8;                     // +0x042A8 (0x808 bytes; constructor 0x0070C440)
    UnknownHouseTracker unknown_4ab0;                     // +0x04AB0 (0x808 bytes; constructor 0x0070C440)
    int unknown_52b8;                                     // +0x052B8
    int unknown_52bc;                                     // +0x052BC
    int unknown_52c0;                                     // +0x052C0
    int unknown_52c4;                                     // +0x052C4
    int unknown_52c8;                                     // +0x052C8
    int unknown_52cc;                                     // +0x052CC
    int Power;                                            // +0x052D0
    int Drain;                                            // +0x052D4
    FactoryClass *unknown_52d8;                            // +0x052D8
    FactoryClass *unknown_52dc;                            // +0x052DC
    FactoryClass *unknown_52e0;                            // +0x052E0
    FactoryClass *unknown_52e4;                            // +0x052E4
    FactoryClass *unknown_52e8;                            // +0x052E8
    FactoryClass *unknown_52ec;                            // +0x052EC
    FactoryClass *unknown_52f0;                            // +0x052F0
    FactoryClass *unknown_52f4;                            // +0x052F4
    FactoryClass *unknown_52f8;                            // +0x052F8
    bool unknown_52fc;                                    // +0x052FC
    bool unknown_52fd;                                    // +0x052FD
    bool unknown_52fe;                                    // +0x052FE
    bool unknown_52ff;                                    // +0x052FF
    bool unknown_5300;                                    // +0x05300
    bool unknown_5301;                                    // +0x05301
    bool unknown_5302;                                    // +0x05302
    bool unknown_5303;                                    // +0x05303
    bool unknown_5304;                                    // +0x05304
    ObjectClass *unknown_5308;                            // +0x05308 (0x004E77A0)
    Cell unknown_530c;                              // +0x0530C (a marked cell; cleared by 0x004E7580)
    int unknown_5310[20];                                 // +0x05310 (per house index: units/infantry/aircraft killed of that house; TechnoClass slot 55)
    int unknown_5360;                                     // +0x05360
    int unknown_5364[20];                                 // +0x05364 (per house index: buildings killed; TechnoClass slot 55)
    int unknown_53b4;                                     // +0x053B4
    int unknown_53b8;                                     // +0x053B8 (-1)
    CoordStruct BaseCenter;                               // +0x053BC
    int unknown_53c8;                                     // +0x053C8
    // Each base zone's defence (RA's ZoneInfo; 0x004E8640 sums it).
    struct ZoneInfoStruct {
        int AirDefense;
        int ArmorDefense;
        int InfantryDefense;
    } ZoneInfo[5];                                        // +0x053CC
    int unknown_5408;                                     // +0x05408
    int unknown_540c;                                     // +0x0540C (-1)
    ObjectClass *unknown_5410;                            // +0x05410
    int unknown_5414;                                     // +0x05414
    int unknown_5418;                                     // +0x05418
    int unknown_541c;                                     // +0x0541C (1)
    UnknownHouseCounter unknown_5420;                     // +0x05420 (0x10 bytes; constructor 0x00491C00, Save 0x00491DB0)
    UnknownHouseCounter unknown_5430;                     // +0x05430 (0x10 bytes; constructor 0x00491C00, Save 0x00491DB0)
    UnknownHouseCounter unknown_5440;                     // +0x05440 (0x10 bytes; constructor 0x00491C00, Save 0x00491DB0)
    UnknownHouseCounter unknown_5450;                     // +0x05450 (0x10 bytes; constructor 0x00491C00, Save 0x00491DB0)
    UnknownHouseCounter unknown_5460;                     // +0x05460 (0x10 bytes; constructor 0x00491C00, Save 0x00491DB0)
    UnknownHouseCounter unknown_5470;                     // +0x05470 (0x10 bytes; constructor 0x00491C00, Save 0x00491DB0)
    UnknownHouseCounter unknown_5480;                     // +0x05480 (0x10 bytes; constructor 0x00491C00, Save 0x00491DB0)
    UnknownHouseCounter unknown_5490;                     // +0x05490 (0x10 bytes; constructor 0x00491C00, Save 0x00491DB0)
    UnknownHouseCounter unknown_54a0;                     // +0x054A0 (0x10 bytes; constructor 0x00491C00, Save 0x00491DB0)
    UnknownHouseCounter unknown_54b0;                     // +0x054B0 (0x10 bytes; constructor 0x00491C00, Save 0x00491DB0)
    UnknownHouseCounter unknown_54c0;                     // +0x054C0 (0x10 bytes; constructor 0x00491C00, Save 0x00491DB0)
    UnknownHouseCounter unknown_54d0;                     // +0x054D0 (0x10 bytes; constructor 0x00491C00, Save 0x00491DB0)
    CDTimerClass<FrameTimerClass> unknown_54e0;           // +0x054E0
    int unknown_54ec;                                     // +0x054EC
    int unknown_54f0;                                     // +0x054F0 (-1)
    DynamicVectorClass<AngerStruct> AngerNodes;           // +0x054F4 (vtable 0x007A2E64)
    DynamicVectorClass<ScoutStruct> ScoutNodes;           // +0x0550C (vtable 0x007A2E44)
    CDTimerClass<FrameTimerClass> unknown_5524;           // +0x05524
    CDTimerClass<FrameTimerClass> unknown_5530;           // +0x05530
    int unknown_553c;                                     // +0x0553C (-1)
    int unknown_5540;                                     // +0x05540 (-1)
    int unknown_5544;                                     // +0x05544 (-1)
    int unknown_5548;                                     // +0x05548 (-1)
    int unknown_554c;                                     // +0x0554C (100)
    int unknown_5550;                                     // +0x05550 (75)
    int unknown_5554;                                     // +0x05554 (75)
    int unknown_5558;                                     // +0x05558 (75)
    int unknown_555c;                                     // +0x0555C
    UnknownHouseBase unknown_5560[3];                     // +0x05560 (0x2C bytes; constructor 0x004A6910)
    int unknown_55e4;                                     // +0x055E4
    bool unknown_55e8;                                    // +0x055E8
    RGBClass unknown_55e9;                                // +0x055E9 (black when made)
    RGBClass unknown_55ec;                                // +0x055EC (white when made)
    BaseClass unknown_55f0;                               // +0x055F0 (the house's base plan)
    bool unknown_5668;                                    // +0x05668 (true)
    bool unknown_5669;                                    // +0x05669 (true)
    bool unknown_566a;                                    // +0x0566A
    short unknown_566c;                                   // +0x0566C
    short unknown_566e;                                   // +0x0566E
    short unknown_5670;                                   // +0x05670
    short unknown_5672;                                   // +0x05672
    unsigned int Allies;                                  // +0x05674 one bit per house index
    CDTimerClass<FrameTimerClass> unknown_5678;           // +0x05678
    CDTimerClass<FrameTimerClass> unknown_5684;           // +0x05684
    CDTimerClass<FrameTimerClass> unknown_5690;           // +0x05690
    CDTimerClass<FrameTimerClass> unknown_569c;           // +0x0569C
    CDTimerClass<FrameTimerClass> unknown_56a8;           // +0x056A8
    CDTimerClass<FrameTimerClass> unknown_56b4;           // +0x056B4
    CDTimerClass<FrameTimerClass> unknown_56c0;           // +0x056C0
    IUnknown *unknown_56cc;                               // +0x056CC (saved through OleSaveToStream)
    int unknown_56d0[0x4204];                             // +0x056D0 (cleared by the constructor)
    FixedString<21> IniName;                              // +0x15EE0 (the [Houses] entry value; the type's ID)
    FixedString<32> unknown_15ef5;                        // +0x15EF5 (a name; empty when made)
    wchar_t UIName[21];                                   // +0x15F16 (the type's UIName)
    int ColorSchemeIndex;                                 // +0x15F40 (hypothesis; BulletClass inherits it)
    int unknown_15f44;                                    // +0x15F44
    DynamicVectorClass<IConnectionPoint *> ConnectionPoints;// +0x15F48 (vtable 0x0079E6A0)
    ConnectionPointClass *unknown_15f60;                  // +0x15F60 (the house's connection point)
    int unknown_15f64;                                    // +0x15F64
    double unknown_15f68;                                 // +0x15F68 (1.0)
    double unknown_15f70;                                 // +0x15F70 (1.0)
    int unknown_15f78;                                    // +0x15F78
    float unknown_15f7c;                                  // +0x15F7C (0.33)
    float unknown_15f80;                                  // +0x15F80 (0.33)
    float unknown_15f84;                                  // +0x15F84 (0.34)
    int unknown_15f88;                                    // +0x15F88
    int unknown_15f8c;                                    // +0x15F8C
};

// Scales a colour to length 240, clamping each channel at 255; black becomes
// white (0x004F5490, House.cpp; name hypothesis).
void __fastcall Normalize_Color(double &red, double &green, double &blue);

// The house's outgoing interface (unknown_iid_7a1ac0) as Adjust_Power and
// Adjust_Drain call it: slot 4 when the house becomes under-powered, slot 3
// when it is powered again (names are hypotheses).
struct __declspec(novtable) IUnknownHouseSink : public IUnknown {
    virtual HRESULT __stdcall Power_Restored() = 0;     // slot 3
    virtual HRESULT __stdcall Power_Low() = 0;          // slot 4
};

// A cell value meaning none (0x00A40F10; compared against picked target cells).
extern Cell unknown_cell_a40f10;

// Every house (0x00A32298; defined in the globals unit).
extern DynamicVectorClass<HouseClass *> Houses;   // (the globals unit defines it as unknown_HouseClass_list_00a32298)

// The player's house (0x00A35DB4).

#endif
