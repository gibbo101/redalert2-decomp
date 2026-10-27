// SuperWeaponTypeClass: a super weapon of the rules (SuperWeaponType.cpp,
// members 0x0069EFC0-0x0069F943; RTTI vtables 0x007AC2B8 primary, 0x007AC29C
// IRTTITypeInfo at +4, 0x007AC294 INoticeSink, 0x007AC28C INoticeSource).
//
// Layout (constructor 0x0069F000, Read_INI 0x0069F450, Compute_CRC 0x0069F340):
//   +0x00  AbstractTypeClass (0x98 bytes)
//   +0x98  int ArrayIndex              SuperWeaponTypes count when constructed
//   +0x9C  WeaponTypeClass *WeaponType "WeaponType="
//   +0xA0  4 ints, -1                  not read by Read_INI (CRC'd)
//   +0xB0  int RechargeTime            frames; 4500 initially, "RechargeTime=" minutes * 900
//   +0xB4  int Type                    index in SuperWeaponTypeNames ("Type="), -1
//   +0xB8  void const *SidebarIcon     SidebarImage + ".SHP" from the mixfiles (XXICON.SHP fallback)
//   +0xBC  int Action                  "Action=" (ActionType name)
//   +0xC0  BuildingTypeClass *AuxBuilding  "AuxBuilding="
//   +0xC4  FixedString<25> SidebarImage    the ID initially
//   +0xDD  bool UseChargeDrain, +0xDE IsPowered (true), +0xDF DisableableFromShell,
//   +0xE0  bool PreClick, +0xE1 PostClick
//   +0xE4  int PreDependent            a Type index ("PreDependent="), -1
//   +0xE8  bool ShowTimer, +0xE9 ManualControl
//   size 0xEC (Size_Of); Kind_Of answers 0x20.
// Every constructed type is added to SuperWeaponTypes (0x00A40338) and removed
// by the destructor. Key names are the INI keys Read_INI reads.
#ifndef SHARED_SUPER_WEAPON_TYPE_HPP
#define SHARED_SUPER_WEAPON_TYPE_HPP

#include "shared/abstract_type.hpp"
#include "shared/weapon_type.hpp"
#include "shared/cc_file_class.hpp"
#include "shared/mix_file_class.hpp"

class WeaponTypeClass;
class BuildingTypeClass;

// BuildingTypeClass::Find_Or_Make, declared as a free function until
// shared/building_type.hpp is installed (WeaponTypeClass's is the member).
BuildingTypeClass *__fastcall BuildingTypeClass_Find_Or_Make(char const *name);   // 0x0045E0E0

// The super weapon type names (7 entries, 0x007F6648 .. "MultiMissile").
extern char const *SuperWeaponTypeNames[7];                    // 0x007F6648

extern "C" GUID const CLSID_SuperWeaponTypeClass;               // 0x007A1AE0

class SuperWeaponTypeClass : public AbstractTypeClass {
public:
    SuperWeaponTypeClass(char const *ini_name);                 // 0x0069F000
    SuperWeaponTypeClass(NoInitClass const &noinit);            // 0x0069F130
    virtual ~SuperWeaponTypeClass();                            // 0x0069F170

    // Index of a Type name in SuperWeaponTypeNames, or -1.
    static int __fastcall Type_From_Name(char const *name);     // 0x0069EFC0
    // Index in SuperWeaponTypes of the type with this ID (case-insensitive), or -1.
    static int __fastcall Find_Index(char const *name);         // 0x0069F790
    // The first type whose Action is action, or null.
    static SuperWeaponTypeClass *__fastcall From_Action(int action);    // 0x0069F7E0
    // The type with this ID, created when missing; null for "<none>" and "none".
    static SuperWeaponTypeClass *__fastcall Find_Or_Make(char const *name);   // 0x0069F820

    virtual HRESULT __stdcall GetClassID(GUID *classid);        // 0x0069F1F0
    virtual HRESULT __stdcall Load(IStream *stream);            // 0x0069F230
    virtual HRESULT __stdcall Save(IStream *stream, BOOL clear_dirty); // 0x0069F300
    virtual int Kind_Of() const;                                // 0x0069F320
    virtual int Size_Of() const;                                // 0x0069F330
    virtual void Compute_CRC(WWCRCEngine &crc) const;           // 0x0069F340
    virtual int unknown_slot16() const;                         // 0x0069F440 (ArrayIndex)
    virtual bool Read_INI(CCINIClass &ini);                     // 0x0069F450
    // Slot 27: the Action, whatever the arguments (0x0069F8B0).
    virtual int unknown_slot27(void const *unknown_a, void const *unknown_b) const;

    int ArrayIndex;                         // +0x98
    WeaponTypeClass *WeaponType;            // +0x9C
    int unknown_0xA0;                       // +0xA0
    int unknown_0xA4;                       // +0xA4
    int unknown_0xA8;                       // +0xA8
    int unknown_0xAC;                       // +0xAC
    int RechargeTime;                       // +0xB0
    int Type;                               // +0xB4
    void const *SidebarIcon;                // +0xB8
    int Action;                             // +0xBC
    BuildingTypeClass *AuxBuilding;         // +0xC0
    FixedString<25> SidebarImage;           // +0xC4
    bool UseChargeDrain;                    // +0xDD
    bool IsPowered;                         // +0xDE
    bool DisableableFromShell;              // +0xDF
    bool PreClick;                          // +0xE0
    bool PostClick;                         // +0xE1
    int PreDependent;                       // +0xE4
    bool ShowTimer;                         // +0xE8
    bool ManualControl;                     // +0xE9
};

extern DynamicVectorClass<SuperWeaponTypeClass *> SuperWeaponTypes;    // 0x00A40338

#endif
