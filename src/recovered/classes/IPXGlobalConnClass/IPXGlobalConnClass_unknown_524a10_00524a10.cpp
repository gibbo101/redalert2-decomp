// void IPXGlobalConnClass::Set_Bridge(NetNumType bridge) (0x00524A10; Red Alert's Set_Bridge).
// Clears IsBridge once the IPX class is configured (the bridge network is unused under Winsock).
#include "shared/ipx_global_conn.hpp"
// @ref ?Configured@IPXConnClass@@2HA=00a52404

void IPXGlobalConnClass::Set_Bridge(NetNumType bridge)
{
    if (Configured) {
        IsBridge = 0;
    }
}
