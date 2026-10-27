// int MissionClass::unknown_slot91() (0x00594770, slot 91): the mission, or the queued one.
#include "shared/mission.hpp"

int MissionClass::unknown_slot91()
{
    if (Mission == -1) {
        return MissionQueue;
    }
    return Mission;
}
