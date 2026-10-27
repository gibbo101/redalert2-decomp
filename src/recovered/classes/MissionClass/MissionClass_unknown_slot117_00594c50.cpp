// bool MissionClass::unknown_slot117() (0x00594C50, slot 117)
// Starts the queued mission; false when nothing is queued.
#include "shared/mission.hpp"

bool MissionClass::unknown_slot117()
{
    if (MissionQueue != -1) {
        Mission = MissionQueue;
        MissionQueue = -1;
        Timer = CDTimerClass<FrameTimerClass>(0);
        unknown_a8 = 0;
        unknown_ac = Frame;
        unknown_a4 = false;
        return true;
    }
    return false;
}
