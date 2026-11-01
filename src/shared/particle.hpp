// ParticleClass: one particle (Particle.cpp, members 0x00608440-0x0060A87E;
// RTTI vtables 0x007A7D5C primary (117 slots), 0x007A7D40 IRTTITypeInfo at
// +4, 0x007A7D38 INoticeSink, 0x007A7D30 INoticeSource).
//
// Layout (from the constructors 0x00608440 and 0x00608980, the destructor
// 0x00608B20 and Load 0x0060A5E0; names are hypotheses):
//   +0x000  ObjectClass (0x98)
//   +0x098  ParticleTypeClass *Class (swizzled; Class_Of returns it)
//   +0x09C  RGBClass Color (from the type's colour, or a random blend)
//   +0x0A0  ParticleColorState (16 bytes: index, unknown word, double fraction)
//   +0x0B0  CoordStruct step per move
//   +0x0BC  Vector3 GasVelocity (0,0,-1)
//   +0x0C8  CoordStruct UnusedCoord1 (0,0,0)
//   +0x0D4  float Velocity (the type's +0x2CC; hypothesis)
//   +0x0D8  CoordStruct unknown_d8   the constructor's second coordinate
//   +0x0E4  CoordStruct unknown_e4   the first coordinate
//   +0x0F0  CoordStruct unknown_f0   zero
//   +0x0FC  Vector3 unknown_fc       (second - first), normalized
//   +0x108  Vector3 unknown_108      the first coordinate as floats
//   +0x114  ParticleSystemClass *System (swizzled)
//   +0x118  short Lifetime (counts down to the +0x121 flag), +0x11A short
//   +0x11C..+0x121  char/bool fields (+0x120 set by Save, +0x121 "done")
//   size 0x128
// Every particle is in the list at 0x00A35E28.
#ifndef RA2_SHARED_PARTICLE_HPP
#define RA2_SHARED_PARTICLE_HPP

#include "shared/random.hpp"   // before the unit's statics: Random3Class's static members take compiler counter values
#include "shared/object_type.hpp"
#include "shared/rgb_class.hpp"
#include "shared/type_list.hpp"
#include "shared/vector3.hpp"
#include "shared/tactical.hpp"

class ParticleClass;
class ParticleSystemClass;

// Vector3: shared/vector3.hpp.

// The particle type; only the fields particles read are named (layout
// hypothesis; ParticleType.cpp is not recovered).
class WarheadTypeClass;

// The particle type (ParticleType.cpp; RTTI vtables 0x007A8560 primary,
// 0x007A8544 IRTTITypeInfo, 0x007A853C INoticeSink, 0x007A8534
// INoticeSource; size 0x2E8). Members are named by the INI keys Read_INI
// (0x00621490) reads into them.
class ParticleTypeClass : public ObjectTypeClass {
public:
    ParticleTypeClass(char const *ini_name);                            // 0x00621120
    ParticleTypeClass(NoInitClass const &noinit);
    virtual ~ParticleTypeClass();                                       // slot 8 (0x00621E80 scalar deleting)
    virtual HRESULT __stdcall GetClassID(GUID *clsid);                  // 0x00621B50 slot 3
    virtual HRESULT __stdcall Load(IStream *stream);                    // 0x00621B90 slot 5
    virtual HRESULT __stdcall Save(IStream *stream, BOOL clear_dirty);  // 0x00621CD0 slot 6
    virtual void Detach(AbstractClass *target, bool all = true);        // 0x00621DE0 slot 10
    virtual int Kind_Of() const;                                        // 0x00621E50 slot 11
    virtual int Size_Of() const;                                        // 0x00621E40 slot 12
    virtual void Compute_CRC(WWCRCEngine &crc) const;                   // 0x00621A10 slot 13
    virtual bool Read_INI(CCINIClass &ini);                             // 0x00621490 slot 25
    virtual bool unknown_slot32(Cell const &cell, HouseClass *house) const;   // 0x00621E60
    virtual ObjectClass *unknown_slot35(HouseClass *house) const;       // 0x00621E70

    CoordStruct NextParticleOffset;         // +0x264
    int XVelocity;                          // +0x270
    int YVelocity;                          // +0x274
    int MinZVelocity;                       // +0x278
    int ZVelocityRange;                     // +0x27C
    double ColorSpeed;                      // +0x280
    TypeList<RGBClass> ColorList;           // +0x288
    RGBClass StartColor1;                   // +0x2A4
    RGBClass StartColor2;                   // +0x2A7
    int MaxDC;                              // +0x2AC
    int MaxEC;                              // +0x2B0
    WarheadTypeClass *Warhead;              // +0x2B4
    int Damage;                             // +0x2B8
    int StartFrame;                         // +0x2BC
    int NumLoopFrames;                      // +0x2C0
    int Translucency;                       // +0x2C4
    int WindEffect;                         // +0x2C8
    float Velocity;                         // +0x2CC
    float Deacc;                            // +0x2D0
    int Radius;                             // +0x2D4
    bool DeleteOnStateLimit;                // +0x2D8
    char EndStateAI;                        // +0x2D9
    char StartStateAI;                      // +0x2DA
    char StateAIAdvance;                    // +0x2DB
    char FinalDamageState;                  // +0x2DC
    unsigned char Translucent25State;       // +0x2DD
    unsigned char Translucent50State;       // +0x2DE
    bool Normalized;                        // +0x2DF
    int NextParticle;                       // +0x2E0 index in the particle types (-1: none)
    int BehavesLike;                        // +0x2E4 (0..4: the behaviour routine)

