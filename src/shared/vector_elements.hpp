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

// 12 bytes: a cell and the value recorded for it (the map-generation undo list
// 0x00ABCE18: unknown_undo_record_684fc0 adds one, unknown_undo_restore_685030 writes the
// values back; VectorClass<UndoInfoStruct>::operator== 0x00686FD0 compares all three words).
struct UndoInfoStruct {
    UndoInfoStruct() : X(0), Y(0), Value(0) {}
    int X;              // +0x00
    int Y;              // +0x04
    int Value;          // +0x08
};
inline bool operator==(UndoInfoStruct const &a, UndoInfoStruct const &b)
{
    return a.X == b.X && a.Y == b.Y && a.Value == b.Value;
}
inline bool operator!=(UndoInfoStruct const &a, UndoInfoStruct const &b) { return !(a == b); }

// 0x14 bytes: a rectangle and a flag (VectorClass<DirtyAreaStruct>::Fetch 0x006AC8D0 copies
// the flag as a byte; operator== 0x006AC970 compares it first).
struct DirtyAreaStruct {
    DirtyAreaStruct() : Area(0, 0, 0, 0), unknown_10(false) {}
    DirtyAreaStruct(DirtyAreaStruct const &other) : Area(other.Area), unknown_10(other.unknown_10) {}
    // An area and its shroud flag (Tactical::Register_Dirty_Area 0x006A3020). The area goes
    // through Rect(x, y, w, h): with the plain copy Area(area) the IL is smaller and the
    // second Union in Register_Dirty_Area stays inline (the original calls 0x0045EFE0).
    DirtyAreaStruct(Rect const &area, bool flag) : Area(area.X, area.Y, area.Width, area.Height), unknown_10(flag) {}
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
#ifdef CENTROID_DECLARE_CONSTRUCTOR
    Centroid(); // 0072A7B0; standalone definition supplied by WDTMap.cpp.
#else
    Centroid() : unknown_00(0), unknown_04(0), unknown_08(0) {}
#endif
#ifdef CENTROID_DECLARE_MEMBERS
    // Guarded (defined by WDTMap.cpp only): new declarations here flip Pick_Lobby 0x00744090's
    // instruction order (type-count sensitivity, VC6_MATCHING_NOTES).
    // Adds a point to the sums (WDTMap.cpp 0x0072A7C0; inlined into the WDTMap.ini builder 0x0072A880).
    Centroid &operator+=(Point2D const &point);
    // The mean of the added points ((0, 0) when there are none; WDTMap.cpp 0x0072A7F0).
    Point2D Average() const;
#endif
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
