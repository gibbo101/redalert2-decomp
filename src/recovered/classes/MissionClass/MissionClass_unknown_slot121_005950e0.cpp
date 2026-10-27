// bool MissionClass::unknown_slot121() const (0x005950E0, slot 121): a mission is suspended.
#include "shared/mission.hpp"

bool MissionClass::unknown_slot121() const
{
    return SuspendedMission != -1;
}
