// HoverLocomotionClass (Hover.cpp, 0x004FB6E0-0x004FEEFF; RTTI vtables
// 0x007A32B4 IPersistStream, 0x007A31EC ILocomotion at +4). Size 0x78.
// Layout from the constructor 0x004FB8D0 and Load 0x004FECC0 (names are
// hypotheses):
//   +0x18  CoordStruct destination, +0x24 CoordStruct head-to coordinate
//          (both start at the unit's zero 0x00A41080)
//   +0x30  FacingClass (rate 0; Link_To_Object sets twice the type's ROT)
//   +0x48, +0x50 double (0), +0x58 double (1.0), +0x60 double (0)
//   +0x68  bool drifting, +0x6C int drift (a random 20..30, either way),
//   +0x70  bool
#ifndef RA2_SHARED_HOVER_LOCOMOTION_HPP
#define RA2_SHARED_HOVER_LOCOMOTION_HPP

#include "shared/locomotion.hpp"

extern CoordStruct unknown_coord_a41080;            // 0x00A41080
extern "C" GUID const CLSID_HoverLocomotionClass;   // 0x007A1F80

class HoverLocomotionClass : public LocomotionClass {
public:
    HoverLocomotionClass();                                                     // 0x004FB8D0
    HoverLocomotionClass(NoInitClass const &noinit) : LocomotionClass(noinit) {}    // inline (Load)
    virtual ~HoverLocomotionClass();                                            // 0x004FB9B0

    virtual HRESULT __stdcall GetClassID(GUID *clsid);                          // 0x004FEC80
    virtual HRESULT __stdcall Load(IStream *stream);                            // 0x004FECC0
    virtual int Size() { return sizeof(HoverLocomotionClass); }                 // 0x004FEEC0 (inline)

    virtual HRESULT __stdcall Link_To_Object(void *object);                     // 0x004FB960
    virtual bool __stdcall Is_Moving();                                         // 0x004FC880
    virtual CoordStruct __stdcall Destination();                                // 0x004FC900
    virtual CoordStruct __stdcall Head_To_Coord();                              // 0x004FC960
    virtual Matrix3D * __stdcall Draw_Matrix(Matrix3D *matrix, int *key);                           // 0x004FBBF0
    virtual Matrix3D * __stdcall Shadow_Matrix(Matrix3D *matrix, int *key);                         // 0x004FBF50
    virtual bool __stdcall Process();                                           // 0x004FBFC0
    virtual void __stdcall Move_To(CoordStruct to);                             // 0x004FC9E0
    virtual void __stdcall Stop_Moving();                                       // 0x004FDF40
    virtual void __stdcall Do_Turn(UnknownFacingDir dir);                       // 0x004FDF90
    virtual bool __stdcall Power_Off();                                         // 0x004FE800
    virtual bool __stdcall Is_Powered();                                        // 0x004FE880
    virtual bool __stdcall Is_Ion_Sensitive();                                  // 0x004FE8B0
    virtual bool __stdcall Push(UnknownFacingDir dir);                          // 0x004FEA20
    virtual bool __stdcall Shove(UnknownFacingDir dir);                         // 0x004FEBD0
    virtual int __stdcall Layer();                                              // 0x004FED10
    virtual bool __stdcall Is_Moving_Now();                                     // 0x004FC8D0
    virtual void __stdcall Mark_All_Occupation_Bits(int mark);                  // 0x004FEDD0
    virtual bool __stdcall Is_Moving_Here(CoordStruct to);                      // 0x004FEE20

    // Starts a drift of 20..30 either way (Power_Off and Shove expand it;
    // name hypothesis).
    bool Reduce_Path_Length_004fdfd0();
    void Gravity_AI_004fb9d0();
    bool unknown_4fdfc0();                                                      // 0x004FDFC0 (moving; never called out of line)
    void Start_Drift();                                                         // 0x004FEC30
    void unknown_4fcbc0(bool arg);                                              // 0x004FCBC0 (Process's step; not yet recovered)
    void unknown_4fe0f0(bool arg);                                              // 0x004FE0F0 (Process's step; not yet recovered)
    void unknown_4fda80();                                                      // 0x004FDA80 (stops: no speed, clears the head-to coordinate and its mark; never called out of line)
    void unknown_4fed20();                                                      // 0x004FED20 (full speed; steps on unless already in the head-to cell; never called out of line)

    CoordStruct unknown_18;             // +0x18 destination
    CoordStruct unknown_24;             // +0x24 head-to coordinate
    FacingClass unknown_30;             // +0x30
    double unknown_48;                  // +0x48 (speed)
    double unknown_50;                  // +0x50
    double unknown_58;                  // +0x58 (1.0)
    double unknown_60;                  // +0x60
    bool unknown_68;                    // +0x68 drifting
    int unknown_6c;                     // +0x6C drift
    bool unknown_70;                    // +0x70
    int unknown_74;                     // +0x74
};

#endif