    // The index of the named particle type, made when missing; -1 for
    // "<none>" (0x00621960).
    static int __fastcall Index_Or_Make(char const *name);
    static ParticleTypeClass *__fastcall Find_Or_Make(char const *name);   // 0x00621D50
    static char const *__fastcall Name_From(unsigned int index);        // 0x006219F0 (0 when out of range)
    static int __fastcall Behaviour_From_Name(char const *name);        // 0x00621E00 (-1: unknown)
};
// The BehavesLike= names of particles (0x007EC1B4: five entries).
extern char const *unknown_particle_behaviour_names_7ec1b4[5];

// Particle colour state at +0xA0. Purpose-name hypothesis; original type name
// is unknown. +0x00 indexes ColorList; +0x08 is a double interpolation fraction
// (original fld/fadd/fst qword accesses at60932c/609332). +0x04 is not initialized.
struct ParticleColorState {
    ParticleColorState() : ColorIndex(0), Fraction(0) {}
    ParticleColorState(NoInitClass const &noinit) {}
    int ColorIndex;
    int unknown_04;
    double Fraction;                       // +0x08, original qword accesses60932c/609332
};

extern "C" GUID const CLSID_ParticleClass;    // 0x007A1C70

// A function-local static cell returned by slot 64 (as ObjectClass's).
class ParticleClass : public ObjectClass {
public:
    ParticleClass(ParticleTypeClass *type, CoordStruct const &coord, CoordStruct const &target, ParticleSystemClass *system);   // 0x00608440
    ParticleClass();                                                    // 0x00608980
    ParticleClass(NoInitClass const &noinit) : ObjectClass(noinit), Color(noinit), ColorState(noinit) {}   // inline (Load)
    virtual ~ParticleClass();                                           // 0x00608B20

    virtual HRESULT __stdcall GetClassID(GUID *clsid)                   // 0x0060A770 slot 3 (inline)
    {
        if (clsid == 0) {
            return E_POINTER;
        }
        *clsid = CLSID_ParticleClass;
        return S_OK;
    }
    virtual HRESULT __stdcall Load(IStream *stream);                    // 0x0060A5E0 slot 5
    virtual HRESULT __stdcall Save(IStream *stream, BOOL clear_dirty);  // 0x0060A650 slot 6
    virtual int Kind_Of() const { return 0x16; }                        // 0x0060A7C0 slot 11 (inline)
    virtual int Size_Of() const { return sizeof(ParticleClass); }       // 0x0060A7B0 slot 12 (inline)
    virtual int unknown_slot29() const;                                 // 0x0060A5B0 (3)
    virtual ObjectTypeClass *Class_Of() const { return Class; }         // 0x0060A7D0 slot 33 (inline)
    virtual Cell const *unknown_slot64(int arg1);                 // 0x0060A550
    virtual void unknown_slot67(int arg1, int arg2);                    // 0x00609D10
    virtual bool unknown_slot71(int arg1);                              // 0x0060A530
    virtual int unknown_slot116();                                      // 0x0060A670 (new)

    void unknown_func_608bb0();                 // 0x00608BB0 behaviour 0
    void unknown_func_609200();                 // 0x00609200 behaviour 4
    void unknown_func_6093a0();                 // 0x006093A0 behaviour 1
    void unknown_func_609540();                 // 0x00609540 behaviour 3
    void unknown_func_609970();                 // 0x00609970 behaviour 2
    void unknown_func_609c90();                 // 0x00609C90 (behaviour by type, then lifetime)
    void unknown_func_60a0e0();                 // 0x0060A0E0 movement of behaviour 0
    void unknown_func_60a230();                 // 0x0060A230 movement of behaviour 1
    void unknown_func_60a350();                 // 0x0060A350 movement of behaviour 2 (inlined)
    void unknown_func_60a420();                 // 0x0060A420 movement by behaviour

    ParticleTypeClass *Class;               // +0x098
    RGBClass Color;                         // +0x09C
    ParticleColorState ColorState;           // +0x0A0
    CoordStruct unknown_b0;                 // +0x0B0 step per move (behaviours 0 and 1)
    Vector3 GasVelocity;                   // +0x0BC velocity, fields from608440/608980
    CoordStruct UnusedCoord1;               // +0x0C8 coordinate, reference-supported name
    float Velocity;                         // +0x0D4
    CoordStruct unknown_d8;                 // +0x0D8
    CoordStruct unknown_e4;                 // +0x0E4
    CoordStruct unknown_f0;                 // +0x0F0
    Vector3 unknown_fc;                     // +0x0FC
    Vector3 unknown_108;                    // +0x108
    ParticleSystemClass *System;            // +0x114
    unsigned short Lifetime;                // +0x118
    short unknown_11a;                      // +0x11A
    char unknown_11c;                       // +0x11C
    char unknown_11d;                       // +0x11D
    char unknown_11e;                       // +0x11E
    char unknown_11f;                       // +0x11F
    bool unknown_120;                       // +0x120
    bool unknown_121;                       // +0x121
    short unknown_122;                      // +0x122
    int unknown_124;                        // +0x124
};

// Per-direction X ([0]) and Y ([1]) steps (8 directions) of the wind,
// indexed by the rules value at +0x6D4: for behaviour 0 (0x007EB7E4) and
// for behaviour 1 (0x007EB824, scaled by the type's +0x2C8).
extern int unknown_wind_7eb7e4[2][8];
extern int unknown_wind_7eb824[2][8];

// The direction (0..7) from one screen point to another (0x00721DB0,
// __fastcall; hypothesis).
int __fastcall Unknown_00721DB0(Point2D const &from, Point2D const &to);

// The list of particles (0x00A35E28; defined by the unit at 0x004D2BA0).
extern DynamicVectorClass<ParticleClass *> unknown_ParticleClass_list_00a35e28;

#endif
