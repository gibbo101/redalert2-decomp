// bool TechnoClass::unknown_slot84(CoordStruct const &coord, int weapon) (0x006C5240, slot 84)
// Slot 212 for the cell object at coord.
#include "shared/techno.hpp"
#include "shared/gscreen.hpp"
#include "shared/techno_map.hpp"

bool TechnoClass::unknown_slot84(CoordStruct const &coord, int weapon)
{
    return unknown_slot212((AbstractClass *)&Map[coord], weapon);
}
