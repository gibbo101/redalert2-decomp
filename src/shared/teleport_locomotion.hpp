// TeleportLocomotionClass (Teleport.cpp, 0x006DFAB0-0x006E1C7F; RTTI vtables
// 0x007AD270 IPersistStream, 0x007AD1A8 ILocomotion at +4, 0x007AD184
// IPiggyback at +0x18). Size 0x4C. No user destructor.
// Layout from the constructor 0x006DFCA0 and Load 0x006E1770 (names are
// hypotheses):
//   +0x1C  CoordStruct destination, +0x28 CoordStruct (both start at the
//          unit's zero 0x00AC0280)
//   +0x34  bool moving (Is_Moving compares it with 1), +0x35, +0x36 bools
//   +0x38  int, +0x3C frame timer (restarted by Load), +0x48 the carried
//          locomotor
#ifndef RA2_SHARED_TELEPORT_LOCOMOTION_HPP
#define RA2_SHARED_TELEPORT_LOCOMOTION_HPP

#include "shared/locomotion.hpp"

extern CoordStruct unknown_coord_ac0280;                // 0x00AC0280
extern "C" GUID const CLSID_TeleportLocomotionClass;    // 0x007A1FD0

class TeleportLocomotionClass : public LocomotionClass, public IPiggyback {
public:
    TeleportLocomotionClass();                                                  // 0x006DFCA0
    TeleportLocomotionClass(NoInitClass const &noinit) : LocomotionClass(noinit) {} // inline (Load)

    virtual HRESULT __stdcall QueryInterface(GUID const &iid, void **object);   // 0x006E1900
    virtual unsigned long __stdcall AddRef();                                    // 0x006E1BA0
    virtual unsigned long __stdcall Release();                                   // 0x006E1BB0
    virtual HRESULT __stdcall GetClassID(GUID *clsid);                          // 0x006E1730
    virtual HRESULT __stdcall Load(IStream *stream);                            // 0x006E1770
    virtual HRESULT __stdcall Save(IStream *stream, BOOL clear_dirty);          // 0x006E1810
    virtual int Size() { return sizeof(TeleportLocomotionClass); }              // 0x006E1BE0 (inline)
    // Teleport's own virtuals (IPersistStream-side slots 10 and 11; names unknown).
    virtual void __stdcall unknown_slot10();                                    // 0x006E16F0 (the warp timer ran out: clears the linked object's +0x205, counts +0x38 on)
    virtual bool unknown_slot11();                                              // 0x006DFD30 (not moving)

    virtual bool __stdcall Is_Moving();                                         // 0x006DFD20
    virtual CoordStruct __stdcall Destination();                                // 0x006DFD40
    virtual bool __stdcall Process();                                           // 0x006E0E10
    virtual void __stdcall Move_To(CoordStruct to);                             // 0x006DFDA0
    virtual void __stdcall Stop_Moving();                                       // 0x006DFED0
    virtual void __stdcall Do_Turn(UnknownFacingDir dir);                       // 0x006E0DE0
    virtual int __stdcall Layer();                                              // 0x006E18F0
    virtual void __stdcall Mark_All_Occupation_Bits(int mark);                  // 0x006E1B50

    // IPiggyback
    virtual HRESULT __stdcall Begin_Piggyback(ILocomotion *pointer);            // 0x006E1960
    virtual HRESULT __stdcall End_Piggyback(ILocomotion **pointer);             // 0x006E19B0
    virtual bool __stdcall Is_Ok_To_End();                                      // 0x006E19F0
    virtual HRESULT __stdcall Piggyback_CLSID(GUID *classid);                   // 0x006E1A40
    virtual bool __stdcall Is_Piggybacking();                                   // 0x006E1BC0

    void unknown_6e06b0(CoordStruct const &to);                                 // 0x006E06B0 (Move_To's step: picks the arrival coordinate, +0x28)

    CoordStruct unknown_1c;                     // +0x1C destination
    CoordStruct unknown_28;                     // +0x28
    bool unknown_34;                            // +0x34 moving
    bool unknown_35;                            // +0x35
    bool unknown_36;                            // +0x36
    int unknown_38;                             // +0x38
    CDTimerClass<FrameTimerClass> unknown_3c;   // +0x3C
    UnknownLocomotionPtr Piggybacker;           // +0x48
};

#endif
