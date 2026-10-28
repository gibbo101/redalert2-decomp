// ShipLocomotionClass (Ship.cpp, 0x00675410-0x0067AC3F; a copy of Drive.cpp; RTTI vtables
// 0x007AB204 IPersistStream, 0x007AB13C ILocomotion at +4, 0x007AB118
// IPiggyback at +0x18). Size 0x70.
// Layout from the constructor 0x00675600 (names are hypotheses):
//   +0x1C, +0x20  int ramps (Force_New_Slope sets both)
//   +0x24  slope timer (a frame timer and a cleared word; restarted by
//          Force_New_Slope)
//   +0x34  CoordStruct destination, +0x40 CoordStruct head-to coordinate
//          (both start at the unit's zero 0x00ab91c8)
//   +0x4C  speed accumulator, +0x50, +0x54 ints, +0x58 track number (-1),
//   +0x5C  track index (-1), +0x60..+0x64 bools, +0x65 bool (true; Lock
//          clears it), +0x68 the carried locomotor
#ifndef RA2_SHARED_SHIP_LOCOMOTION_HPP
#define RA2_SHARED_SHIP_LOCOMOTION_HPP

#include "shared/locomotion.hpp"

extern CoordStruct unknown_coord_ab91c8;            // 0x00ab91c8
extern "C" GUID const CLSID_ShipLocomotionClass;   // 0x007A1FF0

extern TrackControlStruct const ShipTrackControl[];    // 0x007AADF0 (Ship.cpp's table)
extern RawTrackStruct const ShipRawTracks[];         // 0x007AAD20 (Ship.cpp's table; indexed by track - 1)

class ShipLocomotionClass : public LocomotionClass, public IPiggyback {
public:
    ShipLocomotionClass();                                                     // 0x00675600
    ShipLocomotionClass(NoInitClass const &noinit) :                           // inline (Load)
        LocomotionClass(noinit), unknown_24(noinit) {}
    virtual ~ShipLocomotionClass();                                            // 0x006756A0

    virtual HRESULT __stdcall QueryInterface(GUID const &iid, void **object);   // 0x006757E0
    virtual unsigned long __stdcall AddRef();                                    // 0x0067AB40
    virtual unsigned long __stdcall Release();                                   // 0x0067AB50
    virtual HRESULT __stdcall GetClassID(GUID *clsid);                          // 0x0067A740
    virtual HRESULT __stdcall Load(IStream *stream);                            // 0x00675840
    virtual HRESULT __stdcall Save(IStream *stream, BOOL clear_dirty);          // 0x006758C0
    virtual int Size() { return sizeof(ShipLocomotionClass); }                 // 0x0067AB80 (inline)

    virtual bool __stdcall Is_Moving();                                         // 0x00675C30
    virtual CoordStruct __stdcall Destination();                                // 0x00675D40
    virtual CoordStruct __stdcall Head_To_Coord();                              // 0x00675D70
    virtual Matrix3D * __stdcall Draw_Matrix(Matrix3D *matrix, int *key);                           // 0x00676010
    virtual Matrix3D * __stdcall Shadow_Matrix(Matrix3D *matrix, int *key);                         // 0x006764C0
    virtual int __stdcall Z_Adjust();                                           // 0x0067A780
    virtual int __stdcall Z_Gradient();                                         // 0x0067A790
    virtual bool __stdcall Process();                                           // 0x006765B0
    virtual void __stdcall Move_To(CoordStruct to);                             // 0x00675DF0
    virtual void __stdcall Stop_Moving();                                       // 0x00675EB0
    virtual void __stdcall Do_Turn(UnknownFacingDir dir);                       // 0x00676F30
    virtual void __stdcall Unlimbo();                                           // 0x00676580
    virtual void __stdcall Force_Track(int track, CoordStruct coord);           // 0x00676C90
    virtual int __stdcall Layer();                                              // 0x0067A730
    virtual void __stdcall Force_New_Slope(int ramp);                           // 0x00675BF0
    virtual bool __stdcall Is_Moving_Now();                                     // 0x00675CD0
    virtual void __stdcall Mark_All_Occupation_Bits(int mark);                  // 0x0067A7E0
    virtual bool __stdcall Is_Moving_Here(CoordStruct to);                      // 0x0067A830
    virtual bool __stdcall Will_Jump_Tracks();                                  // 0x0067AA10
    virtual void __stdcall Lock();                                              // 0x0067AAF0
    virtual void __stdcall Unlock();                                            // 0x0067AB00
    virtual int __stdcall Get_Track_Number();                                   // 0x0067AB10
    virtual int __stdcall Get_Track_Index();                                    // 0x0067AB20
    virtual int __stdcall Get_Speed_Accum();                                    // 0x0067AB30

    // IPiggyback
    virtual HRESULT __stdcall Begin_Piggyback(ILocomotion *pointer);            // 0x006759A0
    virtual HRESULT __stdcall End_Piggyback(ILocomotion **pointer);             // 0x006759F0
    virtual bool __stdcall Is_Ok_To_End();                                      // 0x00675A30
    virtual HRESULT __stdcall Piggyback_CLSID(GUID *classid);                   // 0x006756D0
    virtual bool __stdcall Is_Piggybacking();                                   // 0x0067AB60

    void unknown_676b20(CoordStruct const &coord, int mark);                    // 0x00676B20 (marks the track cells)
    Point2D Smooth_Turn(Point2D const &offset, int &facing);                    // 0x0067A690 (a track point and facing mirrored by the track's flags, from the head-to coordinate)

    int unknown_1c;                     // +0x1C ramp
    int unknown_20;                     // +0x20 ramp
    UnknownSlopeTimer unknown_24;       // +0x24
    CoordStruct unknown_34;             // +0x34 destination
    CoordStruct unknown_40;             // +0x40 head-to coordinate
    int unknown_4c;                     // +0x4C speed accumulator
    int unknown_50;                     // +0x50
    int unknown_54;                     // +0x54
    int unknown_58;                     // +0x58 track number
    int unknown_5c;                     // +0x5C track index
    bool unknown_60;                    // +0x60
    bool unknown_61;                    // +0x61
    bool unknown_62;                    // +0x62
    bool unknown_63;                    // +0x63
    bool unknown_64;                    // +0x64
    bool unknown_65;                    // +0x65 unlocked
    UnknownLocomotionPtr Piggybacker;   // +0x68
    int unknown_6c;                     // +0x6C
};

#endif
