// HouseTypeClass: a country (house type) of the rules (HouseType.cpp,
// members 0x004F90F0-0x004FA566 and the adjustor thunks 0x004FB6B0-0x004FB6D9;
// RTTI vtables 0x007A3048 primary, 0x007A302C IRTTITypeInfo at +4,
// 0x007A3024 INoticeSink, 0x007A301C INoticeSource).
//
// Layout (constructor 0x004F90F0, Compute_CRC 0x004F9E40, Load/Save):
//   +0x00   AbstractTypeClass (0x98 bytes)
//   +0x98   FixedString<25> ParentCountry
//   +0xB4   int ArrayIndex       index in HouseTypes (slot 16 answers it)
//   +0xB8   int House            index in HouseTypes (Find_Index answers it; owner bit)
//   +0xBC   int Side             -1 initially
//   +0xC0   int Color            0 initially
//   +0xC4   4 bytes not written by these members
//   +0xC8   7 doubles, 1.0       cost/strength multipliers (names hypotheses)
//   +0x100  19 floats, 1.0       not recovered
//   +0x14C  TypeList<InfantryTypeClass *> VeteranInfantry
//   +0x168  TypeList<UnitTypeClass *> VeteranUnits
//   +0x184  TypeList<AircraftTypeClass *> VeteranAircraft
//   +0x1A0  char Suffix[4]
//   +0x1A4  char Prefix          'A' initially
//   +0x1A5  bool Multiplay, +0x1A6 MultiplayPassive, +0x1A7 WallOwner (true),
//   +0x1A8  bool SmartAI
//   +0x1AC  4 bytes not written by these members
//   size 0x1B0 (Size_Of)
// Kind_Of answers 0x0E. Every constructed house type is added to HouseTypes
// (0x00A35D08) and removed by the destructor. The key names follow
// Westwood's [Country] vocabulary; offsets are observed, the names of the
// multipliers and of the bools are hypotheses.
#ifndef SHARED_HOUSE_TYPE_HPP
#define SHARED_HOUSE_TYPE_HPP

#include "shared/abstract_type.hpp"
#include "shared/type_list.hpp"

class InfantryTypeClass;
class UnitTypeClass;
class AircraftTypeClass;


extern "C" GUID const CLSID_HouseTypeClass;                 // 0x007A1BA0 (GetClassID)

class HouseTypeClass : public AbstractTypeClass {
public:
    HouseTypeClass(char const *ini_name);                       // 0x004F90F0
    HouseTypeClass(NoInitClass const &noinit);                  // 0x004F9350
    virtual ~HouseTypeClass();                                  // 0x004F93A0

    // Index (House) of the type whose Name or ID equals the name (case
    // insensitive); -2 for "<random>", -1 when none matches.
    static int __fastcall Find_Index(char const *name);         // 0x004F94D0
    // The type with this ID, created when missing; null for "<none>" and "none".
    static HouseTypeClass *__fastcall Find_Or_Make(char const *name);  // 0x004FA350

    virtual HRESULT __stdcall QueryInterface(GUID const &iid, void **object);  // 0x004FA270
    virtual unsigned long __stdcall AddRef();                   // 0x004FA410 (1)
    virtual unsigned long __stdcall Release();                  // 0x004FA420 (1)
    virtual HRESULT __stdcall GetClassID(GUID *classid);        // 0x004FA310
    virtual HRESULT __stdcall IsDirty();                        // 0x004F9F50 (S_OK)
    virtual HRESULT __stdcall Load(IStream *stream);            // 0x004F9F60
    virtual HRESULT __stdcall Save(IStream *stream, BOOL clear_dirty);  // 0x004FA150
    virtual HRESULT __stdcall GetSizeMax(ULARGE_INTEGER *size); // 0x004FA240
    virtual int Kind_Of() const;                                // 0x004FA3E0
    virtual int Size_Of() const;                                // 0x004FA3F0
    virtual void Compute_CRC(WWCRCEngine &crc) const;           // 0x004F9E40
    virtual int unknown_slot16() const;                         // 0x004FA400 (ArrayIndex)
    virtual bool Read_INI(CCINIClass &ini);                     // 0x004F9550

    FixedString<25> ParentCountry;                  // +0x98
    int ArrayIndex;                                 // +0xB4
    int House;                                      // +0xB8
    int Side;                                       // +0xBC
    int Color;                                      // +0xC0
    int unknown_0xC4;                               // +0xC4 (/Zp4: not alignment) not written here
    double FirepowerMult;                           // +0xC8
    double GroundspeedMult;                         // +0xD0
    double AirspeedMult;                            // +0xD8
    double ArmorMult;                               // +0xE0
    double ROFMult;                                 // +0xE8
    double CostMult;                                // +0xF0
    double BuildtimeMult;                           // +0xF8
    float unknown_0x100;
    float unknown_0x104;
    float unknown_0x108;
    float unknown_0x10C;
    float unknown_0x110;
    float unknown_0x114;
    float unknown_0x118;
    float unknown_0x11C;
    float unknown_0x120;
    float unknown_0x124;
    float unknown_0x128;
    float unknown_0x12C;
    float unknown_0x130;
    float unknown_0x134;
    float unknown_0x138;
    float unknown_0x13C;
    float unknown_0x140;
    float unknown_0x144;
    float unknown_0x148;
    TypeList<InfantryTypeClass *> VeteranInfantry;  // +0x14C
    TypeList<UnitTypeClass *> VeteranUnits;         // +0x168
    TypeList<AircraftTypeClass *> VeteranAircraft;  // +0x184
    char Suffix[4];                                 // +0x1A0
    char Prefix;                                    // +0x1A4
    bool Multiplay;                                 // +0x1A5
    bool MultiplayPassive;                          // +0x1A6
    bool WallOwner;                                 // +0x1A7
    bool SmartAI;                                   // +0x1A8
    int unknown_0x1AC;                              // +0x1AC (size 0x1B0) not written here
};

extern DynamicVectorClass<HouseTypeClass *> HouseTypes;         // 0x00A35D08

#endif
