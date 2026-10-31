// Cell MapClass::Pick_Random_Location() const (0x00559EB0)
// TibSun Pick_Random_Location: a random cell of the map rectangle (Map +0x120/+0x124 the
// first cell, +0x128/+0x12C the size in cells), read through the global Map. No callers or
// pointers to it were found; the thiscall member ABI follows from its body (ECX unused, the
// returned Cell through the hidden pointer, ret 4).
#include "shared/map.hpp"
#include "shared/map_view.hpp"
#include "shared/id_source.hpp"

Cell MapClass::Pick_Random_Location() const
{
    int x = Map.unknown_120 + Random_Pick(0, Map.unknown_128 - 1);
    int y = Map.unknown_124 + Random_Pick(0, Map.unknown_12c - 1);
    return XY_Cell(x, y);
}
