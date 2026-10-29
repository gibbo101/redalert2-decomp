// MultiplayerGameMode *Current_Game_Mode_005c34d0() (0x005C34D0)
// The session's game mode object (session +0x18), or the first registered mode when there is none.
#include "shared/lobby.hpp"
#include "shared/multiplayer_game_mode.hpp"

MultiplayerGameMode *Current_Game_Mode_005c34d0()
{
    MultiplayerGameMode *mode = MultiplayerGameMode::unknown_find_mode_5b6fe0(unknown_session_a3d298.GameModeIndex);
    if (mode == 0) {
        return MultiplayerGameMode::unknown_first_mode_5b6ec0();
    }
    return mode;
}
