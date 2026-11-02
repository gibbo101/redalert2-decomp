// unsigned short FirewallSettings::Get_Next_Port(int step) (0x005B9F10): advances the port pool by step
// (1 when 0), wrapping past 0xFFFF to 0x800, and returns the new port once the UDP transport can open a
// spare socket on it (the socket is closed again); outside internet games, or after 256 tries, the port
// is returned untested. The shared return is the loop body's last statement and the failed open
// continues to the counter test, which leaves the exhausted path its own epilogue (jne top; ret).
#include "shared/firewall_settings.hpp"
#include "shared/winsock_interface.hpp"
#include "shared/udp_interface.hpp"
#include "shared/unknown_globals.hpp"
// @ref ?PacketTransport@@3PAVWinsockInterfaceClass@@A=00839c50

unsigned short FirewallSettings::Get_Next_Port(int step)
{
    if (step == 0) {
        step = 1;
    }
    int tries = 0xFF;
    unsigned short port;
    do {
        PortPool += step;
        port = (unsigned short)PortPool;
        if (PortPool > 0xFFFF) {
            PortPool = 0x800;
        }
        if (PacketTransport && unknown_game_mode_a3d298 == 4) {
            if (!((UDPInterfaceClass *)PacketTransport)->Open_Spare_Socket(port)) {
                continue;
            }
            ((UDPInterfaceClass *)PacketTransport)->Close_Spare_Socket(port);
        }
        return port;
    } while (tries--);
    return port;
}
