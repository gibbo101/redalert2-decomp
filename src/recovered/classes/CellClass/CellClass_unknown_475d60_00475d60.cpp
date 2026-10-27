// CoordStruct CellClass::unknown_475d60() const (0x00475D60): the cell's
// centre at the height of the cell's middle point (128, 128).
#include "shared/cell.hpp"
// @ref ?unknown_4706c0@CellClass@@QBEHABUPoint2D@@@Z=004706c0

CoordStruct CellClass::unknown_475d60() const
{
    CoordStruct center = Cell_Center(MapCoords);
    return CoordStruct(center.X, center.Y, unknown_4706c0(Point2D(128, 128)));
}
