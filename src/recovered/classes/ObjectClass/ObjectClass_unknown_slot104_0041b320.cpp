#include "shared/object.hpp"

Cell ObjectClass::unknown_slot104() const
{
    Cell cell;
    cell.X = Coord.X / 256;
    cell.Y = Coord.Y / 256;
    return cell;
}
