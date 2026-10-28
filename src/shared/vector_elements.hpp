// Small value types that are known only as elements of VectorClass / DynamicVectorClass
// instantiations (RTTI names from the vtables; the fields are layout hypotheses taken from
// the element constructors, copies and comparisons the template members expand).
// Each has an explicit default constructor that clears it, a member-wise copy constructor
// where the original copies a byte or word separately, and the element comparison the
// ID lookups and VectorClass::operator== use.
#ifndef RA2_SHARED_VECTOR_ELEMENTS_HPP
#define RA2_SHARED_VECTOR_ELEMENTS_HPP

#include "shared/coord.hpp"
#include "shared/rect.hpp"

// 8 bytes; VectorClass<AcceleratorTracker>::operator== 0x005B6540 compares both words.
struct AcceleratorTracker {
    AcceleratorTracker() : unknown_00(0), unknown_04(0) {}
    int unknown_00;
    int unknown_04;
};
inline bool operator==(AcceleratorTracker const &a, AcceleratorTracker const &b)
{
    return a.unknown_00 == b.unknown_00 && a.unknown_04 == b.unknown_04;
}
inline bool operator!=(AcceleratorTracker const &a, AcceleratorTracker const &b) { return !(a == b); }

// 8 bytes: an entry of the swizzle manager's tables (shared/swizzle.hpp): an object's
// address when it was saved and the field to fix or the object's new address. The lookups
// compare the first word only (VectorClass<SwizzlePointerClass>::operator== 0x0069FE40).
struct SwizzlePointerClass {
    SwizzlePointerClass() : ID(0), Pointer(0) {}
    SwizzlePointerClass(long id, void *pointer) : ID(id), Pointer(pointer) {}
    long ID;
    void *Pointer;
};
inline bool operator==(SwizzlePointerClass const &a, SwizzlePointerClass const &b) { return a.ID == b.ID; }
inline bool operator!=(SwizzlePointerClass const &a, SwizzlePointerClass const &b) { return !(a == b); }

// 12 bytes: a coordinate (VectorClass<UndoInfoStruct>::operator== 0x00686FD0 compares all
// three words; the constructor passes three separate zeros).
struct UndoInfoStruct {
    UndoInfoStruct() : Coord(0, 0, 0) {}
    CoordStruct Coord;
};
inline bool operator==(UndoInfoStruct const &a, UndoInfoStruct const &b) { return a.Coord == b.Coord; }
inline bool operator!=(UndoInfoStruct const &a, UndoInfoStruct const &b) { return !(a == b); }

// 0x14 bytes: a rectangle and a flag (VectorClass<DirtyAreaStruct>::Fetch 0x006AC8D0 copies
// the flag as a byte; operator== 0x006AC970 compares it first).
struct DirtyAreaStruct {
    DirtyAreaStruct() : Area(0, 0, 0, 0), unknown_10(false) {}
    DirtyAreaStruct(DirtyAreaStruct const &other) : Area(other.Area), unknown_10(other.unknown_10) {}
    Rect Area;                  // +0x00
    bool unknown_10;            // +0x10
};
inline bool operator==(DirtyAreaStruct const &a, DirtyAreaStruct const &b)
{
    return a.unknown_10 == b.unknown_10 && a.Area == b.Area;
}
inline bool operator!=(DirtyAreaStruct const &a, DirtyAreaStruct const &b) { return !(a == b); }

// 12 bytes (WorldDominationTour::Centroid, the element of a map region's centroid list;
// VectorClass<...>::operator== 0x0072B6C0 compares all three words).
namespace WorldDominationTour {
struct Centroid {
    Centroid() : unknown_00(0), unknown_04(0), unknown_08(0) {}
    int unknown_00;
    int unknown_04;
    int unknown_08;
};
inline bool operator==(Centroid const &a, Centroid const &b)
{
    return a.unknown_00 == b.unknown_00 && a.unknown_04 == b.unknown_04 && a.unknown_08 == b.unknown_08;
}
inline bool operator!=(Centroid const &a, Centroid const &b) { return !(a == b); }
}

#endif
