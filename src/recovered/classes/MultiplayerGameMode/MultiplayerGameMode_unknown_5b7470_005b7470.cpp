// bool MultiplayerGameMode::unknown_5b7470(MultiMission *map) -- 0x005B7470
// A map with the fixed text at +0x58 follows slot 11; otherwise the map must
// allow this mode's name (unless +0x17C is clear and 0x0073C370 agrees).
#include "shared/multi_mission.hpp"
// @ref ?Unknown_006720C0@MultiMission@@QAE_NXZ=006720c0
// @ref ?Unknown_006720E0@MultiMission@@QAE_NAAVWstring@@@Z=006720e0
// @ref ?unknown_73c370@@YA_NXZ=0073c370

bool MultiplayerGameMode::unknown_5b7470(MultiMission *map)
{
    if (map->Unknown_006720C0()) {
        return unknown_slot11();
    }
    if (!map->unknown_17c && unknown_73c370()) {
        return false;
    }
    return map->Unknown_006720E0(unknown_30);
}
