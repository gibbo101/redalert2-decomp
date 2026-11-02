// ILocomotion: the COM interface of the locomotors (moved out of
// shared/locomotion.hpp so FootClass can hold and call its locomotor
// without the LocomotionClass header). Method names follow the publicly
// documented RA2/YR interface (hypotheses; the slot order, ret sizes and
// bodies agree).
#ifndef RA2_SHARED_ILOCOMOTION_HPP
#define RA2_SHARED_ILOCOMOTION_HPP

#include "shared/techno.hpp"
#include "shared/rect.hpp"

class Matrix3D;
#ifdef RA2_LOCOMOTION_COM_VALUE_TYPES
struct COMMatrix3DStruct;
#endif

extern "C" GUID const IID_ILocomotion;          // 0x007A5890


struct __declspec(novtable) ILocomotion : public IUnknown {
    virtual HRESULT __stdcall Link_To_Object(void *object) = 0;                  // 3
    virtual bool __stdcall Is_Moving() = 0;                                      // 4
    virtual CoordStruct __stdcall Destination() = 0;                             // 5
    
#ifdef RA2_LOCOMOTION_COM_VALUE_TYPES
    virtual COMCoordStruct __stdcall Head_To_Coord() = 0;
#else
    virtual CoordStruct __stdcall Head_To_Coord() = 0;
#endif                           // 6
    virtual int __stdcall Can_Enter_Cell(Cell cell) = 0;                   // 7
    virtual bool __stdcall Is_To_Have_Shadow() = 0;                              // 8
    
#ifdef RA2_LOCOMOTION_COM_VALUE_TYPES
    virtual COMMatrix3DStruct __stdcall Draw_Matrix(int *key) = 0;
#else
    virtual Matrix3D * __stdcall Draw_Matrix(Matrix3D *matrix, int *key) = 0;
#endif                        // 9
    
#ifdef RA2_LOCOMOTION_COM_VALUE_TYPES
    virtual COMMatrix3DStruct __stdcall Shadow_Matrix(int *key) = 0;
#else
    virtual Matrix3D * __stdcall Shadow_Matrix(Matrix3D *matrix, int *key) = 0;
#endif                      // 10
    
#ifdef RA2_LOCOMOTION_COM_VALUE_TYPES
    virtual COMPoint2DStruct __stdcall Draw_Point() = 0;
#else
    virtual Point2D __stdcall Draw_Point() = 0;
#endif                                  // 11
    
#ifdef RA2_LOCOMOTION_COM_VALUE_TYPES
    virtual COMPoint2DStruct __stdcall Shadow_Point() = 0;
#else
    virtual Point2D __stdcall Shadow_Point() = 0;
#endif                                // 12
    virtual int __stdcall Visual_Character(bool raw) = 0;                        // 13
    virtual int __stdcall Z_Adjust() = 0;                                        // 14
    virtual int __stdcall Z_Gradient() = 0;                                      // 15
    virtual bool __stdcall Process() = 0;                                        // 16
    virtual void __stdcall Move_To(CoordStruct to) = 0;                          // 17
    virtual void __stdcall Stop_Moving() = 0;                                    // 18
    virtual void __stdcall Do_Turn(UnknownFacingDir dir) = 0;                    // 19
    virtual void __stdcall Unlimbo() = 0;                                        // 20
    virtual void __stdcall Tilt_Pitch_AI() = 0;                                  // 21
    virtual bool __stdcall Power_On() = 0;                                       // 22
    virtual bool __stdcall Power_Off() = 0;                                      // 23
    virtual bool __stdcall Is_Powered() = 0;                                     // 24
    virtual bool __stdcall Is_Ion_Sensitive() = 0;                               // 25
    virtual bool __stdcall Push(UnknownFacingDir dir) = 0;                       // 26
    virtual bool __stdcall Shove(UnknownFacingDir dir) = 0;                      // 27
    virtual void __stdcall Force_Track(int track, CoordStruct coord) = 0;        // 28
    virtual int __stdcall Layer() = 0;                                           // 29
    virtual void __stdcall Force_Immediate_Destination(CoordStruct coord) = 0;   // 30
    virtual void __stdcall Force_New_Slope(int ramp) = 0;                        // 31
    virtual bool __stdcall Is_Moving_Now() = 0;                                  // 32
    virtual int __stdcall Apparent_Speed() = 0;                                  // 33
    virtual int __stdcall Drawing_Code() = 0;                                    // 34
    virtual int __stdcall State() = 0;                                           // 35
    virtual int __stdcall Get_Status() = 0;                                      // 36
    virtual void __stdcall Acquire_Hunter_Seeker_Target() = 0;                   // 37
    virtual bool __stdcall Is_Surfacing() = 0;                                   // 38
    virtual void __stdcall Mark_All_Occupation_Bits(int mark) = 0;               // 39
    virtual bool __stdcall Is_Moving_Here(CoordStruct to) = 0;                   // 40
    virtual bool __stdcall Will_Jump_Tracks() = 0;                               // 41
    virtual bool __stdcall Is_Really_Moving_Now() = 0;                           // 42
    virtual void __stdcall Stop_Movement_Animation() = 0;                        // 43
    virtual void __stdcall Lock() = 0;                                           // 44
    virtual void __stdcall Unlock() = 0;                                         // 45
    virtual int __stdcall Get_Track_Number() = 0;                                // 46
    virtual int __stdcall Get_Track_Index() = 0;                                 // 47
    virtual int __stdcall Get_Speed_Accum() = 0;                                 // 48
};

#endif
