// bool TechnoClass::unknown_slot214(CoordStruct const &coord) (0x006C5200, slot 214)
// Slot 213 for the cell of a coordinate.
#include "shared/techno.hpp"
#include "shared/gscreen.hpp"
#include "shared/techno_map.hpp"

bool TechnoClass::unknown_slot214(CoordStruct const &coord)
{
    AbstractClass *cell = (AbstractClass *)&Map[coord];
    return unknown_slot212(cell, unknown_slot174(cell));
}
