// MissionControlClass *MissionClass::Control() const (0x005950D0): the current mission's table entry.
#include "shared/mission.hpp"

MissionControlClass *MissionClass::Control() const
{
    return &MissionControl[Mission];
}
