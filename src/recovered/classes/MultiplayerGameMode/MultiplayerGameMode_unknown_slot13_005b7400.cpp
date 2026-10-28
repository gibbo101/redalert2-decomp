// int MultiplayerGameMode::unknown_slot13() -- 0x005B7400
#include "shared/multi_mission.hpp"
// @ref ?unknown_multi_missions_a3d8d8@@3V?$DynamicVectorClass@PAVMultiMission@@@@A=00a3d8d8
// @ref ?Unknown_006720C0@MultiMission@@QAE_NXZ=006720c0
// @ref ?Unknown_006720E0@MultiMission@@QAE_NAAVWstring@@@Z=006720e0
// @ref ?unknown_73c370@@YA_NXZ=0073c370

int MultiplayerGameMode::unknown_slot13()
{
    int count = unknown_multi_missions_a3d8d8.Count();
    for (int index = 0; index < count; index++) {
        if (unknown_5b7470(unknown_multi_missions_a3d8d8[index])) {
            return index;
        }
    }
    return -1;
}
