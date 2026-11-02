// bool __cdecl unknown_score_service_466a20() (0x00466A20)
// The score dialogs' idle service: the game mode's network service (modem 0x005BBD10,
// internet 0x0073E100), otherwise the plain game I/O service; false then.
#include "shared/campaign_score.hpp"
#include "shared/unknown_globals.hpp"
// @ref ?Unknown_005bbd10@@YA_NXZ=005bbd10
// @ref ?Unknown_0073e100@@YA_NXZ=0073e100
// @ref ?Service_Game_IO_00481fb0@@YIXXZ=00481fb0

bool Unknown_005bbd10();                                // 0x005BBD10 (shared/lobby.hpp)
bool Unknown_0073e100();                                // 0x0073E100 (shared/lobby.hpp)

bool unknown_score_service_466a20()
{
    if (unknown_game_mode_a3d298 == 3) {
        return Unknown_005bbd10();
    }
    if (unknown_game_mode_a3d298 == 4) {
        return Unknown_0073e100();
    }
    Service_Game_IO_00481fb0();
    return false;
}
