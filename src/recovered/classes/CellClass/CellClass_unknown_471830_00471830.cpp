// ObjectClass *CellClass::unknown_471830(Point2D const &spot, bool alt)
// (0x00471830): while the flag at 0x00A40958 is set an aircraft (kind 2) in
// the occupant list wins; otherwise the occupant nearest the spot
// (unknown_471660), and failing that, with the flag set, an occupant of kind
// 0x24. TeamClass 0x006BB260 asks it.
#include "shared/cell.hpp"
#include "shared/unknown_globals.hpp"

ObjectClass *CellClass::unknown_471830(Point2D const &spot, bool alt)
{
    ObjectClass *object;
    if (unknown_flag_a40958) {
        for (object = OccupierPtr; object != 0; object = object->unknown_30) {
            if (object->Kind_Of() == 2) {
                break;
            }
        }
        if (object != 0) {
            return object;
        }
    }
    object = unknown_471660(spot, alt, 0);
    if (object == 0) {
        if (unknown_flag_a40958) {
            for (object = OccupierPtr; object != 0; object = object->unknown_30) {
                if (object->Kind_Of() == 0x24) {
                    return object;
                }
            }
        }
        object = 0;
    }
    return object;
}
