// WalkLocomotionClass (Walk.cpp, 0x0071DC10-0x0071FEEF; RTTI vtables
// 0x007AEBA0 IPersistStream, 0x007AEAD8 ILocomotion at +4, 0x007AEAB4
// IPiggyback at +0x18). Size 0x3C.
// Layout from the constructor 0x0071DE00 (names are hypotheses):
//   +0x1C  CoordStruct destination, +0x28 CoordStruct head-to coordinate
//          (both start at the unit's zero 0x00AF9060)
//   +0x34  bool moving, +0x35 bool processing, +0x36 bool really moving
//   +0x38  the carried locomotor
#ifndef RA2_SHARED_WALK_LOCOMOTION_HPP
#define RA2_SHARED_WALK_LOCOMOTION_HPP

#include "shared/locomotion.hpp"

extern CoordStruct unknown_coord_af9060;            // 0x00AF9060
extern "C" GUID const CLSID_WalkLocomotionClass;    // 0x007A1FA0

class WalkLocomotionClass : public LocomotionClass, public IPiggyback {
public:
    WalkLocomotionClass();                                                      // 0x0071DE00
    WalkLocomotionClass(NoInitClass const &noinit) : LocomotionClass(noinit) {} // inline (Load)
    virtual ~WalkLocomotionClass();                                             // 0x0071DE70

    virtual HRESULT __stdcall QueryInterface(GUID const &iid, void **object);   // 0x0071FAB0
    virtual unsigned long __stdcall AddRef();                                    // 0x0071FDE0
    virtual unsigned long __stdcall Release();                                   // 0x0071FDF0
    virtual HRESULT __stdcall GetClassID(GUID *clsid);                          // 0x0071F900
    virtual HRESULT __stdcall Load(IStream *stream);                            // 0x0071F940
    virtual HRESULT __stdcall Save(IStream *stream, BOOL clear_dirty);          // 0x0071F9C0
    virtual int Size() { return sizeof(WalkLocomotionClass); }                  // 0x0071FE30 (inline)

    virtual bool __stdcall Is_Moving();                                         // 0x0071DEA0
    virtual CoordStruct __stdcall Destination();                                // 0x0071DF10
    virtual CoordStruct __stdcall Head_To_Coord();                              // 0x0071DF70
    virtual bool __stdcall Process();                                           // 0x0071DFF0
    virtual void __stdcall Move_To(CoordStruct to);                             // 0x0071E020
    virtual void __stdcall Stop_Moving();                                       // 0x0071E110
    virtual void __stdcall Do_Turn(UnknownFacingDir dir);                       // 0x0071E170
    virtual int __stdcall Layer();                                              // 0x0071FAA0
    virtual void __stdcall Force_Immediate_Destination(CoordStruct coord);      // 0x0071E1A0
    virtual bool __stdcall Is_Moving_Now();                                     // 0x0071DEB0
    virtual void __stdcall Mark_All_Occupation_Bits(int mark);                  // 0x0071FCE0
    virtual bool __stdcall Is_Moving_Here(CoordStruct to);                      // 0x0071FD30
    virtual bool __stdcall Is_Really_Moving_Now();                              // 0x0071FDD0
    virtual void __stdcall Stop_Movement_Animation();                           // 0x0071FE20

    // IPiggyback
    virtual HRESULT __stdcall Begin_Piggyback(ILocomotion *pointer);            // 0x0071FB10
    virtual HRESULT __stdcall End_Piggyback(ILocomotion **pointer);             // 0x0071FB60
    virtual bool __stdcall Is_Ok_To_End();                                      // 0x0071FBA0
    virtual HRESULT __stdcall Piggyback_CLSID(GUID *classid);                   // 0x0071FBD0
    virtual bool __stdcall Is_Piggybacking();                                   // 0x0071FE00

    void unknown_71e220(bool arg);                                              // 0x0071E220 (Process's step)

    CoordStruct unknown_1c;             // +0x1C destination
    CoordStruct unknown_28;             // +0x28 head-to coordinate
    bool unknown_34;                    // +0x34 moving
    bool unknown_35;                    // +0x35 processing
    bool unknown_36;                    // +0x36 really moving
    UnknownLocomotionPtr Piggybacker;   // +0x38
};

#endif
