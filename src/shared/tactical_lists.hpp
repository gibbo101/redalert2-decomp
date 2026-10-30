// The dirty-area and shadow-control lists of the Tactical unit (TibSun's
// Tactical::DirtyAreas and Tactical::ShadowControls). They are static data
// members (VC6 guards their exit destructors 0x006A2330/0x006A23E0 with a bit),
// held here rather than in shared/tactical.hpp: a static member declared in a
// widely included header takes a value of every including unit's initializer
// counter and renumbers its _$E/$S names (OPEN_MISSES Tiny74). Only the
// Tactical unit includes this header.
#ifndef RA2_SHARED_TACTICAL_LISTS_HPP
#define RA2_SHARED_TACTICAL_LISTS_HPP

#include "shared/vector_class.hpp"
#include "shared/vector_elements.hpp"
#include "shared/rect.hpp"

// A shadow control (0x28 bytes; Tactical::Add_Shadow_Control 0x006A7130 copies
// one onto the heap member by member: a rectangle, a value, a second
// rectangle, a value; meanings unknown).
class ShadowControlClass {
public:
    ShadowControlClass(ShadowControlClass const &other) :
        unknown_00(other.unknown_00), unknown_04(other.unknown_04), unknown_08(other.unknown_08),
        unknown_0c(other.unknown_0c), unknown_10(other.unknown_10), unknown_14(other.unknown_14),
        unknown_24(other.unknown_24) {}
    int unknown_00;                 // +0x00
    int unknown_04;                 // +0x04
    int unknown_08;                 // +0x08
    int unknown_0c;                 // +0x0C
    int unknown_10;                 // +0x10
    Rect unknown_14;                // +0x14
    int unknown_24;                 // +0x24
};

struct TacticalLists {
    static DynamicVectorClass<DirtyAreaStruct> DirtyAreas;              // 0x00ABE5B0
    static DynamicVectorClass<ShadowControlClass *> ShadowControls;     // 0x00ABE528
};

#endif
