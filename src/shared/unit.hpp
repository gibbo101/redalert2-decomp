// UnitClass: a vehicle (Unit.cpp, 0x006FA1E0-0x0070A34F; RTTI vtables
// 0x007ADDF8 primary (313 slots: FootClass's 310 and 3 new), 0x007ADDDC
// IRTTITypeInfo at +4, 0x007ADDD4 INoticeSink, 0x007ADDCC INoticeSource).
//
// Layout (constructor 0x006FA400, destructor 0x006FA7C0, Load 0x00707C20,
// Compute_CRC 0x00707DF0; Size_Of returns 0x7D0). Names are hypotheses:
//   +0x5A8  int (-1)
//   +0x5AC  UnitTypeClass *Type        the constructor's first argument
//   +0x5B0  AbstractClass *            swizzled, cleared by Detach
//   +0x5B4  int (-1), +0x5B8..+0x5BB bools, +0x5BC/+0x5C0 ints (-1)
//   +0x5C4  owned object (0x004B25C0 releases it; Save and Load clear it)
//   +0x5C8  bool, +0x5CC int
//   +0x5D0..+0x7CF  not touched by the constructor
#ifndef RA2_SHARED_UNIT_HPP
#define RA2_SHARED_UNIT_HPP

// The full class: shared/unit_type.hpp declares only a stub without this.
#define RA2_UNIT_FULL

#include "shared/foot.hpp"
#include "shared/unit_type.hpp"
#include "shared/techno_index.hpp"

// The object at +0x5C4 (released by 0x004B25C0).
class UnknownUnit5C4 {
public:
    void unknown_4b25c0();              // 0x004B25C0
};

// The owner's members the constructor uses (a view of HouseClass until its
// layout is shared). +0x34 is the owner's type (hypothesis: HouseTypeClass,
// whose list at +0x168 names the unit types it builds as veterans).
struct UnknownUnitHouseType {
    char unknown_000[0x168];
    DynamicVectorClass<UnitTypeClass *> unknown_168;    // +0x168
};
struct UnknownUnitHouse {
    void unknown_4ea970(UnitClass *unit);   // 0x004EA970 (also BuildingClass::Init)
    char unknown_000[0x34];
    UnknownUnitHouseType *unknown_34;       // +0x34
    char unknown_038[0x207 - 0x38];
    bool unknown_207;                       // +0x207
};
inline UnknownUnitHouse *Unit_House_View(HouseClass *house)
{
    return (UnknownUnitHouse *)house;
}

class BuildingTypeClass;
class CCINIClass;
class BuildingTypeClass;
// Whether a type is in a list (an inline helper; VectorClass::ID is
// virtual, the original expands the search: UnitClass slots 129 and 132).
inline bool Is_Listed(DynamicVectorClass<BuildingTypeClass *> const &list, BuildingTypeClass *type)
{
    for (int index = 0; index < list.Count(); index++) {
        if (list[index] == type) {
            return true;
        }
    }
    return false;
}

extern "C" GUID const CLSID_UnitClass;  // 0x007A1C60

class UnitClass : public FootClass {
public:
    UnitClass(UnitTypeClass *type, HouseClass *house);                // 0x006FA400
    UnitClass(NoInitClass const &noinit) : FootClass(noinit) {}       // inline (Load)
    virtual ~UnitClass();                                             // 0x006FA7C0

