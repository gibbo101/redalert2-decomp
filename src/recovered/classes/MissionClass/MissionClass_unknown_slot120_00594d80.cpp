// bool MissionClass::unknown_slot120() (0x00594D80, slot 120): resumes the suspended mission.
#include "shared/mission.hpp"

bool MissionClass::unknown_slot120()
{
    if (SuspendedMission != -1) {
        Mission = SuspendedMission;
        SuspendedMission = -1;
        unknown_a4 = false;
        return true;
    }
    return false;
}
