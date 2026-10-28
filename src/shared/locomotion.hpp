// LocomotionClass: the base of the COM locomotors (Locomotion.cpp,
// 0x0053CDD0-0x0053D621; RTTI vtables 0x007A33B4 for IPersistStream and
// 0x007A32EC for ILocomotion at +4).
//
// Layout (constructor 0x0053CFC0, destructor 0x0053CFF0, Load 0x0053D3C0):
//   +0x00  IPersistStream vtable, +0x04 ILocomotion vtable
//   +0x08  FootClass *Owner, +0x0C FootClass *LinkedTo  (Link_To_Object
//          sets both; Load swizzles both)
//   +0x10  bool Powered (true), +0x11 bool Dirty (true; IsDirty, Save)
//   +0x14  long RefCount (AddRef/Release; kept across Load)
//   size 0x18
// ILocomotion method names follow the publicly documented RA2/YR
// interface (hypotheses; the slot order, ret sizes and bodies agree).
#ifndef RA2_SHARED_LOCOMOTION_HPP
#define RA2_SHARED_LOCOMOTION_HPP

#include "shared/unknown_globals.hpp"
#include "shared/foot.hpp"
#include "shared/ilocomotion.hpp"
#include "shared/rect.hpp"
#include "shared/com_ptr.hpp"
#include "shared/win32_api.hpp"
#include "shared/map_view.hpp"


class Matrix3D;

// The live COM object count (0x00A6EB14).
// A zero coordinate (0x00A6EA60; Destination's default).
extern CoordStruct unknown_coord_a6ea60;


// CoordStruct ==/!=: shared/coord.hpp.

// A map cell (only the flags the locomotors test).
struct UnknownLocoCell {
    char unknown_000[0x140];
    unsigned int Flags;                 // +0x140 (0x100: a bridge/high cell; hypothesis)
};
inline UnknownLocoCell *Loco_Cell(CoordStruct const &coord)
{
    return (UnknownLocoCell *)&Map[coord];
}
// The cell object at a cell (only the member the locomotors call).
struct UnknownLocoCellObject {
    bool unknown_47c200();              // 0x0047C200
};
inline UnknownLocoCellObject *Loco_Cell_At(Cell const &cell)
{
    return (UnknownLocoCellObject *)&Map[cell];
}
// TacticalClass::Unknown_006A29B0 (Screen/shared/tactical.hpp): pixels to height.
int __fastcall Unknown_006A29B0(int pixels);
// The slope tilt matrix for a cell ramp type (a copy of the table entry at
// 0x00AF8608 + 48 * ramp; LocomotionClass::Shadow_Matrix and the locomotors).
Matrix3D __fastcall Unknown_00718D60(int ramp);                 // 0x00718D60
// Where an object is, as a value (an inline accessor: each use copies the
// whole coordinate; Drive and Ship Is_Moving compare its X and Y).
inline CoordStruct Object_Coord(ObjectClass const *object)
{
    return object->Coord;
}
// ILocomotion: shared/ilocomotion.hpp.

#ifndef E_FAIL
#define E_FAIL ((HRESULT)0x80004005L)
#endif
extern "C" GUID const IID_IPiggyback;           // 0x007A2050

// The interface of locomotors that can carry another (piggybacking).
struct __declspec(novtable) IPiggyback : public IUnknown {
    virtual HRESULT __stdcall Begin_Piggyback(ILocomotion *pointer) = 0;
    virtual HRESULT __stdcall End_Piggyback(ILocomotion **pointer) = 0;
    virtual bool __stdcall Is_Ok_To_End() = 0;
    virtual HRESULT __stdcall Piggyback_CLSID(GUID *classid) = 0;
    virtual bool __stdcall Is_Piggybacking() = 0;
};

// A held ILocomotion with _com_ptr_t semantics (hypothesis: the original
// used the compiler's ILocomotionPtr, identified library code; this
// spells out only what the locomotors expand inline).
struct UnknownLocomotionPtr {
    UnknownLocomotionPtr() : Pointer(0) {}
    ~UnknownLocomotionPtr()
    {
        if (Pointer != 0) {
            Pointer->Release();
        }
    }
    operator ILocomotion *() const { return Pointer; }
    UnknownLocomotionPtr &operator=(ILocomotion *pointer)
    {
        if (Pointer != pointer) {
            ILocomotion *old = Pointer;
            Pointer = pointer;
            if (Pointer != 0) {
                Pointer->AddRef();
            }
            if (old != 0) {
                old->Release();
            }
        }
        return *this;
    }
    ILocomotion **operator&()
    {
        if (Pointer != 0) {
            Pointer->Release();
        }
        Pointer = 0;
        return &Pointer;
    }
    ILocomotion *Pointer;
};

WIN32_IMPORT HRESULT __stdcall OleLoadFromStream(IStream *stream, GUID const &iid, void **object);
WIN32_IMPORT HRESULT __stdcall OleSaveToStream(IPersistStream *object, IStream *stream);

// A frame timer with a fourth word (16 bytes; Drive/Ship Force_New_Slope assign a
// fresh one).
struct UnknownSlopeTimer {
    UnknownSlopeTimer() : unknown_0c(0) {}
    UnknownSlopeTimer(NoInitClass const &noinit) : Timer(noinit) {}
    CDTimerClass<FrameTimerClass> Timer;    // +0x00
    int unknown_0c;                         // +0x0C
};

class LocomotionClass : public IPersistStream, public ILocomotion {
public:
    // IUnknown
    virtual HRESULT __stdcall QueryInterface(GUID const &iid, void **object);   // 0x0053D2B0
    virtual unsigned long __stdcall AddRef();                                    // 0x0053D250
    virtual unsigned long __stdcall Release();                                   // 0x0053D270

