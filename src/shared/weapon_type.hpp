// WeaponTypeClass: a weapon type (WeaponType.cpp, 0x00732CB0-0x007340FA;
// RTTI vtables 0x007AF470 primary (27 slots), 0x007AF444 IRTTITypeInfo at
// +4, 0x007AF468 INoticeSink, 0x007AF460 INoticeSource).
//
// Layout (from the constructor 0x00732EA0, the destructor 0x00733120,
// Compute_CRC 0x00733AB0 and Save 0x00733DF0; names are hypotheses):
//   +0x000  AbstractTypeClass (0x98)
//   +0x098  int unknown_98, +0x09C int Burst (1)
//   +0x0A0  BulletTypeClass *Projectile, +0x0A4 int, +0x0A8 int
//   +0x0AC  WarheadTypeClass *Warhead, +0x0B0 int, +0x0B4 int, +0x0B8 int
//   +0x0BC  TypeList<int> unknown_bc (vtable 0x0079D9F4)
//   +0x0D8  TypeList<AnimTypeClass *> Anim (vtable 0x007A3B3C)
//   +0x0F4  int, +0x0F8 int, +0x0FC..+0x116 bools (+0x10F, +0x113 true)
//   +0x118  int, +0x11C..+0x123 bools, +0x124 unsigned char (10),
//   +0x125..+0x12B bools, +0x12C int
//   size 0x130 (slot 12)
// Every type is added to WeaponTypes (0x00839B90) and removed when destroyed.
#ifndef RA2_SHARED_WEAPON_TYPE_HPP
#define RA2_SHARED_WEAPON_TYPE_HPP

#include "shared/bullet_type.hpp"
#include "shared/warhead_type.hpp"
#include "shared/rgb_class.hpp"

extern "C" GUID const CLSID_WeaponTypeClass;    // 0x007A1DA0

// Speed helpers (0x0047FCD0 returns a default speed for floating
// projectiles; 0x0047FB70 converts a range and speed; hypotheses).
double __cdecl Unknown_0047FCD0();
int __fastcall Unknown_0047FB70(int range, double speed);
struct UnknownFacingDir;
// Whether a ballistic shot reaches: the arc direction for a horizontal
// distance and height difference at a speed (0x0047F8B0; TechnoClass slot
// 170; hypothesis).
bool __fastcall Unknown_0047F8B0(bool arg1, int velocity, int distance, int height, double speed, UnknownFacingDir *dir);

// Armor kinds none, flak, plate, light, medium, heavy, wood, steel,
// concrete, special_1, special_2 (names 0x0079DE28).
enum ArmorType {
    ARMOR_NONE
};
// The armor type names (0x0079DE28: "none", "flak", ... "special_2").
extern char const *ArmorNames[11];
// The armor type named, or 0 (none) when unknown (name is a hypothesis).
ArmorType __fastcall Armor_From_Name(char const *name);                 // 0x00733A20

class WeaponTypeClass : public AbstractTypeClass {
public:
    WeaponTypeClass(char const *ini_name);                              // 0x00732EA0
    WeaponTypeClass(NoInitClass const &noinit);                         // 0x007330D0
    virtual ~WeaponTypeClass();                                         // 0x00733120

    virtual HRESULT __stdcall GetClassID(GUID *clsid);                  // 0x00733C50 slot 3
    virtual HRESULT __stdcall Load(IStream *stream);                    // 0x00733C90 slot 5
    virtual HRESULT __stdcall Save(IStream *stream, BOOL clear_dirty);  // 0x00733DF0 slot 6
    virtual int Kind_Of() const;                                        // 0x00733FE0 slot 11
    virtual int Size_Of() const;                                        // 0x00733FD0 slot 12
    virtual void Compute_CRC(WWCRCEngine &crc) const;                   // 0x00733AB0 slot 13
    virtual bool Read_INI(CCINIClass &ini);                             // 0x00733220 slot 25

    int unknown_func_733a60() const;                                    // 0x00733A60 (projectile flags; callers or the whole of eax: Building/Unit slot 219)
    bool unknown_func_733a90() const;                                   // 0x00733A90
    void unknown_func_7339c0();                                         // 0x007339C0 (sets unknown_a8)
    int unknown_func_733f70(int range) const;                           // 0x00733F70
    static int __fastcall Index_From_Name(char const *name);            // 0x00733F30 (-1 if none)
    static WeaponTypeClass *__fastcall Find_Or_Make(char const *name);  // 0x00733EA0

    int unknown_98;                         // +0x098
    int Burst;                              // +0x09C
    BulletTypeClass *Projectile;            // +0x0A0
    int unknown_a4;                         // +0x0A4
    int unknown_a8;                         // +0x0A8
    WarheadTypeClass *Warhead;              // +0x0AC
    int unknown_b0;                         // +0x0B0
    int unknown_b4;                         // +0x0B4
    int unknown_b8;                         // +0x0B8
    TypeList<int> unknown_bc;               // +0x0BC
    TypeList<AnimTypeClass *> Anim;         // +0x0D8
    AnimTypeClass *unknown_f4;              // +0x0F4 "AssaultAnim"
    ParticleSystemTypeClass *unknown_f8;    // +0x0F8 "AttachedParticleSystem"
    RGBClass unknown_fc;                    // +0x0FC "LaserInnerColor"
    RGBClass unknown_ff;                    // +0x0FF "LaserOuterColor"
    RGBClass unknown_102;                   // +0x102 "LaserOuterSpread"
    bool unknown_105;                       // +0x105
    bool unknown_106;                       // +0x106
    bool unknown_107;                       // +0x107
    bool unknown_108;                       // +0x108
    bool unknown_109;                       // +0x109
    bool unknown_10a;                       // +0x10A
    bool unknown_10b;                       // +0x10B
    bool unknown_10c;                       // +0x10C
    bool unknown_10d;                       // +0x10D
    bool unknown_10e;                       // +0x10E
    bool unknown_10f;                       // +0x10F
    bool unknown_110;                       // +0x110
    bool unknown_111;                       // +0x111
    bool unknown_112;                       // +0x112
    bool unknown_113;                       // +0x113
    bool unknown_114;                       // +0x114
    bool unknown_115;                       // +0x115
    bool unknown_116;                       // +0x116
    int unknown_118;                        // +0x118
    bool unknown_11c;                       // +0x11C
    bool unknown_11d;                       // +0x11D
    bool unknown_11e;                       // +0x11E
    bool unknown_11f;                       // +0x11F
    bool unknown_120;                       // +0x120
    bool unknown_121;                       // +0x121
    bool unknown_122;                       // +0x122
    bool unknown_123;                       // +0x123
    char unknown_124;                       // +0x124 "LaserDuration"
    bool unknown_125;                       // +0x125
    bool unknown_126;                       // +0x126
    bool unknown_127;                       // +0x127
    bool unknown_128;                       // +0x128
    bool unknown_129;                       // +0x129
    bool unknown_12a;                       // +0x12A
    bool unknown_12b;                       // +0x12B
    int unknown_12c;                        // +0x12C
};

// Every weapon type (0x00839B90; defined in the unit at 0x0040F720).
extern DynamicVectorClass<WeaponTypeClass *> unknown_WeaponTypeClass_list_00839b90;

#endif
