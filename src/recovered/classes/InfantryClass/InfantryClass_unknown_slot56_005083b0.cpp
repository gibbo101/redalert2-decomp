// bool InfantryClass::unknown_slot56(CoordStruct const &coord) (0x005083B0, slot 56)
// ObjectClass's slot 56; on success queue mission 5 (15 when the house
// check 0x004F52F0 fails) and play action 33.
#include "shared/infantry.hpp"
// @ref ?unknown_slot56@ObjectClass@@UAE_NABUCoordStruct@@@Z=005d4240
// @ref ?Unknown_004F52F0@HouseClass@@QAE_NXZ=004f52f0

bool InfantryClass::unknown_slot56(CoordStruct const &coord)
{
    if (ObjectClass::unknown_slot56(coord)) {
        if (House->Unknown_004F52F0()) {
            unknown_slot116(5, false);
        } else {
            unknown_slot116(15, false);
        }
        unknown_slot311(33, 1, 0);
        return true;
    }
    return false;
}
