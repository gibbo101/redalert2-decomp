// MechLocomotionClass (Mech.cpp, 0x005914E0-0x0059333F; RTTI vtables
// 0x007A6174 IPersistStream, 0x007A60AC ILocomotion at +4). Size 0x34.
// Layout from the constructor 0x005916D0 (names are hypotheses):
//   +0x18  CoordStruct destination, +0x24 CoordStruct head-to coordinate
//          (both start at the unit's zero coordinate 0x00A70B18)
//   +0x30  bool moving
#ifndef RA2_SHARED_MECH_LOCOMOTION_HPP
#define RA2_SHARED_MECH_LOCOMOTION_HPP

#include "shared/locomotion.hpp"

extern CoordStruct unknown_coord_a70b18;            // 0x00A70B18
extern "C" GUID const CLSID_MechLocomotionClass;    // 0x007A1FE0

class MechLocomotionClass : public LocomotionClass {
public:
    MechLocomotionClass();                                                      // 0x005916D0
    MechLocomotionClass(NoInitClass const &noinit) : LocomotionClass(noinit) {} // inline (Load)
    virtual ~MechLocomotionClass();                                             // 0x00591730

    virtual HRESULT __stdcall GetClassID(GUID *clsid);                          // 0x00593120
    virtual HRESULT __stdcall Load(IStream *stream);                            // 0x00593160
    virtual int Size() { return sizeof(MechLocomotionClass); }                  // 0x00593300 (inline)

    virtual bool __stdcall Is_Moving();                                         // 0x00591750
    virtual CoordStruct __stdcall Destination();                                // 0x00591760
    virtual CoordStruct __stdcall Head_To_Coord();                              // 0x005917C0
    virtual bool __stdcall Process();                                           // 0x00591840
    virtual void __stdcall Move_To(CoordStruct to);                             // 0x00591860
    virtual void __stdcall Stop_Moving();                                       // 0x00591900
    virtual void __stdcall Do_Turn(UnknownFacingDir dir);                       // 0x00591950
    virtual int __stdcall Layer();                                              // 0x00593190
    virtual void __stdcall Force_Immediate_Destination(CoordStruct coord);      // 0x00591980
    virtual bool __stdcall Is_Moving_Now();                                     // 0x005931A0
    virtual void __stdcall Mark_All_Occupation_Bits(int mark);                  // 0x00593210
    virtual bool __stdcall Is_Moving_Here(CoordStruct to);                      // 0x00593260

    void unknown_5919a0(bool arg);                                              // 0x005919A0 (Process's step)
    bool unknown_592f70(CoordStruct const &coord);                              // 0x00592F70 (heads for a coordinate: marks the cell, true when it can be entered)

    CoordStruct unknown_18;             // +0x18 destination
    CoordStruct unknown_24;             // +0x24 head-to coordinate
    bool unknown_30;                    // +0x30 moving
};

#endif
