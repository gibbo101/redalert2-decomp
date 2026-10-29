// Channel test of a game mode 4 session (false in any other mode).
#include "shared/wol_sink.hpp"
#include "shared/session_state.hpp"
// @ref ?unknown_game_channel_b299c0@@3UChannel@WOL@@A=00b299c0

// 0x0073C3A0: flag bit 8 of the current game channel.
bool Unknown_0073c3a0()
{
    return Unknown_0073c3c0(&unknown_game_channel_b299c0);
}
