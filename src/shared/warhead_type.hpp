// WarheadTypeClass: the damage rules of a warhead type (WarheadType.cpp,
// 0x0071FEF0-0x007211A7; RTTI vtables 0x007AEC08 primary (27 slots),
// 0x007AEBEC IRTTITypeInfo at +4, 0x007AEBE4 INoticeSink, 0x007AEBDC
// INoticeSource).
//
// Layout (from the constructor 0x00720100, the NoInitClass constructor
// 0x00720360, the destructor 0x007203D0 and Load 0x00720DB0; names are
// hypotheses; member names follow the INI keys Read_INI 0x007204E0 reads):
//   +0x000  AbstractTypeClass (0x98)
//   +0x098  double Deform (0)
//   +0x0A0  double Verses[11]          every entry 1.0
//   +0x0F8  double ProneDamage (1.0)
//   +0x100  int DeformThreshhold
//   +0x104  TypeList<AnimTypeClass *> AnimList (vtable 0x007A3B3C)
//   +0x120  int InfDeath, +0x124 float CellSpread, +0x128 float CellInset,
//   +0x12C  float PercentAtMax (1.0), +0x130 bool CausesDelayKill,
//   +0x134  int DelayKillFrames (5), +0x138 float DelayKillAtMax (1.0),
//   +0x13C  float CombatLightSize
//   +0x140  ParticleSystemTypeClass *Particle (swizzled; Detach clears it)
//   +0x144..+0x158  bools, +0x15C int, +0x160..+0x166 bools
//   +0x168..+0x174  ints
//   size 0x178 (slot 12)
// Every type is added to WarheadTypes (0x00839B00) and to the abstract list
// 0x00AC0CB0, and removed from WarheadTypes when destroyed.
#ifndef RA2_SHARED_WARHEAD_TYPE_HPP
#define RA2_SHARED_WARHEAD_TYPE_HPP

#include "shared/abstract_type.hpp"
#include "shared/type_list.hpp"

class AnimTypeClass;
class ParticleSystemTypeClass;

extern "C" GUID const CLSID_WarheadTypeClass;   // 0x007A1DB0

// A percentage or plain number ("50%" -> 0.5; hypothesis: Westwood's
// fixed-point/percent INI value parser).
double __fastcall Percent_Value(char const *text);                     // 0x007200C0
extern "C" char *__cdecl strchr(char const *string, int character);
extern "C" int __cdecl atoi(char const *string);
extern "C" double __cdecl atof(char const *string);

// Name lookups of other type classes, declared as free functions until
// their headers exist (AnimTypeClass::Find_Or_Make 0x004264A0 and
// ParticleSystemTypeClass::Find_Or_Make 0x00620DF0, both __fastcall).
AnimTypeClass *__fastcall Find_Or_Make_AnimType_004264a0(char const *name);
ParticleSystemTypeClass *__fastcall Find_Or_Make_ParticleSystemType_00620df0(char const *name);

// The empty string INI readers default to (0x0083C55C; also object_type.hpp).
extern char unknown_string_83c55c[];

// Whether the INI has the section (an inline test of Find_Section).
inline bool Section_Present(CCINIClass &ini, char const *section, char const *entry = 0)
{
    if (entry == 0) {
        return ini.Find_Section(section) != 0;
    }
    return ini.Find_Entry(section, entry) != 0;
}

// Called first by the type destructors (0x006ECB90; also ObjectClass's).

class WarheadTypeClass : public AbstractTypeClass {
public:
    WarheadTypeClass(char const *ini_name);                             // 0x00720100
    WarheadTypeClass(NoInitClass const &noinit);                        // 0x00720360
    virtual ~WarheadTypeClass();                                        // 0x007203D0

    virtual HRESULT __stdcall GetClassID(GUID *clsid);                  // 0x00720D70 slot 3
    virtual HRESULT __stdcall Load(IStream *stream);                    // 0x00720DB0 slot 5
    virtual HRESULT __stdcall Save(IStream *stream, BOOL clear_dirty);  // 0x00720EC0 slot 6
    virtual void Detach(AbstractClass *target, bool all = true);        // 0x00720FC0 slot 10
    virtual int Kind_Of() const;                                        // 0x00721080 slot 11
    virtual int Size_Of() const;                                        // 0x00721070 slot 12
    virtual void Compute_CRC(WWCRCEngine &crc) const;                   // 0x00720BD0 slot 13
    virtual bool Read_INI(CCINIClass &ini);                             // 0x007204E0 slot 25

    static WarheadTypeClass *__fastcall From_Name(char const *name);    // 0x00721020 (0 if none)
    static WarheadTypeClass *__fastcall Find_Or_Make(char const *name); // 0x00720F30

    double Deform;                          // +0x098
    double Verses[11];                      // +0x0A0
    double ProneDamage;                     // +0x0F8
    int DeformThreshhold;                   // +0x100
    TypeList<AnimTypeClass *> AnimList;     // +0x104
    int InfDeath;                           // +0x120
    float CellSpread;                       // +0x124
    float CellInset;                        // +0x128
    float PercentAtMax;                     // +0x12C
    bool CausesDelayKill;                   // +0x130
    int DelayKillFrames;                    // +0x134
    float DelayKillAtMax;                   // +0x138
    float CombatLightSize;                  // +0x13C
    ParticleSystemTypeClass *Particle;      // +0x140
    bool Wall;                              // +0x144
    bool WallAbsoluteDestroyer;             // +0x145
    bool Wood;                              // +0x146
    bool Tiberium;                          // +0x147
    bool unknown_148;                       // +0x148
    bool Sparky;                            // +0x149
    bool Sonic;                             // +0x14A
    bool Fire;                              // +0x14B
    bool Conventional;                      // +0x14C
    bool Rocker;                            // +0x14D
    bool Bright;                            // +0x14E
    bool CLDisableRed;                      // +0x14F
    bool CLDisableGreen;                    // +0x150
    bool CLDisableBlue;                     // +0x151
    bool EMEffect;                          // +0x152
    bool MindControl;                       // +0x153
    bool IvanBomb;                          // +0x154
    bool ElectricAssault;                   // +0x155
    bool Parasite;                          // +0x156
    bool Temporal;                          // +0x157
    bool BombDisarm;                        // +0x158
    int Paralyzes;                          // +0x15C
    bool Culling;                           // +0x160
    bool MakesDisguise;                     // +0x161
    bool NukeMaker;                         // +0x162
    bool Radiation;                         // +0x163
    bool PsychicDamage;                     // +0x164
    bool Bullets;                           // +0x165
    bool Veinhole;                          // +0x166
    int ShakeXlo;                           // +0x168
    int ShakeXhi;                           // +0x16C
    int ShakeYlo;                           // +0x170
    int ShakeYhi;                           // +0x174
};

// Every warhead type (0x00839B00; defined in the unit at 0x0040F0A0).
extern DynamicVectorClass<WarheadTypeClass *> unknown_WarheadTypeClass_list_00839b00;

// The damage a warhead does to an armor type at a distance (0x0047E1C0;
// fastcall: damage, warhead, then armor and distance on the stack;
// ObjectClass::Damage and TechnoClass 0x006CA6C0).
int __fastcall Unknown_0047E1C0(int damage, WarheadTypeClass *warhead, int armour, int distance);

#endif
