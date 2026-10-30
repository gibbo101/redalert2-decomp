// ParticleSystemClass: a group of particles (ParticleSys.cpp, members
// 0x0060AA70-0x0060D04D; RTTI vtables 0x007A7F8C primary (116 slots),
// 0x007A7F70 IRTTITypeInfo at +4, 0x007A7F68 INoticeSink, 0x007A7F60
// INoticeSource).
//
// Layout (from the constructors 0x0060AA70 and 0x0060AD30, the destructor
// 0x0060AE80, Load 0x0060CD30, Save 0x0060CEA0 and Compute_CRC 0x0060CF10;
// names are hypotheses):
//   +0x000  ObjectClass (0x98)
//   +0x098  ParticleSystemTypeClass *Class (swizzled; Class_Of returns it)
//   +0x09C  CoordStruct unknown_9c   offset from the owner's center
//   +0x0A8  DynamicVectorClass<ParticleClass *> Particles (saved by count)
//   +0x0C0  CoordStruct TargetCoord
//   +0x0CC  TechnoClass *Owner (swizzled; losing it sets unknown_e4)
//   +0x0D0  ObjectClass *unknown_d0 (swizzled)
//   +0x0D4  float unknown_d4 (the type's +0x26C), +0x0D8 int Lifetime,
//   +0x0DC  int unknown_dc, +0x0E0 int unknown_e0 (0x1D)
//   +0x0E4  bool unknown_e4 (slot 60 sets it: the system is ending),
//   +0x0E5  bool unknown_e5
//   size 0xE8
// Every system is in the list at 0x00A32280 and in the object list at
// 0x00AC0D60.
#ifndef RA2_SHARED_PARTICLE_SYSTEM_HPP
#define RA2_SHARED_PARTICLE_SYSTEM_HPP

#include "shared/particle.hpp"
#include "shared/rgb_class.hpp"
#include "shared/ini_class.hpp"

// The particle-system type; only the fields systems read are named (layout
// hypothesis; ParticleSysType.cpp is not recovered).
class ParticleSystemTypeClass : public ObjectTypeClass {
public:
    // Members of ParticleSysType.cpp (vtables 0x007A8480 primary,
    // 0x007A8464 IRTTITypeInfo, 0x007A845C INoticeSink, 0x007A8454
    // INoticeSource).
    ParticleSystemTypeClass(NoInitClass const &noinit);
    virtual ~ParticleSystemTypeClass();                                 // slot 8 (0x00620EC0 scalar deleting)
    virtual HRESULT __stdcall GetClassID(GUID *clsid);                  // 0x00620D00 slot 3
    virtual HRESULT __stdcall Load(IStream *stream);                    // 0x00620D40 slot 5
    virtual HRESULT __stdcall Save(IStream *stream, BOOL clear_dirty);  // 0x00620D90 slot 6
    virtual int Kind_Of() const;                                        // 0x00620E90 slot 11
    virtual int Size_Of() const;                                        // 0x00620E80 slot 12
    virtual void Compute_CRC(WWCRCEngine &crc) const;                   // 0x00620C60 slot 13
    virtual bool Read_INI(CCINIClass &ini);                             // 0x00620830 slot 25
    virtual bool unknown_slot32(Cell const &cell, HouseClass *house) const;   // 0x00620EA0
    virtual ObjectClass *unknown_slot35(HouseClass *house) const;       // 0x00620EB0

    ParticleSystemTypeClass(char const *ini_name);                      // 0x00620600
    static int __fastcall Index_Or_Make(char const *name);            // 0x00620B90
    static ParticleSystemTypeClass *__fastcall Find_Or_Make(char const *name);  // 0x00620DF0
    static char const *__fastcall Name_From(unsigned int index);        // 0x00620C40 ("<none>" when out of range)
    static int __fastcall Behaviour_From_Name(char const *name);        // 0x00620DB0 (-1: unknown)

    int HoldsWhat;                          // +0x264 index in the particle types (-1: none)
    bool Spawns;                            // +0x268
    int SpawnFrames;                        // +0x26C
    float Slowdown;                         // +0x270
    int ParticleCap;                        // +0x274
    int SpawnRadius;                        // +0x278
    float SpawnCutoff;                      // +0x27C
    float SpawnTranslucencyCutoff;          // +0x280
    int BehavesLike;                        // +0x284 (0..4: the AI routine)
    int Lifetime;                           // +0x288
    INIVector3 SpawnDirection;              // +0x28C
    double ParticlesPerCoord;               // +0x298
    double SpiralDeltaPerCoord;             // +0x2A0
    double SpiralRadius;                    // +0x2A8
    double PositionPerturbationCoefficient; // +0x2B0
    double MovementPerturbationCoefficient; // +0x2B8
    double VelocityPerturbationCoefficient; // +0x2C0
    double SpawnSparkPercentage;            // +0x2C8
    int SparkSpawnFrames;                   // +0x2D0
    int LightSize;                          // +0x2D4
    RGBClass LaserColor;                    // +0x2D8
    bool Laser;                             // +0x2DB
    bool OneFrameLight;                     // +0x2DC
};

