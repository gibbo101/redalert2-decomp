// void CellClass::unknown_473b30(ObjectClass *object, bool alt) (0x00473B30): TibSun's Occupy_Down: links
// object into the occupier list (alt: the alternate list), a building at the end of the chain, reveals it
// and marks the cell's occupy bit.
#include "shared/cell.hpp"
#include "shared/object.hpp"
#include "shared/map_view.hpp"

void CellClass::unknown_473b30(ObjectClass *object, bool alt)
{
    ObjectClass *optr = alt ? AltOccupierPtr : OccupierPtr;

    if (object == 0) {
        return;
    }

    if (object->Kind_Of() == 6 && optr != 0) {
        while (optr->unknown_30 != 0) {
            optr = optr->unknown_30;
        }
        optr->unknown_30 = object;
        object->unknown_30 = 0;
    } else if (alt) {
        if (optr == 0 || optr->unknown_30 != object) {
            object->unknown_30 = optr;
            AltOccupierPtr = object;
        }
    } else {
        if (optr == 0 || optr->unknown_30 != object) {
            object->unknown_30 = optr;
            OccupierPtr = object;
        }
    }

    if (!Map.Unknown_00568140(unknown_475d60()) && !Map.Unknown_005683C0(unknown_475d60()) || unknown_game_mode_a3d298 != 0) {
        object->unknown_slot96(unknown_player_a35db4);
    }

    if (object->Kind_Of() != 0x0F && object->unknown_slot47()) {
        if (object->Kind_Of() == 6) {
            CoordStruct center(MapCoords.X * 256 + 128, MapCoords.Y * 256 + 128, 0);
            object->unknown_slot58(center);
        } else {
            CoordStruct coord = object->Coord;
            object->unknown_slot58(coord);
        }
    }
}
