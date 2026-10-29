// void Unknown_005c3ae0() (0x005C3AE0)
// Sends every other player a global packet 0x28 with the local nick name, serving the game I/O after each.
#include "shared/lobby.hpp"
#include "shared/ipx_manager.hpp"

void Unknown_005c3ae0()
{
    UnknownGlobalPacket packet;
    memset(&packet, 0, sizeof(packet));
    packet.Command = 0x28;
    strcpy(packet.Name, unknown_name_a3d3a0);
    int count = unknown_players_a3fa7c.Count();
    for (int i = 1; i < count; i++) {
        unknown_ipx_manager_a40978.Send_Global_Message(&packet, sizeof(packet), 1, &unknown_players_a3fa7c[i]->Address, 0, 0);
        Service_Game_IO_00481fb0();
    }
}
