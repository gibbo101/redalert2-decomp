// void MissionClass::unknown_slot118(int mission) (0x00594710, slot 118)
// Sets the mission (not over mission 28 to 5), clears the queue and
// restarts the mission timer.
#include "shared/mission.hpp"

void MissionClass::unknown_slot118(int mission)
{
    if (Mission == 28 && mission == 5) {
        return;
    }
    Mission = mission;
    MissionQueue = -1;
    unknown_a4 = false;
    unknown_a8 = 0;
    unknown_ac = Frame;
    Timer = CDTimerClass<FrameTimerClass>(0);
}
