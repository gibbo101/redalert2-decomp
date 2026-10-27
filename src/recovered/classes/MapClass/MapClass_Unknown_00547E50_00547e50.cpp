// Cell MapClass::Unknown_00547E50(Cell const &cell) (0x00547E50)
// Unknown_00547D40 for cells. No direct callers (inlined everywhere).
#include "shared/map.hpp"

Cell MapClass::Unknown_00547E50(Cell const &cell)
{
    Point2D point = Unknown_00547D40(Point2D(cell.X, cell.Y));
    return Cell(point.X, point.Y);
}
