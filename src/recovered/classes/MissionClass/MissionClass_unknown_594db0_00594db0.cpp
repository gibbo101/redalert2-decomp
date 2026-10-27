// bool __fastcall MissionClass::unknown_594db0(int mission) (0x00594DB0): the mission table's flag +0x06 (true for -1).
#include "shared/mission.hpp"
// @ref ?MissionControl@@3PAVMissionControlClass@@A=00a403b0

bool __fastcall MissionClass::unknown_594db0(int mission)
{
    if (mission == -1) {
        return true;
    }
    return MissionControl[mission].unknown_06;
}
