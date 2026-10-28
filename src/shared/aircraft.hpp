// AircraftClass: an aircraft (Aircraft.cpp, 0x00413800-0x0041BA9F; RTTI
// vtables 0x0079B12C primary (310 slots, FootClass's count), 0x0079B110
// IRTTITypeInfo at +4, 0x0079B108 INoticeSink, 0x0079B100 INoticeSource,
// 0x0079B0D8 IFlyControl at +0x5A8).
//
// Layout (constructor 0x00413A40, Load 0x0041AB80, Compute_CRC 0x0041AD60,
// Detach 0x0041ADB0; Size_Of returns 0x5C0). Names are hypotheses:
//   +0x000  FootClass (0x5A8)
//   +0x5A8  IFlyControl vtable pointer
//   +0x5AC  AircraftTypeClass *Type    the constructor's first argument (swizzled)
//   +0x5B0..+0x5B2  bools (false)
//   +0x5B4  AbstractClass *            swizzled, cleared by Detach
//   +0x5B8..+0x5BA  bools (false; +0x5BA is IFlyControl::Is_Locked)
//   +0x5BB  signed char (5)
//   +0x5BC, +0x5BD  bools (true)
//
// The IFlyControl methods are AircraftClass members whose `this` is the
// IFlyControl part (fields at -0x5A8); the adjustor thunks 0x0041BA40-
// 0x0041BA9F belong to the vtables.
#ifndef RA2_SHARED_AIRCRAFT_HPP
#define RA2_SHARED_AIRCRAFT_HPP

#include "shared/unknown_globals.hpp"
#include "shared/foot.hpp"
#include "shared/aircraft_type.hpp"
#include "shared/techno_index.hpp"
#include "shared/weapon_type.hpp"

// The building fields AircraftClass::Landing_Altitude reads (stand-ins for
// shared/building.hpp and shared/building_type.hpp, skipped when those are
// included): the type at +0x418 and two of its flags.
#ifndef RA2_SHARED_BUILDING_TYPE_HPP
class BuildingTypeClass : public TechnoTypeClass {
public:
    int ArrayIndex;                     // +0xB90 index in BuildingTypes (TechnoClass slot 55)
    char unknown_b94[0x1215 - 0xB94];
    bool Wall;                          // +0x1215 (TechnoClass 0x006C22A0)
    char unknown_1216[0x1218 - 0x1216];
    bool Overpowerable;                 // +0x1218 (TechnoClass slot 174)
    char unknown_1219[0x1349 - 0x1219];
    bool unknown_1349;                  // +0x1349 (UnitRepair)
    bool unknown_134a;                  // +0x134A (UnitReload; AircraftClass slot 129)
    char unknown_134b[0x1357 - 0x134B];
    bool unknown_1357;                  // +0x1357 (WeaponsFactory; AircraftClass slot 28)
    char unknown_1358[0x1364 - 0x1358];
    bool Artillary;                     // +0x1364 (TechnoClass 0x006D3B60)
    bool unknown_1365;                  // +0x1365 (Helipad)
};
#endif
class BuildingClass;
#ifndef RA2_SHARED_CELL_HPP
// A map cell, as far as AircraftClass slot 101 reads it (stand-in for
// shared/cell.hpp): the object standing in it and a passability test.
class CellClass : public AbstractClass {
public:
    // Approved private scope 0c6c96fe: canonical declarations; no partial-layout bodies.
    virtual HRESULT __stdcall GetClassID(GUID *clsid);
    virtual HRESULT __stdcall Load(IStream *stream);
    virtual HRESULT __stdcall Save(IStream *stream, BOOL clear_dirty);
    virtual int Kind_Of() const;
    virtual int Size_Of() const;
    ObjectClass *unknown_471660(Point2D const &spot, bool alt, ObjectClass *except) const;
    bool Unknown_00478760(int arg1, int arg2, int arg3, int arg4, int arg5, int arg6, int arg7);   // 0x00478760
    BuildingClass *Unknown_004717B0();  // 0x004717B0 (the building in the cell; hypothesis)
    char unknown_024[0xE4 - 0x24];
    TechnoClass *Occupier;              // +0xE4 (hypothesis)
};
#endif

// BuildingClass: the stand-in in shared/techno.hpp.

// Flight control the locomotors query (IID 0x007A2080; method names follow
// the IFlyControl interface of RA2's locomotion COM objects; hypotheses).
struct __declspec(novtable) IFlyControl : public IUnknown {
    virtual int __stdcall Landing_Altitude() = 0;          // slot 3
    virtual int __stdcall Landing_Direction() = 0;         // slot 4
    virtual long __stdcall Is_Loaded() = 0;                // slot 5
    virtual long __stdcall Is_Strafe() = 0;                // slot 6
    virtual long __stdcall Is_Fighter() = 0;               // slot 7
    virtual long __stdcall Is_Locked() = 0;                // slot 8
};
extern "C" GUID const IID_IFlyControl;     // 0x007A2080