    virtual HRESULT __stdcall GetClassID(GUID *clsid)                 // slot 3 0x0070A290 (inline)
    {
        if (clsid == 0) {
            return E_POINTER;
        }
        *clsid = CLSID_UnitClass;
        return S_OK;
    }
    virtual HRESULT __stdcall Load(IStream *stream);                  // slot 5 0x00707C20
    virtual HRESULT __stdcall Save(IStream *stream, BOOL clear_dirty);    // slot 6 0x00707DB0
    virtual void Init();                                              // slot 9 0x00709E10
    virtual void Detach(AbstractClass *target, bool all = true);      // slot 10 0x00707E90
    virtual int Kind_Of() const { return 1; }                         // slot 11 0x0070A2D0 (inline)
    virtual int Size_Of() const { return sizeof(UnitClass); }         // slot 12 0x0070A280 (inline)
    virtual void Compute_CRC(WWCRCEngine &crc) const;                 // slot 13 0x00707DF0
    virtual void AI();                                                // slot 23 0x006FB100
    virtual int unknown_slot27(Cell const *cell, bool arg2, bool arg3);         // slot 27 0x007041F0
    virtual int unknown_slot28(ObjectClass *object, bool arg2);                 // slot 28 0x00703BD0
    virtual bool unknown_slot31();                                    // slot 31 0x00709A00
    virtual ObjectTypeClass *Class_Of() const;                        // slot 33 0x00705020
    virtual wchar_t const *unknown_slot35();                                 // slot 35 0x0070A0E0
    virtual bool unknown_slot49(HouseClass *house);                            // slot 49 0x00709D50
    virtual ObjectTypeClass *unknown_slot50(bool arg1);                        // slot 50 0x00709BB0
    virtual HouseClass *unknown_slot51(bool arg1);                         // slot 51 0x00709BF0
    virtual bool unknown_slot52();                                     // slot 52 0x007078F0
    virtual bool unknown_slot53(CoordStruct const *coord, int dir);                   // slot 53 0x006FC940
    virtual void unknown_slot55(TechnoClass *techno);                            // slot 55 0x00707ED0
    virtual void unknown_slot58(CoordStruct const &coord);                             // slot 58 0x00707980
    virtual void unknown_slot59(CoordStruct const &coord);                             // slot 59 0x007079E0
    virtual bool unknown_slot63(Rect *bounds, bool arg2, bool arg3);  // slot 63 0x006FF350
    virtual void unknown_slot67(int arg1, int arg2);                  // slot 67 0x00700E70
    virtual bool unknown_slot77(int arg1, int arg2, int arg3, bool arg4);  // slot 77 0x006FD610
    virtual bool unknown_slot78(int arg1, int arg2, bool arg3);        // slot 78 0x006FD5A0
    virtual int unknown_slot86(int *damage, int distance, WarheadTypeClass *warhead, TechnoClass *source, bool forced, int arg6);  // slot 86 0x006FCA30
    virtual void unknown_slot87(CoordStruct const &source, bool forced, bool nokidding);        // slot 87 0x007072D0
    virtual void unknown_slot93(int arg1);                            // slot 93 0x006FE610
    virtual int unknown_slot95(RadioClass *radio, int message, long &param);         // slot 95 0x006FC1F0
    virtual int unknown_slot101(CellClass *arg1, int arg2, int arg3, int arg4, bool arg5);   // slot 101 0x00703040
    virtual bool unknown_slot122();                                   // slot 122 0x00707A40
    virtual int unknown_slot126();                                    // slot 126 0x00707F50
    virtual int unknown_slot129();                                    // slot 129 0x00704440
    virtual int unknown_slot130();                                    // slot 130 0x00707940
    virtual int unknown_slot131();                                    // slot 131 0x007025A0
    virtual int unknown_slot132();                                    // slot 132 0x00702F60
    virtual int unknown_slot133();                                    // slot 133 0x00704680
    virtual int unknown_slot137();                                    // slot 137 0x00701580
    virtual int unknown_slot141();                                    // slot 141 0x00704B10
    virtual int unknown_slot145();                                    // slot 145 0x007046E0
    virtual bool unknown_slot159();                                   // slot 159 0x00707950
    virtual UnknownFacingDir unknown_slot162()                        // slot 162 0x0070A2E0 (inline: the turret or body facing)
    {
        if (Type->Turret) {
            return unknown_2f8.Current();
        }
        return unknown_2e0.Current();
    }
    virtual double unknown_slot165();                                 // slot 165 0x00705030
    virtual int unknown_slot166();                                    // slot 166 0x00704A20
    virtual int unknown_slot182(AbstractClass *object, Cell *cell);          // slot 182 0x00704730
    virtual UnknownFacingDir unknown_slot183();                             // slot 183 0x00704BB0
    virtual InfantryTypeClass *unknown_slot184();                     // slot 184 0x00704B00
    virtual bool unknown_slot201();                                   // slot 201 0x0070A240 (inline in the original: unknown_5c0 != -1 or the TechnoClass copy, called out of line; ours inlines it)
    virtual int unknown_slot218(AbstractClass *target, int weapon, int arg3);        // slot 218 0x00704C00
    virtual AbstractClass *unknown_slot219(int arg1, CoordStruct const *coord, bool arg3);        // slot 219 0x00706A10
    virtual BulletClass *unknown_slot221(AbstractClass *target, int arg2);                  // slot 221 0x00704ED0
    virtual bool unknown_slot222(HouseClass *house, int arg2);                  // slot 222 0x007099A0
    virtual void unknown_slot239();                                    // slot 239 0x006FBB40
    virtual void unknown_slot255(TechnoClass *techno);                           // slot 255 0x00709C70
    virtual void unknown_slot256();                                   // slot 256 0x00709D20
    virtual void unknown_slot260(AbstractClass *target, int arg2);                 // slot 260 0x007053F0
    virtual bool unknown_slot261(bool arg1, bool arg2);                 // slot 261 0x006FD630
    virtual bool unknown_slot274();                                   // slot 274 0x0070A260 (inline in the original: a jump to TechnoClass's copy, which ours inlines)
    virtual bool unknown_slot275();                                   // slot 275 0x0070A270 (as slot 274)
    virtual void unknown_slot280(int arg1);                           // slot 280 0x00709A20
    virtual void unknown_slot281(int arg1);                           // slot 281 0x00709AE0
    virtual bool unknown_slot284();                                   // slot 284 0x006FBBF0
    virtual void unknown_slot302(Cell const *cell, bool arg2);  // slot 302 0x00705160
    virtual void unknown_slot304();                                   // slot 304 0x00705070
    virtual bool INoticeSink_Unknown(int code, int arg);              // INoticeSink (+8) slot 0 0x00709890 (vtable 0x007ADDD4)

