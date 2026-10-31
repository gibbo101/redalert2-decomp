#include "shared/lobby.hpp"
#include "shared/netdlg.hpp"
#include "shared/winsock_interface.hpp"

// Red Alert's Shutdown_Network as NetDlg.CPP has it (0x005BB5A0; netdlg2.cpp's copy 0x005BC4D0 also
// frees the lobby entries).
void Shutdown_Network_005bb5a0()
{
    unknown_host_name_a3f618[0] = 0;
    if (PacketTransport != 0) {
        delete PacketTransport;
    }
    PacketTransport = 0;
}
