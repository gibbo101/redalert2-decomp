// Channel test of a game mode 4 session (false in any other mode).
#include "shared/wol_sink.hpp"
#include "shared/session_state.hpp"
// @ref ?unknown_game_channel_b299c0@@3UChannel@WOL@@A=00b299c0

// 0x0073C400: the channel's flag bit 12.
bool __fastcall Unknown_0073c400(WOL::Channel const *channel)
{
    if (unknown_session_a3d298.Type != 4) return false;
    return (channel->unknown_20 >> 12) & 1;
}
