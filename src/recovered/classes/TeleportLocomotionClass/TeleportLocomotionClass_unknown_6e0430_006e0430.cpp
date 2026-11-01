// void TeleportLocomotionClass::unknown_6e0430(CoordStruct coord) (0x006E0430)
// The warp arrival at coord (Process, state 5): each occupant of the cell
// that slot 83 marks crushes the linked object (C4Warhead, its full
// strength); a land unit on water that is not on a bridge sinks (+0x325,
// slot 210), and a naval object off water, or one the cell refuses
// (slot 101 answers 7), is destroyed unless the cell (0x0047B7E0) lets an
// infantry-less object sink there.
#include "shared/teleport_locomotion.hpp"
#include "shared/cell.hpp"
#include "shared/rules.hpp"
#include "shared/techno_type.hpp"

void TeleportLocomotionClass::unknown_6e0430(CoordStruct coord)
{
    for (ObjectClass *object = Map[coord].OccupierPtr; object != 0; object = object->unknown_30) {
        if (object->unknown_slot83()) {
            int damage = LinkedTo->unknown_slot32()->MaxStrength;
            LinkedTo->unknown_slot86(&damage, 0, Rules->unknown_c74, 0, true, 0);
        }
    }
    bool kill = false;
    if (LinkedTo->unknown_slot32()->Naval && ((Map[coord].unknown_140 & 0x100) || Map[coord].unknown_ec == 1)) {
        kill = true;
    }
    if (Map[Coord_Cell(coord)].unknown_ec == 2 && !LinkedTo->unknown_slot32()->Naval && LinkedTo->Kind_Of() != 15
        && !(Map[coord].unknown_140 & 0x100) && Map[coord].unknown_ec != 1) {
        LinkedTo->unknown_325 = true;
        LinkedTo->unknown_slot210();
        return;
    }
    if (LinkedTo->unknown_slot101(&Map[Coord_Cell(coord)], -1, -1, 0, true) == 7 || kill) {
        if (!Map[Coord_Cell(coord)].unknown_47b7e0() || LinkedTo->Kind_Of() == 15) {
            int damage = LinkedTo->unknown_slot32()->MaxStrength;
            LinkedTo->unknown_slot86(&damage, 0, Rules->unknown_c74, 0, true, 0);
        } else {
            LinkedTo->unknown_325 = true;
            LinkedTo->unknown_slot210();
        }
    }
}
