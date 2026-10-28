// AircraftTypeClass: aircraft types (AircraftType.cpp, members
// 0x0041BC90-0x0041C3CA; RTTI vtables 0x0079B678 primary, 0x0079B65C
// IRTTITypeInfo at +4, 0x0079B654 INoticeSink, 0x0079B64C INoticeSource).
//
// Layout from the constructor 0x0041BC90, Read_INI 0x0041BFD0 and
// Compute_CRC 0x0041C110 (names are the INI keys read into each member):
//   +0x000  TechnoTypeClass (0xB90)
//   +0xB90  int ArrayIndex         index in AircraftTypes (slot 16)
//   +0xB94  bool Carryall
//   +0xB98  AnimTypeClass *Trailer (art INI; swizzled by Load)
//   +0xB9C  int SpawnDelay         (art INI)
//   +0xBA0  bool Rotors, +0xBA1 CustomRotor (art INI), +0xBA2 Landable,
//   +0xBA3  AirportBound, +0xBA4 Fighter
//   size 0xBA8 (Size_Of, Find_Or_Make's allocation)
#ifndef RA2_SHARED_AIRCRAFT_TYPE_HPP
#define RA2_SHARED_AIRCRAFT_TYPE_HPP

#include "shared/anim_type.hpp"
#include "shared/techno_type.hpp"

class AircraftClass;

#ifndef E_POINTER
#define E_POINTER ((HRESULT)0x80004003L)
#endif

// Type lookup by name, making an empty type when unknown (0x004264A0;
// hypothesis: AnimTypeClass::Find_Or_Make).

// An animation type named by an INI entry, or `defvalue` when the entry
// is absent (expanded inline: the default is loaded before the read).
inline AnimTypeClass *Get_Anim_Type(CCINIClass &ini, char const *section, char const *entry, AnimTypeClass *defvalue)
{
    char buffer[128];
    if (ini.Get_String(section, entry, unknown_string_83c55c, buffer, sizeof(buffer))) {
        return AnimTypeClass::Find_Or_Make(buffer);
    }
    return defvalue;
}

// An aircraft (only its constructor is used here; 0x5C0 bytes). The full
// class is shared/aircraft.hpp, which includes this header and skips the
// stand-in.
#ifndef RA2_SHARED_AIRCRAFT_HPP
class AircraftClass {
public:
    AircraftClass(AircraftTypeClass *type, HouseClass *house);         // 0x00413A40
    static void __fastcall Read_INI_0041A840(CCINIClass &ini);        // 0x0041A840 (as shared/aircraft.hpp)

    char unknown_000[0x5C0];
};
#endif

// Shape file retrieval by name: MixFileClass<CCFileClass>::Retrieve, shared/mix_file_class.hpp.

// The class ID GetClassID reports (0x007A1B20).
extern "C" GUID const unknown_clsid_aircraft_type_7a1b20;

class AircraftTypeClass : public TechnoTypeClass {
public:
    AircraftTypeClass(char const *ini_name);                            // 0x0041BC90
    AircraftTypeClass(NoInitClass const &noinit);                       // 0x0041BDB0
    virtual ~AircraftTypeClass();                                       // 0x0041BDE0

    virtual HRESULT __stdcall GetClassID(GUID *clsid);                  // 0x0041C210
    virtual HRESULT __stdcall Load(IStream *stream);                    // 0x0041C180
    virtual HRESULT __stdcall Save(IStream *stream, BOOL clear_dirty);  // 0x0041C1F0
    virtual int Kind_Of() const;                                        // 0x0041C310 (3)
    virtual int Size_Of() const;                                        // 0x0041C320
    virtual void Compute_CRC(WWCRCEngine &crc) const;                   // 0x0041C110
    virtual int unknown_slot16() const;                                 // 0x0041C330 (ArrayIndex)
    virtual bool Read_INI(CCINIClass &ini);                             // 0x0041BFD0
    virtual CoordStruct unknown_slot31() const;                         // 0x0041BFA0
    virtual bool unknown_slot32(Cell const &cell, HouseClass *house) const; // 0x0041BF90 (false)
    virtual ObjectClass *unknown_slot35(HouseClass *house) const;       // 0x0041BED0 (new aircraft)
    virtual Cell const *unknown_slot36(int arg1) const;           // 0x0041BF20
    virtual bool unknown_slot40() const;                                // 0x0041BF00 (false)
    virtual bool unknown_slot41() const;                                // 0x0041BF10 (false)

    static int __fastcall From_Name(char const *name);                  // 0x0041BE60
    static void Init();                                                 // 0x0041BEB0 (rotor shapes)
    static AircraftTypeClass *__fastcall Find_Or_Make(char const *name); // 0x0041C250

    int ArrayIndex;                     // +0xB90
    bool Carryall;                      // +0xB94
    AnimTypeClass *Trailer;             // +0xB98
    int SpawnDelay;                     // +0xB9C
    bool Rotors;                        // +0xBA0
    bool CustomRotor;                   // +0xBA1
    bool Landable;                      // +0xBA2
    bool AirportBound;                  // +0xBA3
    bool Fighter;                       // +0xBA4
};

typedef char AircraftTypeClass_size_check[(sizeof(AircraftTypeClass) == 0xBA8) ? 1 : -1];

extern DynamicVectorClass<AircraftTypeClass *> AircraftTypes;   // 0x00A3D278

// The height factor slot 31 doubles (0x0083C550).
extern int unknown_83c550;

// The rotor shapes Init loads (0x0083C554, 0x0083C558).
extern void const *unknown_left_rotor_83c554;
extern void const *unknown_right_rotor_83c558;

#endif
