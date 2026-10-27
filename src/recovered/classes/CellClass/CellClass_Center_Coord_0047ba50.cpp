// CoordStruct CellClass::Center_Coord() const (0x0047BA50, slot 18): the
// cell's centre at the ground height there.
#include "shared/cell.hpp"
// @ref ?unknown_4706c0@CellClass@@QBEHABUPoint2D@@@Z=004706c0

CoordStruct CellClass::Center_Coord() const
{
    int x = MapCoords.X * 256 + 128;
    int y = MapCoords.Y * 256 + 128;
    return CoordStruct(x, y, unknown_4706c0(Point2D(x, y)));
}
