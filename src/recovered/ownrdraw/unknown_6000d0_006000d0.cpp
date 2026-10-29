// @ref ?Unknown_005B5EE0@@YAXXZ=005b5ee0
// @ref ?unknown_game_mode_a3d298@@3HA=00a3d298
// @ref ?unknown_session_a3f616@@3_NA=00a3f616
// @ref ?unknown_counter_a3fabc@@3HA=00a3fabc
// @ref ?unknown_53f460@@YA_NXZ=0053f460
// @ref ?unknown_53fbd0@@YA_NXZ=0053fbd0
// @ref ?Service_Game_IO_00481fb0@@YIXXZ=00481fb0
#include "shared/keyboard.hpp"
#include "shared/unknown_globals.hpp"
#include "shared/lobby.hpp"
#include "shared/owner_draw_dialog_control.hpp"
#include "shared/ms_message_box.hpp"

// Services the game for a modal dialog loop (0x006000D0).
bool unknown_6000d0()
{
    Unknown_005B5EE0();
    if (unknown_game_mode_a3d298 == 0 || unknown_game_mode_a3d298 == 5 || unknown_session_a3f616 ||
        unknown_counter_a3fabc != 0) {
        Service_Game_IO_00481fb0();
        return false;
    }
    if (!unknown_53f460() && unknown_53fbd0()) {
        return true;
    }
    return false;
}