    // New virtuals (slots 310-312): the draw paths. Slot 67 (0x00700E70) calls
    // 310 or 311 with (point, a 16-byte Rect copy, depth), ret 0x1C; both call
    // 312 with the surface first, ret 0x20. Slot 311 passes the address of its
    // point argument on as a Point2D. Names are hypotheses.
    virtual void unknown_slot310(Point2D point, Rect window, int depth);    // slot 310 0x006FF690 (ret 0x1C)
    virtual void unknown_slot311(Point2D point, Rect window, int depth);    // slot 311 0x007005B0 (ret 0x1C)
    virtual void unknown_slot312(Surface &surface, Point2D point, Rect window, int depth);  // slot 312 0x006FF3E0 (ret 0x20)
    static void __fastcall Read_INI(CCINIClass &ini);                 // 0x00706AE0 (the [Units] section; hypothesis)
    static void __fastcall Write_INI(CCINIClass &ini);                // 0x00706F60 (the [Units] section; hypothesis)
    void unknown_709c30(ObjectTypeClass *type);                       // 0x00709C30 (sets the disguise; hypothesis)
    bool Clear_Unknown5B4_007049F0();                 // 0x007049F0
    bool unknown_6fbab0();                           // 0x006FBAB0
    bool unknown_7049c0(int arg1);                                    // 0x007049C0
    void unknown_704a80();                                            // 0x00704A80 (restarts the +0x2A8 change over the type's DeployTime; AI and slot 95 expand it inline)
    void unknown_704aa0();                                            // 0x00704AA0
    bool unknown_709790(Cell const *from, Cell const *to);   // 0x00709790 (hypothesis: whether a trip should use the path estimator)
    bool unknown_707170(TechnoClass *target);                         // 0x00707170 (hypothesis: may crush the target)
    void Unknown_006FAA30(); // 0x006FAA30; observed no-argument ECX call
    void Unknown_00709EC0(); // 0x00709EC0; observed no-argument ECX call
    void unknown_6fd3a0();                                            // 0x006FD3A0 (hypothesis: the death explosion)
    void unknown_6fbf40();                                            // 0x006FBF40 (hypothesis: an idle shuffle of an unmoving unit)
    void unknown_6fb890();                                            // 0x006FB890 (hypothesis: turret and body turning toward the target)
    void unknown_6fbc90();                                            // 0x006FBC90 (hypothesis: acts on the answer of slot 218 for the target)
    bool unknown_7013a0();                                            // 0x007013A0 (hypothesis: one step of harvesting)
    bool unknown_6fd930();                                            // 0x006FD930 (slot 132: may start deploying)
    bool unknown_6fdfc0();                                            // 0x006FDFC0 (slot 132: deploy check)
    int unknown_707130();                                             // 0x00707130 (the value of the stored load scaled by the owner; inlined everywhere)

    int unknown_5a8;                        // +0x5A8 (-1)
    UnitTypeClass *Type;                    // +0x5AC
    AbstractClass *unknown_5b0;             // +0x5B0 (swizzled)
    int unknown_5b4;                        // +0x5B4 (-1)
    bool unknown_5b8;                       // +0x5B8
    bool unknown_5b9;                       // +0x5B9
    bool unknown_5ba;                       // +0x5BA
    bool unknown_5bb;                       // +0x5BB
    int unknown_5bc;                        // +0x5BC (-1)
    int unknown_5c0;                        // +0x5C0 (-1)
    UnknownUnit5C4 *unknown_5c4;            // +0x5C4
    bool unknown_5c8;                       // +0x5C8
    int unknown_5cc;                        // +0x5CC
    wchar_t unknown_5d0[256];               // +0x5D0 the name slot 35 composes ("%s %s")
};

// Every unit (0x00866198): Units, declared in shared/foot.hpp.

// Unit.cpp's drawing rectangle (0x00AD0490): a copy of unknown_static_rect
// made by its dynamic initializer 0x006FA3D0; slot 312 (0x006FF3E0) offsets
// it by the draw position. Name is a hypothesis.
extern Rect unknown_unit_rect_ad0490;

#endif
