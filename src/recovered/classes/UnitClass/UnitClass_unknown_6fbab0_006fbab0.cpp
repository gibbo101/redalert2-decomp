// Checks mission 5 and the coordinate test before notifying the team and slots210/60.
#include "shared/unit.hpp"
#include "shared/team.hpp"
#include "shared/map_view.hpp"
bool UnitClass::unknown_6fbab0()
{
    if (unknown_slot91() == 5) {
        CoordStruct position = Coord;
        if (!Map.Unknown_0054AB00(position) && unknown_32d) {
            if (Team) {
                Team->TargetNotAssigned = true;
            }
            unknown_slot210();
            unknown_slot60();
            return true;
        }
    }
    return false;
}
