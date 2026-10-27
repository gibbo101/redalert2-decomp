// Cell MapClass::Unknown_00547F30(Cell const &cell) (0x00547F30)
// Unknown_00547DF0 for cells.
#include "shared/map.hpp"

Cell MapClass::Unknown_00547F30(Cell const &cell)
{
    Point2D point = Unknown_00547DF0(Point2D(cell.X, cell.Y));
    return Cell(point.X, point.Y);
}
