// SubzoneTrackingStruct: the element of MapClass's three subzone tracking vectors, kept
// apart from shared/map_elements.hpp because its list member makes every VectorClass
// instantiation that sees it emit the list's own implicit members.
#ifndef RA2_SHARED_SUBZONE_TRACKING_HPP
#define RA2_SHARED_SUBZONE_TRACKING_HPP

#include "shared/map_elements.hpp"

// 0x24-byte element of the three subzone tracking vectors (constructor
// inlined into VectorClass<SubzoneTrackingStruct>::VectorClass 0x0056CC40,
// vector deleting destructor 0x0040AFA0).
struct SubzoneTrackingStruct {
#ifdef RA2_MAP_SUBZONE_ASSIGN_SOURCE
    SubzoneTrackingStruct &operator=(SubzoneTrackingStruct const &other); // original0056C2E0
#endif
    SubzoneTrackingStruct()
    {
        Connections.Clear();
        unknown_18 = 0;
        unknown_1c = 0;
        unknown_20 = 0;
    }
    // Member-wise (VectorClass<SubzoneTrackingStruct>::Fetch 0x0056ABF0 expands the list copy).
    SubzoneTrackingStruct(SubzoneTrackingStruct const &other)
        : Connections(other.Connections), unknown_18(other.unknown_18), unknown_1c(other.unknown_1c), unknown_20(other.unknown_20)
    {
    }
    DynamicVectorClass<SubzoneConnectionStruct> Connections;    // +0x00
    short unknown_18;               // +0x18
    int unknown_1c;                 // +0x1C
    int unknown_20;                 // +0x20
};

inline bool operator==(SubzoneTrackingStruct const &a, SubzoneTrackingStruct const &b)
{
    return a.unknown_18 == b.unknown_18 && a.unknown_1c == b.unknown_1c;
}
inline bool operator!=(SubzoneTrackingStruct const &a, SubzoneTrackingStruct const &b) { return !(a == b); }

#endif
