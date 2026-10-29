// InfantryTypeClass: infantry types (InfantryType.cpp, members
// 0x00509B20-0x0050B0D9; RTTI vtables 0x007A3A78 primary, 0x007A3A5C
// IRTTITypeInfo at +4, 0x007A3A54 INoticeSink, 0x007A3A4C INoticeSource).
//
// Layout from the constructor 0x00509B20, Read_INI 0x0050A3C0, the art
// sequence reader 0x0050A0E0, Compute_CRC 0x0050AA20 and Load/Save (names are
// the INI keys read into each member):
//   +0x000  TechnoTypeClass (0xB90)
//   +0xB90  int ArrayIndex        index in InfantryTypes (slot 16)
//   +0xB94  int Pip (1)
//   +0xB98  DoInfoStruct *DoControls   38 sequence entries (0x260 bytes,
//                                      owned; saved and CRCed as bytes)
//   +0xB9C  int FireUp, +0xBA0 int FireProne
//   +0xBA4  TypeList<AnimTypeClass *> DeadBodies, +0xBC0 DeathAnims
//   +0xBDC  TypeList<int> VoiceComment
//   +0xBF8  int EnterWaterSound, +0xBFC LeaveWaterSound (-1)
//   +0xC00..+0xC16  flags (Crawls true), +0xC04 int DetectionDistance
//   size 0xC18 (Size_Of, Find_Or_Make's allocation)
#ifndef RA2_SHARED_INFANTRY_TYPE_HPP
#define RA2_SHARED_INFANTRY_TYPE_HPP

#include "shared/techno_type.hpp"

#ifndef E_POINTER
#define E_POINTER ((HRESULT)0x80004003L)
#endif

class InfantryTypeClass;

// One animation sequence (Sequence= art entries "%d,%d,%d,<facing>").
struct DoInfoStruct {
    int Frame;
    int Count;
    int Jump;
    int Facing;     // 0..7 (N, NE, E, SE, S, SW, W, NW), -1 when unset
};

#ifdef RA2_INFANTRY_FULL
// InfantryClass is declared in shared/infantry.hpp (InfantryType.cpp
// includes it for slot 35).
class InfantryClass;
#else
// An infantry unit (only its constructor and ObjectClass virtuals are used
// here; 0x5D8 bytes; the full class is in the Infantry workers'
// shared/infantry.hpp proposals, derived through FootClass).
class InfantryTypeClass;
class InfantryClass : public ObjectClass {
public:
    InfantryClass(InfantryTypeClass *type, HouseClass *house);         // 0x004FF640
    static void __fastcall Read_INI(CCINIClass &ini);                 // 0x00506960 (as shared/infantry.hpp)
    static void __fastcall Write_INI(CCINIClass &ini);                // 0x00506D70 (as shared/infantry.hpp)

    virtual HRESULT __stdcall GetClassID(GUID *clsid);
    virtual HRESULT __stdcall Save(IStream *stream, BOOL clear_dirty);
    virtual int Kind_Of() const;
    virtual int Size_Of() const;

    bool unknown_5090a0() const;            // 0x005090A0 (as shared/infantry.hpp; TeamClass 0x006BB8B0)

    char unknown_098[0x5A8 - 0x98];         // TechnoClass/FootClass members
    InfantryTypeClass *Type;                // +0x5A8 (as shared/infantry.hpp; TeamClass 0x006B9BB0)
    char unknown_5ac[0x5D8 - 0x5AC];        // InfantryClass members
};
#endif

// The class ID GetClassID reports (0x007A1B10).
extern "C" GUID const unknown_clsid_infantry_type_7a1b10;
// The height factor slot 31 doubles (0x00A411B0).
extern int unknown_a411b0;

class InfantryTypeClass : public TechnoTypeClass {
public:
    InfantryTypeClass(char const *ini_name);                            // 0x00509B20
    InfantryTypeClass(NoInitClass const &noinit);                       // 0x00509D60
    virtual ~InfantryTypeClass();                                       // 0x00509DB0

    virtual HRESULT __stdcall GetClassID(GUID *clsid);                  // 0x0050AE90
    virtual HRESULT __stdcall Load(IStream *stream);                    // 0x0050AB40
    virtual HRESULT __stdcall Save(IStream *stream, BOOL clear_dirty);  // 0x0050AD80
    virtual int Kind_Of() const;                                        // 0x0050AF60 (0x10)
    virtual int Size_Of() const;                                        // 0x0050AF70
    virtual void Compute_CRC(WWCRCEngine &crc) const;                   // 0x0050AA20
    virtual int unknown_slot16() const;                                 // 0x0050AF80 (ArrayIndex)
    virtual bool Read_INI(CCINIClass &ini);                             // 0x0050A3C0
    virtual CoordStruct unknown_slot27(CoordStruct const &coord) const; // 0x0050A9B0 (raised to the ground)
    virtual CoordStruct unknown_slot31() const;                         // 0x0050A940
    virtual bool unknown_slot32(Cell const &cell, HouseClass *house) const; // 0x00509F20
    virtual ObjectClass *unknown_slot35(HouseClass *house) const;       // 0x00509EF0 (new infantry)
    virtual Cell const *unknown_slot36(int arg1) const;           // 0x0050A000
    virtual bool unknown_slot40() const;                                // 0x0050A990 (TechnoType's)
    virtual bool unknown_slot41() const;                                // 0x0050A9A0 (TechnoType's)
    virtual int Repair_Cost() const;                                    // 0x0050A980 (0)
    virtual int Repair_Step() const;                                    // 0x0050A970

    static int __fastcall From_Name(char const *name);                  // 0x0050A070
    void Read_Sequence();                                               // 0x0050A0E0 (name hypothesis)
    static InfantryTypeClass *__fastcall Find_Or_Make(char const *name); // 0x0050AED0

    int ArrayIndex;                         // +0xB90
    int Pip;                                // +0xB94
    DoInfoStruct *DoControls;               // +0xB98
    int FireUp;                             // +0xB9C
    int FireProne;                          // +0xBA0
    TypeList<AnimTypeClass *> DeadBodies;   // +0xBA4
    TypeList<AnimTypeClass *> DeathAnims;   // +0xBC0
    TypeList<int> VoiceComment;             // +0xBDC
    int EnterWaterSound;                    // +0xBF8
    int LeaveWaterSound;                    // +0xBFC
    bool Cyborg;                            // +0xC00
    bool NotHuman;                          // +0xC01
    bool Ivan;                              // +0xC02
    int DetectionDistance;                  // +0xC04
    bool Occupier;                          // +0xC08
    bool Assaulter;                         // +0xC09
    bool Fearless;                          // +0xC0A
    bool Crawls;                            // +0xC0B
    bool Infiltrate;                        // +0xC0C
    bool Fraidycat;                         // +0xC0D
    bool TiberiumProof;                     // +0xC0E
    bool Civilian;                          // +0xC0F
    bool C4;                                // +0xC10
    bool Engineer;                          // +0xC11
    bool Agent;                             // +0xC12
    bool Thief;                             // +0xC13
    bool VehicleThief;                      // +0xC14
    bool Doggie;                            // +0xC15
    bool Deployer;                          // +0xC16
};

typedef char InfantryTypeClass_size_check[(sizeof(InfantryTypeClass) == 0xC18) ? 1 : -1];

extern DynamicVectorClass<InfantryTypeClass *> InfantryTypes;   // 0x00A40350

#endif
