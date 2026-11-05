// SuperClass: a house's instance of a super weapon (Super.cpp, members
// 0x0069C660-0x0069ED8D; RTTI vtables 0x007AC210 primary, 0x007AC1F4
// IRTTITypeInfo at +4, 0x007AC1EC INoticeSink, 0x007AC1E4 INoticeSource).
//
// Layout (constructors 0x0069C660/0x0069C730, Load 0x0069E9F0,
// Compute_CRC 0x0069EB20, Detach 0x0069EAF0):
//   +0x00  AbstractClass (0x24 bytes)
//   +0x24  SuperWeaponTypeClass *Type
//   +0x28  HouseClass *House
//   +0x2C  CDTimerClass<FrameTimerClass> RechargeTimer   (DelayTime set from Type->RechargeTime)
//   +0x38  wchar_t const *unknown_0x38    the empty wide text (default constructor only)
//   +0x3C  bool, +0x40 int, +0x44 int     zeroed; +0x40/+0x44 cleared again by Load
//   +0x48  bool (true)
//   +0x4A  Cell unknown_0x4A        copied from 0x00ABD768 (2-byte aligned)
//   +0x50  AnimClass *Anim                its Loops byte (+0x175) and ID are CRC'd
//   +0x54  bool, +0x55..+0x58 bools       +0x54: Anim was detached; +0x57 cleared on recharge
//   +0x5C  int (-1), +0x60 int (-1)
//   size 0x68 (Size_Of); Kind_Of and What_Am_I answer 0x39.
// Constructed supers join Supers (0x00A35D28); the typed constructor also
// joins two other object lists (0x00AC0CB0, 0x00AC0D08). Field names other
// than Type, House, RechargeTimer and Anim are not recovered.
#ifndef SHARED_SUPER_HPP
#define SHARED_SUPER_HPP

#include "shared/anim.hpp"
#include "shared/cd_timer.hpp"
#include "shared/coord.hpp"
#include "shared/super_weapon_type.hpp"

class HouseClass;
class SuperWeaponTypeClass;

// Three fields the constructors clear in the order +4, +0, +8 (a bool and two
// ints; what they hold is not recovered).
struct SuperStateStruct {
    SuperStateStruct()
    {
        unknown_4 = 0;
        unknown_0 = false;
        unknown_8 = 0;
    }
    SuperStateStruct(NoInitClass const &) {}

    bool unknown_0;     // +0x00
    int unknown_4;      // +0x04
    int unknown_8;      // +0x08
};

// The super joins object.hpp's lists unknown_objects_ac0cb0 (0x00AC0CB0),
// unknown_abstracts_ac0d08 and unknown_abstracts_ac0bf8.
// The super weapon type whose placement is pending (4 while a chronosphere warp waits, else -1; hypothesis).
extern int unknown_pending_super_833694;                          // 0x00833694
extern Cell const unknown_cell_abd768;                            // 0x00ABD768

extern "C" GUID const CLSID_SuperClass;                         // 0x007A1AF0

class SuperClass : public AbstractClass {
public:
    SuperClass();                                               // 0x0069C660
    SuperClass(SuperWeaponTypeClass *type, HouseClass *house);  // 0x0069C730
    // Load path: a fresh AbstractClass part, the other fields kept (inline).
    SuperClass(NoInitClass const &noinit) : AbstractClass(), RechargeTimer(noinit), unknown_0x3C(noinit) {}
    virtual ~SuperClass();                                      // 0x0069C8B0

    // Drops the animation (and the animation-list entry it implies).
    void unknown_69ca70();                                      // 0x0069CA70
    // Drops the animation and restarts the recharge timer.
    void unknown_69ebb0();                                      // 0x0069EBB0
    // Whether the sidebar should flash its tab for it (ready; hypothesis).
    bool Unknown_0069D820();                                    // 0x0069D820
#ifdef RA2_SELECT_ACTION_UNIT
    void Unknown_0069D680();                                    // 0x0069D680 (the click while not ready; TS Impatient_Click)
#endif
    // Grants it to its house (TS's Grant(one_time, announce, on_hold); hypothesis; true when granted).
    bool unknown_69d390(bool local_player); // original0069D390, AL result/RET4; meaning remains a hypothesis
    // Starts the chrono placement animation (Rules->ChronoPlacement) 5 leptons above coord (hypothesis).
    void unknown_place_anim_69cb30(CoordStruct coord);          // 0x0069CB30
    bool Suspend(bool on);                                      // 0x0069CC60
    bool Remove();                                              // 0x0069CF40
    bool Recharge(bool player);                                 // 0x0069CFC0
    bool Discharged(bool player, Cell const &cell);             // 0x0069D090
    int Anim_Stage() const;                                     // 0x0069D560
    void Forced_Charge(bool player);                            // 0x0069D690
    bool Is_Powered() const;                                    // 0x0069D760
    wchar_t const *State_String() const;                        // 0x0069D770
    void Place(Cell const &cell, bool player);                  // 0x0069D850
    bool unknown_69e990() const;                                // 0x0069E990
    bool Is_Present() const { return unknown_0x55; }
    bool Is_One_Time() const { return unknown_0x56 && unknown_0x55; }
    bool Grant(bool one_time, bool announce, bool on_hold);     // 0x0069CCF0

    virtual int __stdcall What_Am_I();                          // 0x0069ECA0
    virtual HRESULT __stdcall GetClassID(GUID *classid);        // 0x0069E9B0
    virtual HRESULT __stdcall Load(IStream *stream);            // 0x0069E9F0
    virtual HRESULT __stdcall Save(IStream *stream, BOOL clear_dirty); // 0x0069EAD0
    virtual void Detach(AbstractClass *target, bool all = true);    // 0x0069EAF0
    virtual int Kind_Of() const;                                // 0x0069ECB0
    virtual int Size_Of() const;                                // 0x0069ECC0
    virtual void Compute_CRC(WWCRCEngine &crc) const;           // 0x0069EB20

    SuperWeaponTypeClass *Type;                 // +0x24
    HouseClass *House;                          // +0x28
    CDTimerClass<FrameTimerClass> RechargeTimer;    // +0x2C
    wchar_t const *unknown_0x38;                // +0x38
    SuperStateStruct unknown_0x3C;              // +0x3C (+0x40 and +0x44 cleared again by Load)
    bool unknown_0x48;                          // +0x48
    Cell unknown_0x4A;                    // +0x4A
    AnimClass *Anim;                            // +0x50
    bool AnimDetached;                          // +0x54
    bool unknown_0x55;                          // +0x55
    bool unknown_0x56;                          // +0x56
    bool unknown_0x57;                          // +0x57
    bool unknown_0x58;                          // +0x58
    int unknown_0x5C;                           // +0x5C
    int unknown_0x60;                           // +0x60
    int unknown_0x64;                           // +0x64 (size 0x68) not written here
};

extern DynamicVectorClass<SuperClass *> Supers;                 // 0x00A35D28
// Another list the destructor removes the super from (meaning not recovered).
extern DynamicVectorClass<SuperClass *> unknown_supers_a35db8;  // 0x00A35DB8

#endif