extern "C" GUID const CLSID_AircraftClass; // 0x007A1BD0

class AircraftClass : public FootClass, public IFlyControl {
public:
    AircraftClass(AircraftTypeClass *type, HouseClass *house);        // 0x00413A40
    AircraftClass(NoInitClass const &noinit) : FootClass(noinit) {}   // inline (Load)
    virtual ~AircraftClass();                                         // 0x00413DA0

    // IUnknown (both bases)
    virtual HRESULT __stdcall QueryInterface(GUID const &iid, void **object);   // slot 0 0x00413FA0
    virtual unsigned long __stdcall AddRef();                         // slot 1 0x00414000
    virtual unsigned long __stdcall Release();                        // slot 2 0x00414010

    virtual HRESULT __stdcall GetClassID(GUID *clsid)                 // slot 3 0x0041B590 (inline)
    {
        if (clsid == 0) {
            return E_POINTER;
        }
        *clsid = CLSID_AircraftClass;
        return S_OK;
    }
    virtual HRESULT __stdcall Load(IStream *stream);                  // slot 5 0x0041AB80
    virtual HRESULT __stdcall Save(IStream *stream, BOOL clear_dirty);    // slot 6 0x0041AD10
    virtual void Init();                                              // slot 9 0x00413CA0
    virtual void Detach(AbstractClass *target, bool all = true);      // slot 10 0x0041ADB0
    virtual int Kind_Of() const { return 2; }                         // slot 11 0x0041B580 (inline)
    virtual int Size_Of() const { return sizeof(AircraftClass); }     // slot 12 0x0041B570 (inline)
    virtual void Compute_CRC(WWCRCEngine &crc) const;                 // slot 13 0x0041AD60
    virtual bool unknown_slot20() const;                              // slot 20 0x0041B0B0
    virtual bool unknown_slot21() const;                              // slot 21 0x0041B050
    virtual void AI();                                                // slot 23 0x004147F0
    virtual int unknown_slot27(Cell const *cell, bool arg2, bool arg3);         // slot 27 0x00417840
    virtual int unknown_slot28(ObjectClass *object, bool arg2);                 // slot 28 0x004175A0
    virtual int unknown_slot29() const;                               // slot 29 0x0041A500
    virtual bool unknown_slot31();                                    // slot 31 0x0041B040
    virtual ObjectTypeClass *Class_Of() const;                        // slot 33 0x0041B600
    virtual wchar_t const *unknown_slot35();                          // slot 35 0x0041B5D0 (the type's UIName)
    virtual bool unknown_slot53(CoordStruct const *coord, int dir);                   // slot 53 0x00414020
    virtual int unknown_slot62(TechnoClass *techno);                           // slot 62 0x004153C0
    virtual void unknown_slot67(int arg1, int arg2);                  // slot 67 0x004141C0
    virtual void unknown_slot70(bool arg1, bool arg2);                  // slot 70 0x0041A530
    virtual bool unknown_slot77(int arg1, int arg2, int arg3, bool arg4);  // slot 77 0x00417560
    virtual bool unknown_slot78(int arg1, int arg2, bool arg3);        // slot 78 0x004174B0
    virtual int unknown_slot86(int *damage, int distance, WarheadTypeClass *warhead, TechnoClass *source, bool forced, int arg6);  // slot 86 0x00415E70
    virtual void unknown_slot87(CoordStruct const &source, bool forced, bool nokidding);        // slot 87 0x00419CD0
    virtual int unknown_slot95(RadioClass *radio, int message, long &param);         // slot 95 0x00418840
    virtual int unknown_slot101(CellClass *arg1, int arg2, int arg3, int arg4, int arg5);   // slot 101 0x00418E00
    virtual void unknown_slot116(int mission, bool commence);         // slot 116 0x0041B160
    virtual bool unknown_slot117();                                   // slot 117 0x0041AFC0
    virtual void unknown_slot118(int mission);                        // slot 118 0x0041B120
    virtual void unknown_slot119(int mission, int unknown2, int unknown3);   // slot 119 0x0041B1A0
    virtual bool unknown_slot122();                                   // slot 122 0x0041AD30
    virtual int unknown_slot126();                                    // slot 126 0x004178A0
    virtual int unknown_slot129();                                    // slot 129 0x00419D00
    virtual int unknown_slot130();                                    // slot 130 0x0041A080
    virtual int unknown_slot132();                                    // slot 132 0x004146C0
    virtual int unknown_slot133();                                    // slot 133 0x00415FF0
    virtual int unknown_slot134();                                    // slot 134 0x00415300
    virtual int unknown_slot137();                                    // slot 137 0x00414D90
    virtual int unknown_slot138();                                    // slot 138 0x004193D0
    virtual int unknown_slot145();                                    // slot 145 0x00416C20
    virtual int unknown_slot146();                                    // slot 146 0x00415190
    virtual int unknown_slot147();                                    // slot 147 0x00415210
    virtual UnknownFacingDir unknown_slot162();                               // slot 162 0x0041B5E0
    virtual int unknown_slot182(AbstractClass *object, Cell *cell);          // slot 182 0x00418CF0
    virtual UnknownFacingDir unknown_slot183();                               // slot 183 0x00419CB0
    virtual bool unknown_slot200(int arg1, int arg2, int arg3, int arg4);  // slot 200 0x00417580
    virtual void unknown_slot207();                                   // slot 207 0x0041B030 (nothing)
    virtual int unknown_slot218(AbstractClass *target, int weapon, int arg3);        // slot 218 0x0041A120
    virtual int unknown_slot221(int arg1, int arg2);                  // slot 221 0x00415790
    virtual bool unknown_slot242();                                   // slot 242 0x0041B110
    virtual void unknown_slot260(AbstractClass *target, int arg2);                 // slot 260 0x0041A1C0
    virtual bool unknown_slot261(bool arg1, bool arg2);                 // slot 261 0x00417010
    virtual bool unknown_slot282();                                   // slot 282 0x0041AFD0
    virtual TechnoClass *unknown_slot299(DynamicVectorClass<TechnoTypeClass *> const *types, int arg2, int arg3);    // slot 299 0x0041B1E0

