// int MissionClass::Timer_Value() const (0x005950F0): the mission timer's remaining time.
#include "shared/mission.hpp"

int MissionClass::Timer_Value() const
{
    return Timer.Value();
}
