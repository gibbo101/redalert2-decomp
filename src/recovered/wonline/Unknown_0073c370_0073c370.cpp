// Channel test of a game mode 4 session (false in any other mode).
#include "shared/wol_sink.hpp"
#include "shared/session_state.hpp"
// @ref ?unknown_game_channel_b299c0@@3UChannel@WOL@@A=00b299c0

// 0x0073C370: the same test of the current game channel.
bool Unknown_0073c370()
{
    return Unknown_0073c340(&unknown_game_channel_b299c0);
}
