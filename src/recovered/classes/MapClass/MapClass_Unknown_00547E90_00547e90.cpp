// Cell MapClass::Unknown_00547E90(Cell const &cell) (0x00547E90)
// Unknown_00547D70 for cells. No direct callers (inlined everywhere).
#include "shared/map.hpp"

Cell MapClass::Unknown_00547E90(Cell const &cell)
{
    Point2D point = Unknown_00547D70(Point2D(cell.X, cell.Y));
    return Cell(point.X, point.Y);
}
