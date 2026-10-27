// int IPXConnClass::Stop_Listening() (0x00523CF0)
#include "shared/ipx_conn.hpp"
// @ref ?Listening@IPXConnClass@@2HA=00a5240c
// @ref ?PacketTransport@@3PAVWinsockInterfaceClass@@A=00839c50

int IPXConnClass::Stop_Listening()
{
    if (PacketTransport) {
        PacketTransport->Stop_Listening();
    }
    Listening = 0;
    return 1;
}
