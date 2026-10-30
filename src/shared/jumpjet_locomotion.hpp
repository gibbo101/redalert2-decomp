// JumpjetLocomotionClass (Jumpjet.cpp, 0x0052EF70-0x0053135F; RTTI vtables
// 0x007A536C IPersistStream, 0x007A52A4 ILocomotion at +4). Size 0x90.
// Layout from the constructor 0x0052F160 (names are hypotheses):
//   +0x18..+0x3B  not constructed (the type's jumpjet values, set by Link_To_Object)
//   +0x3C  CoordStruct (from 0x00A6E3E0), +0x48 bool (Is_Moving), +0x4C int
//   +0x50  FacingClass (rate: rules +0x368; desired and current 0x4000)
//   +0x68..+0x84 ints, +0x88 bool
#ifndef RA2_SHARED_JUMPJET_LOCOMOTION_HPP
#define RA2_SHARED_JUMPJET_LOCOMOTION_HPP

#include "shared/locomotion.hpp"

extern CoordStruct unknown_coord_a6e3e0;            // 0x00A6E3E0
extern "C" GUID const CLSID_JumpjetLocomotionClass; // 0x007A2000

class JumpjetLocomotionClass : public LocomotionClass {
public:
    JumpjetLocomotionClass();                                                   // 0x0052F160
    JumpjetLocomotionClass(NoInitClass const &noinit) :                         // inline (Load)
        LocomotionClass(noinit), unknown_50(noinit) {}
    virtual ~JumpjetLocomotionClass();                                          // 0x0052F210

    virtual HRESULT __stdcall GetClassID(GUID *clsid);                          // 0x0052FBA0
    virtual HRESULT __stdcall Load(IStream *stream);                            // 0x0052FBE0
    virtual int Size() { return sizeof(JumpjetLocomotionClass); }               // 0x00531320 (inline)

    virtual HRESULT __stdcall Link_To_Object(void *object);                     // 0x0052F230
    virtual bool __stdcall Is_Moving();                                         // 0x0052F350
    virtual CoordStruct __stdcall Destination();                                // 0x0052F360
    virtual CoordStruct __stdcall Head_To_Coord();                              // 0x005312D0
    virtual bool __stdcall Process();                                           // 0x0052F3C0
    virtual void __stdcall Move_To(CoordStruct to);                             // 0x0052F600
    virtual void __stdcall Stop_Moving();                                       // 0x0052F960
    virtual void __stdcall Do_Turn(UnknownFacingDir dir);                       // 0x0052FB70
    virtual int __stdcall Layer();                                              // 0x0052FC10
    virtual bool __stdcall Is_Moving_Now();                                     // 0x00530AE0
    virtual void __stdcall Mark_All_Occupation_Bits(int mark);                  // 0x00531250

    void unknown_52fca0();              // 0x0052FCA0 (Process: a moving jumpjet takes off: full height ratio, the object facing taken, speeds cleared, target height; unless the house holds the locomotors, state 1)
    int unknown_531140();               // 0x00531140 (the ground height to hold: under the object, or with speed the higher of it and one cell ahead, else their mean; bridges add the bridge height)
    void unknown_52fd50();              // 0x0052FD50 (Process state 1, ascending: climbs to the target height, then claims the cell (2) or cruises (3))
    void unknown_52fff0();              // 0x0052FFF0 (Process state 2, hovering: over the target the state becomes 2 or 4, else turns toward it, releases the cell claims, state 3)
    void unknown_530180();              // 0x00530180 (Process state 3)
    void unknown_530550();              // 0x00530550 (Process state 4)
    void unknown_530940();              // 0x00530940 (Process state 5, crashing: sinks and spins; on the ground state 6 and notice 0x117C)
    void unknown_530ad0();              // 0x00530AD0 (Process state 6: an empty routine; Process expands it, the copy is unreferenced)
    void unknown_530b00();              // 0x00530B00 (Process: the movement step)
    CoordStruct unknown_5310a0(CoordStruct const &coord);    // 0x005310A0 (the free spot near a coordinate (0x0049CB70) at ground height, bridges added; Move_To expands it, the copy is unreferenced)

    // The linked type's [Jumpjet*] values (Link_To_Object copies them; the
    // height is at least twice the unit's geometry constant).
    int TurnRate;                       // +0x18 (JumpjetTurnRate)
    int Speed;                          // +0x1C (JumpjetSpeed)
    float Climb;                        // +0x20 (JumpjetClimb)
    float Crash;                        // +0x24 (JumpjetCrash)
    int Height;                         // +0x28 (JumpjetHeight)
    float Accel;                        // +0x2C (JumpjetAccel)
    float Wobbles;                      // +0x30 (JumpjetWobbles)
    int Deviation;                      // +0x34 (JumpjetDeviation)
    bool NoWobbles;                     // +0x38 (JumpjetNoWobbles)
    CoordStruct unknown_3c;             // +0x3C
    bool unknown_48;                    // +0x48
    int unknown_4c;                     // +0x4C
    FacingClass unknown_50;             // +0x50
    double unknown_68;                  // +0x68
    double unknown_70;                  // +0x70
    int unknown_78;                     // +0x78
    int unknown_7c;                     // +0x7C
    double unknown_80;                  // +0x80
    bool unknown_88;                    // +0x88
    int unknown_8c;                     // +0x8C
};

#endif
