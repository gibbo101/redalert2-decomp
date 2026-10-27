// void CellClass::unknown_473d20(ObjectClass *object, bool alt) (0x00473D20):
// unlinks object from the occupier list (alt: the alternate list) and then,
// unless it is infantry (kind 0x0F), calls its slot 59 with the cell's centre
// (buildings) or its own coordinate when its slot 47 agrees.
#include "shared/cell.hpp"
#include "shared/object.hpp"

void CellClass::unknown_473d20(ObjectClass *object, bool alt)
{
    if (object != 0) {
        ObjectClass *occupier = alt ? AltOccupierPtr : OccupierPtr;
        if (occupier == object) {
            if (alt) {
                AltOccupierPtr = object->unknown_30;
            } else {
                OccupierPtr = object->unknown_30;
            }
            object->unknown_30 = 0;
        } else {
            for (ObjectClass *previous = occupier; previous != 0; previous = previous->unknown_30) {
                if (previous->unknown_30 == object) {
                    previous->unknown_30 = object->unknown_30;
                    object->unknown_30 = 0;
                    break;
                }
            }
        }
        if (object->Kind_Of() != 0x0F && object->unknown_slot47()) {
            CoordStruct coord;
            if (object->Kind_Of() == 6) {
                CoordStruct center(MapCoords.X * 256 + 128, MapCoords.Y * 256 + 128, 0);
                object->unknown_slot59(center);
            } else {
                CoordStruct coord = object->Coord;
                object->unknown_slot59(coord);
            }
        }
    }
}
