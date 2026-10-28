// DriveLocomotionClass (Drive.cpp, 0x0049F450-0x004A4D9F; RTTI vtables
// 0x007A0594 IPersistStream, 0x007A04CC ILocomotion at +4, 0x007A04A8
// IPiggyback at +0x18). Size 0x70.
// Layout from the constructor 0x0049F640 (names are hypotheses):
//   +0x1C, +0x20  int ramps (Force_New_Slope sets both)
//   +0x24  slope timer (a frame timer and a cleared word; restarted by
//          Force_New_Slope)
//   +0x34  CoordStruct destination, +0x40 CoordStruct head-to coordinate
//          (both start at the unit's zero 0x00852998)
//   +0x4C  speed accumulator, +0x50, +0x54 ints, +0x58 track number (-1),
//   +0x5C  track index (-1), +0x60..+0x64 bools, +0x65 bool (true; Lock
//          clears it), +0x68 the carried locomotor
#ifndef RA2_SHARED_DRIVE_LOCOMOTION_HPP
#define RA2_SHARED_DRIVE_LOCOMOTION_HPP

#include "shared/locomotion.hpp"

extern CoordStruct unknown_coord_852998;            // 0x00852998
extern "C" GUID const CLSID_DriveLocomotionClass;   // 0x007A1F70

extern TrackControlStruct const DriveTrackControl[];   // 0x007A0180 (Drive.cpp's table)
extern RawTrackStruct const DriveRawTracks[];        // 0x007A00B0 (Drive.cpp's table; indexed by track - 1)

class DriveLocomotionClass : public LocomotionClass, public IPiggyback {
public:
    DriveLocomotionClass();                                                     // 0x0049F640
    DriveLocomotionClass(NoInitClass const &noinit) :                           // inline (Load)
        LocomotionClass(noinit), unknown_24(noinit) {}
    virtual ~DriveLocomotionClass();                                            // 0x0049F6E0

    virtual HRESULT __stdcall QueryInterface(GUID const &iid, void **object);   // 0x0049F820
    virtual unsigned long __stdcall AddRef();                                    // 0x004A4C60
    virtual unsigned long __stdcall Release();                                   // 0x004A4C70
    virtual HRESULT __stdcall GetClassID(GUID *clsid);                          // 0x004A47F0
    virtual HRESULT __stdcall Load(IStream *stream);                            // 0x0049F880
    virtual HRESULT __stdcall Save(IStream *stream, BOOL clear_dirty);          // 0x0049F900
    virtual int Size() { return sizeof(DriveLocomotionClass); }                 // 0x004A4CA0 (inline)

    virtual bool __stdcall Is_Moving();                                         // 0x0049FC70
    virtual CoordStruct __stdcall Destination();                                // 0x0049FD80
    virtual CoordStruct __stdcall Head_To_Coord();                              // 0x0049FDB0
    virtual Matrix3D * __stdcall Draw_Matrix(Matrix3D *matrix, int *key);                           // 0x004A0050
    virtual Matrix3D * __stdcall Shadow_Matrix(Matrix3D *matrix, int *key);                         // 0x004A0500
    virtual int __stdcall Z_Adjust();                                           // 0x004A4830
    virtual int __stdcall Z_Gradient();                                         // 0x004A4840
    virtual bool __stdcall Process();                                           // 0x004A05F0
    virtual void __stdcall Move_To(CoordStruct to);                             // 0x0049FE30
    virtual void __stdcall Stop_Moving();                                       // 0x0049FEF0
    virtual void __stdcall Do_Turn(UnknownFacingDir dir);                       // 0x004A0FD0
    virtual void __stdcall Unlimbo();                                           // 0x004A05C0
    virtual void __stdcall Force_Track(int track, CoordStruct coord);           // 0x004A0D30
    virtual int __stdcall Layer();                                              // 0x004A47E0
    virtual void __stdcall Force_New_Slope(int ramp);                           // 0x0049FC30
    virtual bool __stdcall Is_Moving_Now();                                     // 0x0049FD10
    virtual void __stdcall Mark_All_Occupation_Bits(int mark);                  // 0x004A4890
    virtual bool __stdcall Is_Moving_Here(CoordStruct to);                      // 0x004A48E0
    virtual bool __stdcall Will_Jump_Tracks();                                  // 0x004A4AC0
    virtual void __stdcall Lock();                                              // 0x004A4BA0
    virtual void __stdcall Unlock();                                            // 0x004A4BB0
    virtual int __stdcall Get_Track_Number();                                   // 0x004A4BC0
    virtual int __stdcall Get_Track_Index();                                    // 0x004A4BD0
    virtual int __stdcall Get_Speed_Accum();                                    // 0x004A4BE0

    // IPiggyback
    virtual HRESULT __stdcall Begin_Piggyback(ILocomotion *pointer);            // 0x0049F9E0
    virtual HRESULT __stdcall End_Piggyback(ILocomotion **pointer);             // 0x0049FA30
    virtual bool __stdcall Is_Ok_To_End();                                      // 0x0049FA70
    virtual HRESULT __stdcall Piggyback_CLSID(GUID *classid);                   // 0x0049F710
    virtual bool __stdcall Is_Piggybacking();                                   // 0x004A4C80

    void unknown_4a0bc0(CoordStruct const &coord, int mark);                    // 0x004A0BC0 (marks the track cells)
    Point2D Smooth_Turn(Point2D const &offset, int &facing);                    // 0x004A4740 (a track point and facing mirrored by the track's flags, from the head-to coordinate)

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
