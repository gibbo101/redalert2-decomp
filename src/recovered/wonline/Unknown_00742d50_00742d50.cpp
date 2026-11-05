// bool Unknown_00742d50() (0x00742D50)
// Runs 0x007424C0 on the chosen IRC server (unknown_irc_index_b292d8) when it is a valid index above 0.
#include "shared/wol_sink.hpp"
// @ref ?Unknown_007424c0@@YI_NPAUServer@WOL@@@Z=007424c0
// @ref ?unknown_irc_index_b292d8=00b292d8

bool Unknown_00742d50()
{
    if (unknown_irc_index_b292d8 >= 1 && unknown_irc_index_b292d8 < unknown_servers_b2a700.length()) {
        WOL::Server *server = 0;
        unknown_servers_b2a700.Get(server, unknown_irc_index_b292d8);
        return Unknown_007424c0(server);
    }
    return false;
}
