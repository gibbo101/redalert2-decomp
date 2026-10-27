// Cell MapClass::Unknown_00547EE0(Cell const &cell) (0x00547EE0)
// Unknown_00547DB0 for cells. No direct callers (inlined everywhere).
#include "shared/map.hpp"

Cell MapClass::Unknown_00547EE0(Cell const &cell)
{
    Point2D point = Unknown_00547DB0(Point2D(cell.X, cell.Y));
    return Cell(point.X, point.Y);
}
