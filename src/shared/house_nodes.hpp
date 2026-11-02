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
    // Original004F6BE0 node reset; constructor identity remains unproven.
    BaseNodeClass *unknown_4f6be0(int type, ::Cell const &cell);
    BaseNodeClass(int type, ::Cell cell) : Type(type), Cell(cell) {}
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
    bool operator>(BaseNodeClass const &node);
#endif
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
