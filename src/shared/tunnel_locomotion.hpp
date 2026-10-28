// TunnelLocomotionClass (Tunnel.cpp, 0x006EF9F0-0x006F13DF; RTTI vtables
// 0x007ADC74 IPersistStream, 0x007ADBAC ILocomotion at +4). Size 0x3C.
// Layout from the constructor 0x006EFBE0 and Load 0x006F12F0 (names are
// hypotheses):
//   +0x18  int state (0 idle; 4 underground)
//   +0x1C  CoordStruct destination (from the unit's zero 0x00AC0F30)
//   +0x28  frame timer and its total duration (16 bytes, restarted by Load),
//   +0x38  bool
#ifndef RA2_SHARED_TUNNEL_LOCOMOTION_HPP
#define RA2_SHARED_TUNNEL_LOCOMOTION_HPP

#include "shared/locomotion.hpp"
#include "shared/matrix3d.hpp"

extern CoordStruct unknown_coord_ac0f30;            // 0x00AC0F30

// A frame timer with the duration it was set to (16 bytes; the states assign a
// fresh one whole, so the padding word is copied too).
struct UnknownTunnelTimer {
    UnknownTunnelTimer() : Total(0) {}
    UnknownTunnelTimer(int duration) : Timer(duration), Total(duration) {}
    CDTimerClass<FrameTimerClass> Timer;    // +0x00
    int Total;                              // +0x0C
};
extern "C" GUID const CLSID_TunnelLocomotionClass;  // 0x007A1F90

// The product of two matrices (the slope matrix: shared/locomotion.hpp).
Matrix3D __fastcall operator*(Matrix3D const &left, Matrix3D const &right);   // 0x00591180

class TunnelLocomotionClass : public LocomotionClass {
public:
    TunnelLocomotionClass();                                                    // 0x006EFBE0
    TunnelLocomotionClass(NoInitClass const &noinit) :                          // inline (Load)
        LocomotionClass(noinit) {}

    virtual HRESULT __stdcall GetClassID(GUID *clsid);                          // 0x006F12B0
    virtual HRESULT __stdcall Load(IStream *stream);                            // 0x006F12F0
    virtual int Size() { return sizeof(TunnelLocomotionClass); }                // 0x006F13A0 (inline)

    virtual bool __stdcall Is_Moving();                                         // 0x006EFC30
    virtual CoordStruct __stdcall Destination();                                // 0x006EFC70
    virtual int __stdcall Can_Enter_Cell(Cell cell);                      // 0x006F1230
    virtual bool __stdcall Is_To_Have_Shadow();                                 // 0x006F1200
    virtual Matrix3D * __stdcall Draw_Matrix(Matrix3D *matrix, int *key);                           // 0x006F0CE0
    virtual int __stdcall Visual_Character(bool raw);                           // 0x006F0390
    virtual int __stdcall Z_Adjust();                                           // 0x006F0FF0
    virtual int __stdcall Z_Gradient();                                         // 0x006F11C0
    virtual bool __stdcall Process();                                           // 0x006F0000
    virtual void __stdcall Move_To(CoordStruct to);                             // 0x006EFCD0
    virtual void __stdcall Stop_Moving();                                       // 0x006EFDE0
    virtual void __stdcall Do_Turn(UnknownFacingDir dir);                       // 0x006F1280
    virtual int __stdcall Layer();                                              // 0x006F1340
    virtual bool __stdcall Is_Moving_Now();                                     // 0x006EFC40
    virtual int __stdcall State();                                              // 0x006F1360
    virtual bool __stdcall Is_Surfacing();                                      // 0x006F1380

    // The state handlers Process dispatches to (hypotheses; 0x006F0530, 0x006F0630,
    // 0x006F0690 and 0x006F0C50 are the out-of-line copies of the ones it expands).
    void unknown_6f03b0();                      // 0x006F03B0 (state 1)
    void unknown_6f0530();                      // 0x006F0530 (state 2)
    void unknown_6f0690();                      // 0x006F0690 (state 3)
    void unknown_6f0730();                      // 0x006F0730 (state 4)
    void unknown_6f0aa0();                      // 0x006F0AA0 (state 5)
    void unknown_6f0c50();                      // 0x006F0C50 (state 6)
    void unknown_6f0630();                      // 0x006F0630 (state 7)

    // How far the state's timer has run (1.0 with no duration; hypothesis).
    double Timer_Ratio()
    {
        if (unknown_28.Total == 0) {
            return 1.0;
        }
        return (double)(unknown_28.Total - unknown_28.Timer.Value()) / (double)unknown_28.Total;
    }

    int unknown_18;                             // +0x18 state
    CoordStruct unknown_1c;                     // +0x1C
    UnknownTunnelTimer unknown_28;              // +0x28
    bool unknown_38;                            // +0x38
};

#endif
