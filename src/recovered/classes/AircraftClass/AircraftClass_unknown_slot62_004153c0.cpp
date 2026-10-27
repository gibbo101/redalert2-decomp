// int AircraftClass::unknown_slot62(TechnoClass *techno) (0x004153C0, slot 62)
// Puts techno down next to the aircraft: tries the facings in table order
// for a cell slot 101 accepts (techno's), then has techno take the spot
// (slot 53) facing that way. On success techno gets mission 2 and the cell
// as target, and the aircraft radios it (message 2; 9 to the contact when
// that answers 1). Returns whether techno was placed.
#include "shared/aircraft.hpp"
#include "shared/map_view.hpp"
// @ref ?Map@@3VMouseClass@@A=008324e0
// @ref ?AdjacentCell@@3QBVCell@@B=00851a70
// @ref ?unknown_facings_7ce4a8@@3QBHB=007ce4a8

int AircraftClass::unknown_slot62(TechnoClass *techno)
{
    Cell cell(0, 0);
    int index;
    for (index = 0; index < 8; index++) {
        cell = Adjacent_Cell(unknown_slot104(), unknown_facings_7ce4a8[index]);
        if (techno->unknown_slot101(&Map[cell], -1, -1, 0, 1) == 0) {
            break;
        }
    }
    UnknownFacingDir dir = Facing_Dir(unknown_facings_7ce4a8[index]);
    CoordStruct coord = Coord;
    if (techno->unknown_slot53(&coord, Dir_To_256(dir))) {
        techno->unknown_slot116(2, false);
        techno->unknown_slot260((AbstractClass *)&Map[cell], 1);
        if (unknown_slot150(2, techno) == 1) {
            unknown_slot149(9);
        }
        return 1;
    }
    return 0;
}
