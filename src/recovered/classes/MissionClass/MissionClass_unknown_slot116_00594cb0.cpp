// void MissionClass::unknown_slot116(int mission, bool commence) (0x00594CB0, slot 116)
// Queues a mission (not over missions 28/5 and 19) and optionally starts it.
#include "shared/mission.hpp"

void MissionClass::unknown_slot116(int mission, bool commence)
{
    if (Mission == 28 && mission == 5) {
        return;
    }
    if (Mission == 19) {
        return;
    }
    if (mission != -1 && (Mission != mission || (MissionQueue != mission && MissionQueue != -1))) {
        MissionQueue = mission;
        unknown_a4 = false;
    }
    if (commence && unknown_slot122()) {
        unknown_slot117();
    }
}
