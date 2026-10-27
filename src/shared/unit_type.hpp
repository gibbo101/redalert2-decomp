// UnitTypeClass: vehicle types (UnitType.cpp, members 0x0070A600-0x0070B68A;
// RTTI vtables 0x007AE328 primary, 0x007AE30C IRTTITypeInfo at +4,
// 0x007AE304 INoticeSink, 0x007AE2FC INoticeSource).
//
// Layout from the constructor 0x0070A600, Read_INI 0x0070AB40,
// Compute_CRC 0x0070B3E0 and Load 0x0070B480 (names are the INI keys read
// into each member):
//   +0x000  TechnoTypeClass (0xB90)
//   +0xB90  int ArrayIndex        index in UnitTypes (slot 16)
//   +0xB94  int MovementRestrictedTo (-1)
//   +0xB98  CoordStruct HalfDamageSmokeLocation
//   +0xBA4..+0xBB3  flags (IsTilter true)
//   +0xBB4..+0xBD4  frame counts (art INI)
//   +0xBD8  int FiringSyncFrame[2], +0xBE0 int BurstDelay[4]  (-1)
//   +0xBF0  void const *AltImage (loaded from AltImageFile + ".SHP")
//   +0xBF4  char WalkFrames (12), +0xBF5 char FiringFrames
//   +0xBF6  FixedString<25> AltImageFile
//   size 0xC10 (Size_Of, Find_Or_Make's allocation)
#ifndef RA2_SHARED_UNIT_TYPE_HPP
#define RA2_SHARED_UNIT_TYPE_HPP

#include "shared/techno_type.hpp"

#ifndef E_POINTER
#define E_POINTER ((HRESULT)0x80004003L)
#endif

// A vehicle: only the constructor UnitType.cpp calls (0x7D0 bytes).
// shared/unit.hpp has the full class and defines RA2_UNIT_FULL before
// including this header.
#ifndef RA2_UNIT_FULL
class UnitClass {
public:
    UnitClass(UnitTypeClass *type, HouseClass *house);                 // 0x006FA400

    char unknown_000[0x7D0];
};
#else
class UnitClass;
#endif

// The class ID GetClassID reports (0x007A1B00).
extern "C" GUID const unknown_clsid_unit_type_7a1b00;
// The height factor slot 31 doubles (0x00AD0600).
extern int unknown_ad0600;

// Shape file retrieval by name: MixFileClass<CCFileClass>::Retrieve, shared/mix_file_class.hpp.
// The CRT's _makepath (0x007831F0).
extern "C" void __cdecl _makepath(char *path, char const *drive, char const *dir, char const *fname, char const *ext);

class UnitTypeClass : public TechnoTypeClass {
public:
    UnitTypeClass(char const *ini_name);                                // 0x0070A600
    UnitTypeClass(NoInitClass const &noinit);                           // 0x0070A7E0
    virtual ~UnitTypeClass();                                           // 0x0070A810

    virtual HRESULT __stdcall GetClassID(GUID *clsid);                  // 0x0070B3A0
    virtual HRESULT __stdcall Load(IStream *stream);                    // 0x0070B480
    virtual HRESULT __stdcall Save(IStream *stream, BOOL clear_dirty);  // 0x0070B520
    virtual int Kind_Of() const;                                        // 0x0070B5E0 (0x28)
    virtual int Size_Of() const;                                        // 0x0070B5D0
    virtual void Compute_CRC(WWCRCEngine &crc) const;                   // 0x0070B3E0
    virtual int unknown_slot16() const;                                 // 0x0070B5F0 (ArrayIndex)
    virtual bool Read_INI(CCINIClass &ini);                             // 0x0070AB40
    virtual CoordStruct unknown_slot27(CoordStruct const &coord) const; // 0x0070B320 (raised to the ground)
    virtual CoordStruct unknown_slot30() const;                         // 0x0070AAB0
    virtual CoordStruct unknown_slot31() const;                         // 0x0070AAF0
    virtual bool unknown_slot32(Cell const &cell, HouseClass *house) const; // 0x0070A9D0
    virtual ObjectClass *unknown_slot35(HouseClass *house) const;       // 0x0070AA80 (new vehicle)
    virtual bool unknown_slot40() const;                                // 0x0070A8E0 (TechnoType's)
    virtual bool unknown_slot41() const;                                // 0x0070A8F0 (TechnoType's)
    virtual int Repair_Step() const;                                    // 0x0070B390

    static int __fastcall From_Name(char const *name);                  // 0x0070A890
    static UnitTypeClass *__fastcall Find_Or_Make(char const *name);    // 0x0070B540

    int ArrayIndex;                         // +0xB90
    int MovementRestrictedTo;               // +0xB94
    CoordStruct HalfDamageSmokeLocation;    // +0xB98
    bool Passive;                           // +0xBA4
    bool CrateGoodie;                       // +0xBA5
    bool Harvester;                         // +0xBA6
    bool Weeder;                            // +0xBA7
    bool unknown_ba8;                       // +0xBA8
    bool unknown_ba9;                       // +0xBA9
    bool DeployToFire;                      // +0xBAA
    bool IsSimpleDeployer;                  // +0xBAB
    bool IsTilter;                          // +0xBAC
    bool UseTurretShadow;                   // +0xBAD
    bool TooBigToFitUnderBridge;            // +0xBAE
    bool CanBeach;                          // +0xBAF
    bool SmallVisceroid;                    // +0xBB0
    bool LargeVisceroid;                    // +0xBB1
    bool CarriesCrate;                      // +0xBB2
    bool NonVehicle;                        // +0xBB3
    int StandingFrames;                     // +0xBB4
    int DeathFrames;                        // +0xBB8
    int DeathFrameRate;                     // +0xBBC
    int StartStandFrame;                    // +0xBC0
    int StartWalkFrame;                     // +0xBC4
    int StartFiringFrame;                   // +0xBC8
    int StartDeathFrame;                    // +0xBCC
    int MaxDeathCounter;                    // +0xBD0
    int Facings;                            // +0xBD4
    int FiringSyncFrame[2];                 // +0xBD8
    int BurstDelay[4];                      // +0xBE0
    void const *AltImage;                   // +0xBF0
    char WalkFrames;                        // +0xBF4
    char FiringFrames;                      // +0xBF5
    FixedString<25> AltImageFile;           // +0xBF6
};

typedef char UnitTypeClass_size_check[(sizeof(UnitTypeClass) == 0xC10) ? 1 : -1];

extern DynamicVectorClass<UnitTypeClass *> UnitTypes;   // 0x00A35D48

#endif
