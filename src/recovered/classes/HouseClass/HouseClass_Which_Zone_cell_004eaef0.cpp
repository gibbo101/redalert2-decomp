// int HouseClass::Which_Zone(Cell const &cell) const (0x004EAEF0)
// The base zone of a cell (its center coordinate).
#include "shared/techno.hpp"

int HouseClass::Which_Zone(Cell const &cell) const
{
    return Which_Zone(CoordStruct(cell.X * 256 + 128, cell.Y * 256 + 128, 0));
}
