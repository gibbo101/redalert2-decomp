// bool Tactical::Is_Cell_Visible(Cell const &cell) (0x006A9120): the cell lies in
// the visible cell rectangle (+0xD80) (TibSun Tactical::Is_Cell_Visible).
#include "shared/tactical.hpp"

bool Tactical::Is_Cell_Visible(Cell const &cell)
{
    Point2D point = Point2D(cell.X, cell.Y);
    if (unknown_d80.Is_Point_Within(point)) {
        return true;
    }
    return false;
}
