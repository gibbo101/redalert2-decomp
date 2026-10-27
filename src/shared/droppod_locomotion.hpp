// DropPodLocomotionClass (DropPod.cpp, 0x004A5850-0x004A671F; RTTI vtables
// 0x007A0958 IPersistStream, 0x007A0890 ILocomotion at +4, 0x007A086C
// IPiggyback at +0x18). Size 0x30.
// Layout from the constructor 0x004A5A40 (names are hypotheses):
//   +0x18  IPiggyback vtable, +0x1C bool (Drawing_Code)
//   +0x20  CoordStruct destination (from the unit's zero 0x00852A20)
//   +0x2C  the carried locomotor (released by the destructor)
#ifndef RA2_SHARED_DROPPOD_LOCOMOTION_HPP
#define RA2_SHARED_DROPPOD_LOCOMOTION_HPP

#include "shared/locomotion.hpp"

extern CoordStruct unknown_coord_852a20;            // 0x00852A20
extern "C" GUID const CLSID_DropPodLocomotionClass; // 0x007A1FB0

class DropPodLocomotionClass : public LocomotionClass, public IPiggyback {
public:
    DropPodLocomotionClass();                                                   // 0x004A5A40
    DropPodLocomotionClass(NoInitClass const &noinit) : LocomotionClass(noinit) {} // inline (Load)
    virtual ~DropPodLocomotionClass();                                          // 0x004A5A90

    virtual HRESULT __stdcall QueryInterface(GUID const &iid, void **object);   // 0x004A63F0
    virtual unsigned long __stdcall AddRef();                                    // 0x004A6620
    virtual unsigned long __stdcall Release();                                   // 0x004A6630
    virtual HRESULT __stdcall GetClassID(GUID *clsid);                          // 0x004A6180
    virtual HRESULT __stdcall Load(IStream *stream);                            // 0x004A61C0
    virtual HRESULT __stdcall Save(IStream *stream, BOOL clear_dirty);          // 0x004A6240
    virtual int Size() { return sizeof(DropPodLocomotionClass); }               // 0x004A6660 (inline)

    virtual bool __stdcall Is_Moving();                                         // 0x004A5AC0
    virtual CoordStruct __stdcall Destination();                                // 0x004A5AD0
    virtual bool __stdcall Process();                                           // 0x004A5B00
    virtual void __stdcall Move_To(CoordStruct to);                             // 0x004A5FC0
    virtual void __stdcall Stop_Moving();                                       // 0x004A6320
    virtual int __stdcall Layer();                                              // 0x004A6450
    virtual int __stdcall Drawing_Code();                                       // 0x004A6570

    // IPiggyback
    virtual HRESULT __stdcall Begin_Piggyback(ILocomotion *pointer);            // 0x004A6330
    virtual HRESULT __stdcall End_Piggyback(ILocomotion **pointer);             // 0x004A6380
    virtual bool __stdcall Is_Ok_To_End();                                      // 0x004A63C0
    virtual HRESULT __stdcall Piggyback_CLSID(GUID *classid);                   // 0x004A6460
    virtual bool __stdcall Is_Piggybacking();                                   // 0x004A6640

    bool unknown_1c;                    // +0x1C
    CoordStruct unknown_20;             // +0x20 destination
    UnknownLocomotionPtr Piggybacker;   // +0x2C
};

#endif
