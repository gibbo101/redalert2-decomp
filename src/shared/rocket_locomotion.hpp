// RocketLocomotionClass (Rocket.cpp, 0x0063D8D0-0x0063ED6F; RTTI vtables
// 0x007A8FA4 IPersistStream, 0x007A8EDC ILocomotion at +4). Size 0x58.
// Layout from the constructor 0x0063DAC0 and Load 0x0063EBA0 (names are
// hypotheses):
//   +0x18  CoordStruct destination (none: 0x00AB6888)
//   +0x24, +0x34  frame timers (the second has no loading constructor)
//   +0x30, +0x40 (state; 3..5 is moving), +0x44..+0x54 ints
#ifndef RA2_SHARED_ROCKET_LOCOMOTION_HPP
#define RA2_SHARED_ROCKET_LOCOMOTION_HPP

#include "shared/locomotion.hpp"

struct RocketStruct;
extern CoordStruct unknown_coord_ab6888;            // 0x00AB6888
extern "C" GUID const CLSID_RocketLocomotionClass;  // 0x007A2010

class RocketLocomotionClass : public LocomotionClass {
public:
    RocketLocomotionClass();                                                    // 0x0063DAC0
    RocketLocomotionClass(NoInitClass const &noinit) :                          // inline (Load)
        LocomotionClass(noinit), unknown_24(noinit) {}
    virtual ~RocketLocomotionClass();                                           // 0x0063DB30

    virtual HRESULT __stdcall GetClassID(GUID *clsid);                          // 0x0063EB60
    virtual HRESULT __stdcall Load(IStream *stream);                            // 0x0063EBA0
    virtual int Size() { return sizeof(RocketLocomotionClass); }                // 0x0063ED30 (inline)

    virtual bool __stdcall Is_Moving();                                         // 0x0063DB50
    virtual CoordStruct __stdcall Destination();                                // 0x0063DBB0
    virtual Matrix3D * __stdcall Draw_Matrix(Matrix3D *matrix, int *key);                           // 0x0063EC00
    virtual bool __stdcall Process();                                           // 0x0063DE90
    virtual void __stdcall Move_To(CoordStruct to);                             // 0x0063EA80
    virtual void __stdcall Stop_Moving();                                       // 0x0063EB50
    virtual int __stdcall Layer();                                              // 0x0063EBF0
    virtual bool __stdcall Is_Moving_Now();                                     // 0x0063DB90

    CoordStruct unknown_63dbe0(int distance);                                    // 0x0063DBE0 (the point distance ahead along the facing and the pitch)
    bool unknown_63dcf0(RocketStruct const *rocket);                             // 0x0063DCF0 (the rocket's nose is down at the destination's height (or the bridge deck above it): explodes)
    double unknown_63de10();
    void unknown_63e7d0();                                                       // 0x0063E7D0 (detonates)                                                    // 0x0063DE10 (the pitch toward the destination: atan of the height over the ground distance)

    CoordStruct unknown_18;                     // +0x18
    UnknownSlopeTimer unknown_24;               // +0x24 (a frame timer and, +0x30, the duration it was set to; Move_To assigns a fresh one)
    CDTimerClass<FrameTimerClass> unknown_34;   // +0x34
    int unknown_40;                             // +0x40 (state)
    int unknown_44;                             // +0x44
    double unknown_48;                          // +0x48
    float unknown_50;                           // +0x50 (the pitch; Draw_Matrix tilts by it)
    int unknown_54;                             // +0x54
};

#endif
