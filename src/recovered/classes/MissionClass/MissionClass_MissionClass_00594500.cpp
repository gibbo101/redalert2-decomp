// MissionClass::MissionClass() (0x00594500)
// No mission, nothing queued or suspended; the timer starts now.
#include "shared/mission.hpp"
// @ref ??_7MissionClass@@6BIPersistStream@@@=007a6200
// @ref ??0ObjectClass@@QAE@XZ=005d22e0
// @ref ??_7MissionClass@@6BIRTTITypeInfo@@@=007a61e4
// @ref ??_7MissionClass@@6BINoticeSink@@@=007a61dc
// @ref ??_7MissionClass@@6BINoticeSource@@@=007a61d4
// @ref ?Frame@@3HA=00a40d2c

MissionClass::MissionClass() :
    Mission(-1),
    SuspendedMission(-1),
    MissionQueue(-1),
    unknown_a4(false),
    unknown_a8(0),
    unknown_ac(0)
{
}
// @ref ?AI@MissionClass@@UAEXXZ=00594790
