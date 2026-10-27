// Marks the team target state, or handles a teamless guard outside the map predicate (0x005070E0).
#include "shared/infantry.hpp"
#include "shared/map_view.hpp"
// @ref ?Map@@3VMouseClass@@A=008324e0
// @ref ?Unknown_0054AB00@MapClass@@QAE_NABUCoordStruct@@@Z=0054ab00
// Complete independently decoded body through RET 0x0050716C: 141 bytes.
// Inventory 0x0050711C is inside a displacement, not a separate entry.
bool InfantryClass::unknown_5070e0()
{
    if (Team != 0 && unknown_32d) {
        Team->TargetNotAssigned = true;
    }
    if (Team == 0 && unknown_slot91() == 5) {
        CoordStruct coord = Coord;
        if (!Map.Unknown_0054AB00(coord)) {
            unknown_slot210();
            unknown_slot60();
            return true;
        }
    }
    return false;
}

