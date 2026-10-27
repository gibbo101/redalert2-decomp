// Element types of MapClass's zone and subzone vectors and hash tables, kept out of
// shared/map.hpp so the VectorClass/DynamicVectorClass template members that copy
// and compare them can be compiled without the whole MapClass layout.
// (Moved unchanged from shared/map.hpp.) Cell ==/!=: shared/coord.hpp.
#ifndef RA2_SHARED_MAP_ELEMENTS_HPP
#define RA2_SHARED_MAP_ELEMENTS_HPP

#include "shared/coord.hpp"
#include "shared/hash_object.hpp"
#include "shared/vector_class.hpp"

// A connection between two cells' zones (16 bytes; the element constructor
// inlined into VectorClass<ZoneConnectionClass>::VectorClass 0x0056CB90).
struct ZoneConnectionClass {
    ZoneConnectionClass() : From(0, 0), To(0, 0), unknown_08(false), unknown_0c(-1) {}
    // Member-wise (MouseClass::unknown_slot31 copies the bool as one byte).
    ZoneConnectionClass(ZoneConnectionClass const &other)
        : From(other.From), To(other.To), unknown_08(other.unknown_08), unknown_0c(other.unknown_0c)
    {
    }
    Cell From;                // +0x00
    Cell To;                  // +0x04
    bool unknown_08;                // +0x08
    int unknown_0c;                 // +0x0C -1 when unset
};

// 8-byte element of SubzoneTrackingStruct's list (DynamicVectorClass ID
// 0x0056AAA0 divides by 8); contents unknown.
struct SubzoneConnectionStruct {
    SubzoneConnectionStruct() : unknown_00(0), unknown_04(false) {}
    // Member-wise: VectorClass<SubzoneConnectionStruct>::Fetch (0x0040B050) copies the byte alone.
    SubzoneConnectionStruct(SubzoneConnectionStruct const &other)
        : unknown_00(other.unknown_00), unknown_04(other.unknown_04)
    {
    }
    int unknown_00;
    bool unknown_04;
};


// Element comparisons used by the vector ID lookups and operator== (the
// template members are recovered separately; member-wise comparison is a
// hypothesis for the element types that have no recovered operator).
// Cell ==/!=: shared/coord.hpp.
inline bool operator==(ZoneConnectionClass const &a, ZoneConnectionClass const &b)
{
    return a.From == b.From && a.To == b.To;
}
inline bool operator!=(ZoneConnectionClass const &a, ZoneConnectionClass const &b) { return !(a == b); }
inline bool operator==(SubzoneConnectionStruct const &a, SubzoneConnectionStruct const &b)
{
    return a.unknown_00 == b.unknown_00;
}
inline bool operator!=(SubzoneConnectionStruct const &a, SubzoneConnectionStruct const &b) { return !(a == b); }

#endif
