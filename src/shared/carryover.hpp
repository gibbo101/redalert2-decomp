// CarryoverClass (RTTI vtable 0x0079D83C, LinkClass base; unit 0x00468AC0):
// one object carried over to the next scenario (Westwood's CARRY.CPP).
// Layout from the constructor 0x00468CB0 and Create 0x00468D50.
#ifndef RA2_SHARED_CARRYOVER_HPP
#define RA2_SHARED_CARRYOVER_HPP

#include "shared/gadget.hpp"
#include "shared/coord.hpp"

class TechnoClass;

class CarryoverClass : public LinkClass {
public:
    CarryoverClass(TechnoClass *techno = 0);        // 0x00468CB0 (scalar deleting destructor 0x00468E80)
    bool Create() const;                            // 0x00468D50 (recreates the object; false)

    int RTTI;               // +0x0C Kind_Of of the object (1 unit, 6 building, 15 infantry)
    int Type;               // +0x10 its type's heap index
    Cell Position;          // +0x14 its cell
    int Strength;           // +0x18
    int House;              // +0x1C the owner's house type index (-1: none)
};

#endif
