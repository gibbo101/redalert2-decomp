// void Shutdown_Network_005bc4d0() (0x005BC4D0)
#include "shared/lobby.hpp"
#include "shared/winsock_interface.hpp"

void Shutdown_Network_005bc4d0()
{
    Unknown_Free_Lobby_Entries_005c8950();
    unknown_host_name_a3f618[0] = 0;
    if (PacketTransport != 0) {
        delete PacketTransport;
    }
    PacketTransport = 0;
}