    // IPersistStream (GetClassID is pure; Load is pure with a body the
    // locomotors call)
    virtual HRESULT __stdcall IsDirty() { return Dirty ? S_OK : S_FALSE; }      // inline, kept 0x004A4BF0
    virtual HRESULT __stdcall Load(IStream *stream) = 0;                        // 0x0053D3C0
    virtual HRESULT __stdcall Save(IStream *stream, BOOL clear_dirty);          // 0x0053D360
    virtual HRESULT __stdcall GetSizeMax(ULARGE_INTEGER *size);                 // 0x0053D440

    LocomotionClass();                                                          // 0x0053CFC0
    LocomotionClass(NoInitClass const &noinit) {}                               // inline (the locomotors' Load)
    virtual ~LocomotionClass();                                                 // 0x0053CFF0 (slot 8; deleting copy kept 0x004FEF00)
    virtual int Size() = 0;                                                     // slot 9 (the saved size; hypothesis)

    // ILocomotion
    virtual HRESULT __stdcall Link_To_Object(void *object);                     // 0x0053D010
    virtual bool __stdcall Is_Moving();                                         // 0x0053D5D0
    virtual CoordStruct __stdcall Destination();                                // 0x0053D570
    virtual CoordStruct __stdcall Head_To_Coord();                              // 0x0053D5A0
    virtual int __stdcall Can_Enter_Cell(Cell cell);                      // 0x0053D4F0
    virtual bool __stdcall Is_To_Have_Shadow();                                 // 0x0053D4E0
    virtual Matrix3D * __stdcall Draw_Matrix(Matrix3D *matrix, int *key);                           // 0x0053D030
    virtual Matrix3D * __stdcall Shadow_Matrix(Matrix3D *matrix, int *key);                         // 0x0053D0D0
    virtual Point2D __stdcall Draw_Point();                                     // 0x0053D4D0
    virtual Point2D __stdcall Shadow_Point();                                   // 0x0053D1C0
    virtual int __stdcall Visual_Character(bool raw);                           // 0x0053D4C0
    virtual int __stdcall Z_Adjust();                                           // 0x0053D4A0
    virtual int __stdcall Z_Gradient();                                         // 0x0053D4B0
    virtual bool __stdcall Process();                                           // 0x0053D560
    virtual void __stdcall Move_To(CoordStruct to);                             // 0x0053D550
    virtual void __stdcall Stop_Moving();                                       // 0x0053D540
    virtual void __stdcall Do_Turn(UnknownFacingDir dir);                       // 0x0053D530
    virtual void __stdcall Unlimbo();                                           // 0x0053D520
    virtual void __stdcall Tilt_Pitch_AI();                                     // 0x0053D490
    virtual bool __stdcall Power_On();                                          // 0x0053D1F0
    virtual bool __stdcall Power_Off();                                         // 0x0053D210
    virtual bool __stdcall Is_Powered();                                        // 0x0053D230
    virtual bool __stdcall Is_Ion_Sensitive();                                  // 0x0053D240
    virtual bool __stdcall Push(UnknownFacingDir dir);                          // 0x0053D470
    virtual bool __stdcall Shove(UnknownFacingDir dir);                         // 0x0053D480
    virtual void __stdcall Force_Track(int track, CoordStruct coord);           // 0x0053D510
    virtual int __stdcall Layer() = 0;
    virtual void __stdcall Force_Immediate_Destination(CoordStruct coord);      // 0x0053D500
    virtual void __stdcall Force_New_Slope(int ramp);                           // 0x0053D5E0
    virtual bool __stdcall Is_Moving_Now() { return Is_Moving(); }              // inline, kept 0x004A6590
    virtual int __stdcall Apparent_Speed();                                     // 0x0053D610
    virtual int __stdcall Drawing_Code();                                       // 0x0053D5F0
    virtual int __stdcall State();                                              // 0x0053D600
    virtual int __stdcall Get_Status() { return 0; }                            // inline, kept 0x004A4C20
    virtual void __stdcall Acquire_Hunter_Seeker_Target() {}                    // inline, kept 0x004A4C30
    virtual bool __stdcall Is_Surfacing() { return false; }                     // inline, kept 0x004A4C40
    virtual void __stdcall Mark_All_Occupation_Bits(int mark) {}                // inline, kept 0x004A65A0
    virtual bool __stdcall Is_Moving_Here(CoordStruct to) { return false; }     // inline, kept 0x004A65B0
    virtual bool __stdcall Will_Jump_Tracks() { return false; }                 // inline, kept 0x004A65C0
    virtual bool __stdcall Is_Really_Moving_Now() { return Is_Moving_Now(); }   // inline, kept 0x004A4C10
    virtual void __stdcall Stop_Movement_Animation() {}                         // inline, kept 0x004A4C50
    virtual void __stdcall Lock() {}                                            // inline, kept 0x004A65D0
    virtual void __stdcall Unlock() {}                                          // inline, kept 0x004A65E0
    virtual int __stdcall Get_Track_Number() { return -1; }                     // inline, kept 0x004A65F0
    virtual int __stdcall Get_Track_Index() { return -1; }                      // inline, kept 0x004A6600
    virtual int __stdcall Get_Speed_Accum() { return -1; }                      // inline, kept 0x004A6610

    FootClass *Owner;                   // +0x08
    FootClass *LinkedTo;                // +0x0C
    bool Powered;                       // +0x10
    bool Dirty;                         // +0x11
    long RefCount;                      // +0x14
};

#endif