// Every particle system type (0x00A35DD0).
extern DynamicVectorClass<ParticleSystemTypeClass *> ParticleSystemTypes;
// The BehavesLike= names (0x007EBFD8: Smoke, Gas, Fire, Spark, Railgun).
extern char const *unknown_behaviour_names_7ebfd8[5];

// The particle types (0x00A35E00; defined by the unit at 0x004D2BA0).
extern DynamicVectorClass<ParticleTypeClass *> ParticleTypes;

extern "C" GUID const CLSID_ParticleSystemClass;  // 0x007A1C30

class ParticleSystemClass : public ObjectClass {
public:
    // A new system of type at coord for owner, aimed at target or
    // target_coord (argument names hypotheses; AircraftClass slot 86).
    ParticleSystemClass(ParticleSystemTypeClass *type, CoordStruct const &coord, AbstractClass *target,
                        TechnoClass *owner, CoordStruct const &target_coord);   // 0x0060AA70
    ParticleSystemClass();                                              // 0x0060AD30
    ParticleSystemClass(NoInitClass const &noinit) : ObjectClass(noinit) {}   // inline (Load)
    virtual ~ParticleSystemClass();                                     // 0x0060AE80

    virtual HRESULT __stdcall GetClassID(GUID *clsid)                   // 0x0060CFB0 slot 3 (inline)
    {
        if (clsid == 0) {
            return E_POINTER;
        }
        *clsid = CLSID_ParticleSystemClass;
        return S_OK;
    }
    virtual HRESULT __stdcall Load(IStream *stream);                    // 0x0060CD30 slot 5
    virtual HRESULT __stdcall Save(IStream *stream, BOOL clear_dirty);  // 0x0060CEA0 slot 6
    virtual void Detach(AbstractClass *target, bool all = true);        // 0x0060CCA0 slot 10
    virtual int Kind_Of() const { return 0x18; }                        // 0x0060D010 slot 11 (inline)
    virtual int Size_Of() const { return sizeof(ParticleSystemClass); } // 0x0060D000 slot 12 (inline)
    virtual void Compute_CRC(WWCRCEngine &crc) const;                   // 0x0060CF10 slot 13
    virtual bool unknown_slot17() const;                                // 0x0060CC70 (ended and empty)
    virtual void AI();                                                  // 0x0060CB70 slot 23
    virtual int unknown_slot29() const;                                 // 0x0060CC90 (2)
    virtual ObjectTypeClass *Class_Of() const { return Class; }         // 0x0060D020 slot 33 (inline)
    virtual void unknown_slot60() { unknown_e4 = true; }                // 0x0060CFF0 (inline)
    virtual void unknown_slot67(int arg1, int arg2);                    // 0x0060B090

    ParticleClass *Spawn_Particle(CoordStruct const &coord, CoordStruct const &target);            // 0x0060B190
    ParticleClass *Spawn_Held_Particle(ParticleTypeClass *type, CoordStruct const &coord);       // 0x0060B240
    ParticleClass *Spawn_Particle(CoordStruct const &coord, CoordStruct const &target, int range); // 0x0060B2D0
    bool Remove_Particle(int index);                                    // 0x0060B3E0
    void Remove_All_Particles();                                        // 0x0060B460
    void unknown_func_60b4e0();                 // 0x0060B4E0 behaviour 1
    void unknown_func_60b670();                 // 0x0060B670 behaviour 3
    void unknown_func_60bb70();                 // 0x0060BB70 behaviour 0
    void unknown_func_60c050();                 // 0x0060C050 behaviour 4
    void unknown_func_60c7c0();                 // 0x0060C7C0 behaviour 2

    ParticleSystemTypeClass *Class;                 // +0x098
    CoordStruct unknown_9c;                         // +0x09C
    DynamicVectorClass<ParticleClass *> Particles;  // +0x0A8
    CoordStruct TargetCoord;                        // +0x0C0
    ObjectClass *Owner;                             // +0x0CC (a TechnoClass; hypothesis)
    AbstractClass *unknown_d0;                      // +0x0D0
    float unknown_d4;                               // +0x0D4
    int Lifetime;                                   // +0x0D8
    int unknown_dc;                                 // +0x0DC
    int unknown_e0;                                 // +0x0E0
    bool unknown_e4;                                // +0x0E4
    bool unknown_e5;                                // +0x0E5
};

// The list of particle systems (0x00A32280; defined by the unit at 0x004D2BA0).
extern DynamicVectorClass<ParticleSystemClass *> ParticleSystems;

// The gas cloud particle system (0x00A40D20; Westwood's GasSystem): made by
// Fill_In_Data, removed and deleted by Clear_Scenario.
extern ParticleSystemClass *unknown_gas_cloud_system_a40d20;

#endif
