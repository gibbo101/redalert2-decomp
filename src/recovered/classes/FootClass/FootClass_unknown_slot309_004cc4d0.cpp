// bool FootClass::unknown_slot309(AbstractClass *target) (0x004CC4D0)
// Whether the cell of a target is free for this unit: the unit itself or
// its radio contact may be there, and for a Spawned type an object that
// carries spawns (+0x238) or is Spawned; an empty cell must pass the cell
// test 0x00478760 and no other landed aircraft may be heading for the same
// target.
#include "shared/foot.hpp"
#include "shared/building_type.hpp"
#include "shared/building_type.hpp"
#include "shared/aircraft.hpp"
#include "shared/techno_type.hpp"
#include "shared/map_view.hpp"
// @ref ?Map@@3VMouseClass@@A=008324e0
// @ref ?Unknown_00471660@UnknownCellClass@@QAEPAVTechnoClass@@ABUPoint2D@@HH@Z=00471660
// @ref ?Unknown_00478760@UnknownCellClass@@QAE_NHHHHHHH@Z=00478760
// @ref ?Contact_With_Whom@RadioClass@@QBEPAVTechnoClass@@H@Z=00636e20

bool FootClass::unknown_slot309(AbstractClass *target)
{
    if (target == 0) {
        return false;
    }
    Cell cell = Coord_Cell(target->Center_Coord());
    if (!Map.Unknown_0055A660(cell, true)) {
        return false;
    }
    TechnoClass *techno = ((UnknownCellClass *)&Map[cell])->Unknown_00471660(Point2D(0, 0), 0, 0);
    if (techno != 0) {
        if (this != techno && Contact_With_Whom(0) != techno) {
            if (!unknown_slot32()->Spawned || (techno->unknown_238 == 0 && !techno->unknown_slot32()->Spawned)) {
                return false;
            }
        }
    } else {
        if (!((UnknownCellClass *)&Map[cell])->Unknown_00478760(1, 0, 0, -1, 0, -1, 1)) {
            return false;
        }
        for (int index = 0; index < Aircraft.Count(); index++) {
            AircraftClass *aircraft = Aircraft[index];
            if (aircraft->unknown_7d && !aircraft->unknown_76 && aircraft->unknown_494 == target && aircraft != this) {
                return false;
            }
        }
    }
    return true;
}
