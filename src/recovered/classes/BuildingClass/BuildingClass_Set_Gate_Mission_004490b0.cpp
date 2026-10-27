// Set the gate animation state and mission; the second stack argument is unused.
#include "shared/building.hpp"
#include "shared/gscreen.hpp"
// @ref _unknown_flag_a40d13=00a40d13
// @ref _unknown_a40774=00a40774
// @ref ?unknown_443d60@BuildingClass@@=00443d60
bool BuildingClass::unknown_slot261(bool opening, bool arg2)
{
    int mission;
    if(opening && !unknown_a40774 && !unknown_flag_a40d13) {
        unknown_443d60(false);
        mission=18;
    } else {
        unknown_443d60(true);
        mission=5;
    }
    unknown_slot116(mission,false);
    return false;
}
