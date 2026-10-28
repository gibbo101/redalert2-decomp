// WaypointPathClass (WaypointPath.cpp, unit 0x007249F0-0x007252CF plus its
// container COMDATs; RTTI vtables 0x007AEF28 primary, 0x007AEF0C
// IRTTITypeInfo, 0x007AEF04 INoticeSink, 0x007AEEFC INoticeSource) and
// WaypointClass (RTTI DynamicVectorClass<WaypointClass> 0x007AEF8C,
// VectorClass<WaypointClass> 0x007AEFAC).
//
// Layout (constructors 0x00724B10/0x00724BF0, Load 0x00725050):
//   AbstractClass                    +0x00..+0x23
//   +0x24  int Selected              -1; the waypoint picked by
//                                    Select_Waypoint (0x00724E30); the
//                                    path loops back to it (name hypothesis)
//   +0x28  DynamicVectorClass<WaypointClass> Waypoints
//   size 0x40 (Size_Of), Kind_Of 0x33
//
// The paths live in the unit's list at 0x00B25590 (defined with the unit's
// header statics, HeaderStatics_diagonal_init_00724780.cpp).
// shared/house.hpp includes this header (HouseClass keeps the paths).
#ifndef RA2_SHARED_WAYPOINT_PATH_HPP
#define RA2_SHARED_WAYPOINT_PATH_HPP

#include "shared/abstract.hpp"
#include "shared/coord.hpp"
#include "shared/vector_class.hpp"

// One waypoint: a cell-centred coordinate (12 bytes). The constructor,
// copy constructor and destructor are defined in the unit (0x00724AD0,
// 0x00724AE0, 0x00724B00) and expanded inline wherever the unit uses them.
struct WaypointClass {
    WaypointClass();                                // 0x00724AD0
    WaypointClass(WaypointClass const &waypoint);   // 0x00724AE0
    ~WaypointClass();                               // 0x00724B00
    // Member-wise comparison (the container lookups 0x00725490, 0x00725800).
    bool operator==(WaypointClass const &waypoint) const
    {
        return Coord.X == waypoint.Coord.X && Coord.Y == waypoint.Coord.Y && Coord.Z == waypoint.Coord.Z;
    }
    bool operator!=(WaypointClass const &waypoint) const { return !(*this == waypoint); }
    // Its (x, y, z) constructor wraps CoordStruct's (0x00434820 around
    // 0x0041B630; shared/coord.hpp).
    UnknownCoord434820 Coord;
};

class WaypointPathClass : public AbstractClass {
public:
    // IPersist / IPersistStream
    virtual HRESULT __stdcall GetClassID(GUID *clsid);                  // 0x00725010
    virtual HRESULT __stdcall Load(IStream *stream);                    // 0x00725050
    virtual HRESULT __stdcall Save(IStream *stream, BOOL clear_dirty);  // 0x00725170

    WaypointPathClass();                                    // 0x00724B10
    WaypointPathClass(NoInitClass const &noinit);           // 0x00724BB0
    WaypointPathClass(int index);                           // 0x00724BF0 (index: a path number 0..11; hypothesis)
    virtual ~WaypointPathClass();                           // 0x00724CA0

    virtual int Kind_Of() const;                            // 0x007251F0 slot 11 (0x33)
    virtual int Size_Of() const;                            // 0x007251E0 slot 12 (0x40)
    virtual void Compute_CRC(WWCRCEngine &crc) const;       // 0x00724FE0 slot 13

    WaypointClass *Get_Waypoint(int index);                 // 0x00724D60
    bool Add_Waypoint(CoordStruct const &coord);            // 0x00724D80 (adds the cell centre; hypothesis)
    bool Select_Waypoint(CoordStruct const &coord);         // 0x00724E30 (by cell; name hypothesis)
    void Set_Waypoint(int index, WaypointClass const &waypoint);   // 0x00724ED0 (name hypothesis)
    void Remove_Waypoint(int index);                        // 0x00724F10 (name hypothesis)
    WaypointClass *Next_Waypoint(WaypointClass const *waypoint);   // 0x00724F80 (name hypothesis)
    void Clear_Waypoints();                                 // 0x00724FC0 (name hypothesis)

    int Selected;                                   // +0x24
    DynamicVectorClass<WaypointClass> Waypoints;    // +0x28
};

extern "C" GUID const CLSID_WaypointPathClass;     // 0x007A1DC0

// The unit's list of paths (0x00B25590; name is a hypothesis).
extern DynamicVectorClass<WaypointPathClass *> unknown_WaypointPathClass_list_00b25590;

extern "C" int __cdecl isalpha(int character);
extern "C" int __cdecl toupper(int character);

#include "shared/waypoint_string.hpp"

#endif
