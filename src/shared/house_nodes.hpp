// AngerStruct and ScoutStruct: the elements of HouseClass's AngerNodes and ScoutNodes
// (sizes from the constructor; names are hypotheses). Kept out of shared/house.hpp so the
// VectorClass template members that copy them can be compiled without the whole House layout.
#ifndef RA2_SHARED_HOUSE_NODES_HPP
#define RA2_SHARED_HOUSE_NODES_HPP

#include "shared/coord.hpp"

class HouseClass;

struct AngerStruct {
    AngerStruct() : House(0), Value(0) {}
    AngerStruct(AngerStruct const &other) : House(other.House), Value(other.Value) {}   // user copy constructor (member-wise; VectorClass<AngerStruct>::Fetch 0x004F6CB0)
    AngerStruct(HouseClass *house, int value) : House(house), Value(value) {}
    HouseClass *House;
    int Value;
};
struct ScoutStruct {
    ScoutStruct() : House(0), IsPreferred(false) {}
    ScoutStruct(ScoutStruct const &other) : House(other.House), IsPreferred(other.IsPreferred) {}   // user copy constructor (VectorClass<ScoutStruct>::Fetch 0x004F6D20)
    ScoutStruct(HouseClass *house, bool preferred) : House(house), IsPreferred(preferred) {}
    HouseClass *House;
    bool IsPreferred;
};
// A planned building of a base plan (RTTI BaseClass's node list, vtable
// 0x0079C5C0; 0x10-byte elements). Cell ==/!=: shared/coord.hpp.
class BaseNodeClass {
public:                      // (layout hypothesis)
    BaseNodeClass() {}
#ifdef RA2_BASE_NODE_FULL_ARGUMENTS
    // A new node at `cell`, not built and not tried yet (0x004F6BE0, the House unit's copy). Body
    // assignments (64 /Ob2 units, defined in its own source): the base planner 0x004F5D30 inlines it
    // until the budget runs out and calls it for its last three wall corners.
    BaseNodeClass(int type, ::Cell const &cell);
    BaseNodeClass(int type, ::Cell cell, bool built, int counter) : Type(type), Cell(cell), unknown_08(built), unknown_0c(counter) {}
#else
    BaseNodeClass(int type, ::Cell cell) : Type(type), Cell(cell) {}   // BaseClass::Read_INI 0x0042C460 (other fields unset)
#endif
    // User copy constructor, member-wise (VectorClass<BaseNodeClass>::Fetch 0x0042CBE0 copies the byte separately).
    BaseNodeClass(BaseNodeClass const &other)
        : Type(other.Type), Cell(other.Cell), unknown_08(other.unknown_08), unknown_0c(other.unknown_0c)
    {
    }
    int Type;
    ::Cell Cell;
    bool unknown_08;
    int unknown_0c;              // not compared
#ifdef RA2_BASE_NODE_MEMBER_OPERATORS
    // base.cpp defines the members (0x0042BEE0 ==, 0x0042BF10 !=, 0x0042BF60 >; no callers); the
    // unit that defines RA2_BASE_NODE_MEMBER_OPERATORS sees them instead of the inline free forms.
    bool operator==(BaseNodeClass const &node);
    bool operator!=(BaseNodeClass const &node);
#endif
    // TibSun's member operator> (0x0042BF60, defined in the BaseClass unit; no callers).
    bool operator>(BaseNodeClass const &node);
};
#ifndef RA2_BASE_NODE_MEMBER_OPERATORS
// Compares the type and the cell only (VectorClass<BaseNodeClass>::operator== 0x0042CC80).
inline bool operator==(BaseNodeClass const &a, BaseNodeClass const &b) { return a.Type == b.Type && a.Cell == b.Cell; }
inline bool operator!=(BaseNodeClass const &a, BaseNodeClass const &b) { return !(a == b); }
#endif
inline bool operator==(AngerStruct const &a, AngerStruct const &b) { return a.House == b.House && a.Value == b.Value; }
inline bool operator!=(AngerStruct const &a, AngerStruct const &b) { return !(a == b); }
inline bool operator==(ScoutStruct const &a, ScoutStruct const &b) { return a.House == b.House && a.IsPreferred == b.IsPreferred; }
inline bool operator!=(ScoutStruct const &a, ScoutStruct const &b) { return !(a == b); }
#endif
