// int UnitClass::unknown_slot141() (0x00704B10, slot 141)
// The harvest step (hypothesis): looks for the rules' refinery type (slot
// 301); with one in reach asks it to dock (radio message 2) and on a roger
// queues mission 7; otherwise, unless the house owns such a building,
// gives up (slot 261). Answers the mission's delay in frames.
#include "shared/unit.hpp"
#include "shared/building_type.hpp"
// @ref ?Rules@@3PAVRulesClass@@A=00839848
// @ref ?unknown_func_491d10@UnknownHouseCounter@@QAEHH@Z=00491d10
// @ref ?Control@MissionClass@@QBEPAVMissionControlClass@@XZ=005950d0
// @ref __ftol=0077f110
// @ref __real@8@4008e100000000000000=0079b608

int UnitClass::unknown_slot141()
{
    TechnoClass *refinery = unknown_slot301(Rules->unknown_778, 0, 0);
    unknown_5ba = false;
    if (!refinery) {
        if (!House->unknown_5420.unknown_func_491d10(Rules->unknown_778->ArrayIndex)) {
            unknown_slot261(0, 1);
        }
    } else if (unknown_slot150(2, refinery) == 1) {
        unknown_slot116(7, false);
        return 1;
    }
    return (int)(Control()->unknown_10 * 900.0);
}
