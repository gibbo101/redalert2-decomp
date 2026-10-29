// BuildingLightClass: a search light swept by a building or unit
// (BuildingLight.cpp, unit 0x00432DD0-0x0043491F; RTTI vtables 0x0079C7E0
// primary, 0x0079C7C4 IRTTITypeInfo at +4, 0x0079C7BC INoticeSink,
// 0x0079C7B4 INoticeSource).
//
// Layout (constructor 0x00432FC0, 0x00434370, Load 0x004340E0, Detach
// 0x00434190, Compute_CRC 0x004346D0; names are hypotheses):
//   +0x00  ObjectClass (0x98 bytes)
//   +0x98  double unknown_98          0 (cleared again by Set_Behavior)
//   +0xA0  CoordStruct unknown_a0     the default coordinate (0x0084EA28) at first
//   +0xAC  CoordStruct unknown_ac
//   +0xB8  double unknown_b8
//   +0xC0  bool unknown_c0
//   +0xC4  int Behavior               Set_Behavior's argument (3: follow the
//                                     nearest object of kind 15 or 1)
//   +0xC8  ObjectClass *Following
//   +0xCC  TechnoClass *Owner         the constructor's argument
//   size 0xD0 (Size_Of)
// Every light is added to BuildingLights (0x00866220).
#ifndef RA2_SHARED_BUILDING_LIGHT_HPP
#define RA2_SHARED_BUILDING_LIGHT_HPP

#include "shared/techno.hpp"

extern "C" GUID const CLSID_BuildingLightClass;    // 0x007A1CA0

// Radians per facing unit, negated (-2*pi/65536; 0x0079B620).
extern double const unknown_facing_radians_79b620;

// Sine and cosine of an angle in radians (shared/bullet.hpp declares the same).
double __cdecl unknown_sin_4ba480(double angle);    // 0x004BA480
double __cdecl unknown_cos_4ba4d0(double angle);    // 0x004BA4D0

class BuildingLightClass;
extern DynamicVectorClass<BuildingLightClass *> BuildingLights;    // 0x00866220

#include "shared/unknown_list_832470.hpp"

class BuildingLightClass : public ObjectClass {
public:
    BuildingLightClass(TechnoClass *owner);                         // 0x00432FC0
    BuildingLightClass(NoInitClass const &noinit) : ObjectClass(noinit) {}   // (inlined into Load)
    virtual ~BuildingLightClass();                                  // 0x004332F0 (also inlined into 0x00434850)

    void unknown_func_4341d0(TechnoClass *object);                  // 0x004341D0
    void Set_Behavior(int behavior);                                // 0x00434370 (name hypothesis)
    int unknown_func_434530() const;                                // 0x00434530
    int unknown_func_434610() const;                                // 0x00434610

    virtual HRESULT __stdcall GetClassID(GUID *clsid);              // 0x004340A0 slot 3
    virtual HRESULT __stdcall Load(IStream *stream);                // 0x004340E0 slot 5
    virtual HRESULT __stdcall Save(IStream *stream, BOOL clear_dirty);  // 0x00434150 slot 6
    virtual void Detach(AbstractClass *target, bool all = true);    // 0x00434190 slot 10
    virtual int Kind_Of() const { return 0x13; }                    // 0x00434840 slot 11 (inline)
    virtual int Size_Of() const { return sizeof(BuildingLightClass); }  // 0x00434090 slot 12 (inline)
    virtual void Compute_CRC(WWCRCEngine &crc) const;               // 0x004346D0 slot 13
    virtual void AI();                                              // 0x00433970 slot 23
    virtual int unknown_slot29() const { return 3; }                // 0x00434180 (inline)
    virtual ObjectTypeClass *Class_Of() const { return 0; }         // 0x00434170 slot 33 (inline)
    // Slots 52 and 53 return bool (needs the bool declarations proposed for
    // object.hpp, radio.hpp and techno.hpp).
    virtual bool unknown_slot52();                                  // 0x004347C0
    virtual bool unknown_slot53(CoordStruct const *coord, int dir);              // 0x004347E0
    virtual void unknown_slot67(int arg1, int arg2);                // 0x00433380

    double unknown_98;              // +0x98
    CoordStruct unknown_a0;         // +0xA0
    CoordStruct unknown_ac;         // +0xAC
    double unknown_b8;              // +0xB8
    bool unknown_c0;                // +0xC0
    int Behavior;                   // +0xC4
    ObjectClass *Following;         // +0xC8
    TechnoClass *Owner;             // +0xCC
};

#endif
