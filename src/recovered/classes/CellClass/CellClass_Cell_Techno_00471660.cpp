// ObjectClass *CellClass::unknown_471660(Point2D const &spot, bool alt, ObjectClass *except) const
// (0x00471660): Westwood's Cell_Techno. The techno occupier (alt: on the bridge) other than except
// closest to the pixel spot inside the cell.
#include "shared/cell.hpp"
#include "shared/object.hpp"

ObjectClass *CellClass::unknown_471660(Point2D const &spot, bool alt, ObjectClass *except) const
{
    ObjectClass *object;
    CoordStruct click;
    ObjectClass *close = 0;
    int distance = 0;

    click = CoordStruct(spot.X * 7, spot.Y * 7, 0);
    ObjectClass *occupier = alt ? AltOccupierPtr : OccupierPtr;
    if (occupier != 0) {
        object = occupier;
        while (object != 0) {
            bool techno;
            if (object != 0) {
                techno = object->unknown_14_bit0;
            }
            if (object != 0 && techno && object != except) {
                CoordStruct coord = object->Center_Coord();
                // Westwood's Coord_Fraction(coord) - click.
                CoordStruct fraction = CoordStruct(coord.X & 0xFF, coord.Y & 0xFF, coord.Z) - click;
                int dist = Point2D(fraction.X, fraction.Y).Length();
                if (close == 0 || dist < distance) {
                    close = object;
                    distance = dist;
                }
            }
            object = object->unknown_30;
        }
    }
    return close;
}