    static void __fastcall Read_INI_0041A840(CCINIClass &ini); // Aircraft section reader; source identity hypothesis
    static void __fastcall Write_INI_0041A6C0(CCINIClass &ini); // Aircraft section writer; source identity hypothesis

    int unknown_416010(); // private own normal-unload helper00416010; ECX/RET0/int ABI hypothesis
    int Move_Carryall_00416670(); // private own carryall-move helper00416670; ECX/RET0/int ABI hypothesis
    bool Is_Landing_Cell_Available_00419250(Cell const &cell, bool allow_self); // AL0/1, RET8; identity hypothesis
    AbstractClass *Select_Landing_Destination_004185b0(AbstractClass *desired); // approved private source identity hypothesis
    void unknown_416420(); // evidenced own ECX receiver/RET0 cargo operation; declaration only
    int unknown_415510();                                            // 0x00415510 (slot 147, over the target)

    // IFlyControl
    virtual int __stdcall Landing_Altitude();                         // 0x0041ADF0
    virtual int __stdcall Landing_Direction();                        // 0x0041AEB0
    virtual long __stdcall Is_Loaded();                               // 0x0041AF20
    virtual long __stdcall Is_Strafe();                               // 0x0041AF40
    virtual long __stdcall Is_Fighter();                              // 0x0041AF90
    virtual long __stdcall Is_Locked();                               // 0x0041AFB0

    AircraftTypeClass *Type;                // +0x5AC
    bool unknown_5b0;                       // +0x5B0
    bool unknown_5b1;                       // +0x5B1
    bool unknown_5b2;                       // +0x5B2
    TechnoClass *unknown_5b4;               // +0x5B4 (swizzled; a radio contact, hypothesis)
    bool unknown_5b8;                       // +0x5B8
    bool unknown_5b9;                       // +0x5B9
    bool unknown_5ba;                       // +0x5BA (Is_Locked)
    signed char unknown_5bb;                // +0x5BB (5)
    bool unknown_5bc;                       // +0x5BC (true)
    bool unknown_5bd;                       // +0x5BD (true)
    AbstractClass *unknown_4198b0();                                  // 0x004198B0 (where to land; AircraftClass slot 95)
};

// The cell offsets of the eight facings (0x00851A70; Westwood's
// AdjacentCell) and the order slot 62 tries them in (0x007CE4A8).
extern int const unknown_facings_7ce4a8[8];
extern int const unknown_facings_7ce4c8[8];  // 0x007CE4C8 (slot 182)

// The cell next to `cell` toward an 8-way facing.
#ifndef RA2_ADJACENT_CELL
#define RA2_ADJACENT_CELL
#include "shared/adjacent_cell.hpp"

inline Cell Adjacent_Cell(Cell const &cell, int facing)
{
    Cell const &offset = AdjacentCell[facing & 7];
    return Cell(cell.X + offset.X, cell.Y + offset.Y);
}
#endif

// Every aircraft (0x00A40398).
extern DynamicVectorClass<AircraftClass *> Aircraft;

#endif
