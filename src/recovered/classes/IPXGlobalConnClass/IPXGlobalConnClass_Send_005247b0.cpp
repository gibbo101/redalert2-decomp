// int IPXGlobalConnClass::Send(char *buf, int buflen, void *extrabuf, int extralen, bool flagged, unsigned short id) (0x005247B0, slot 9)
// Sends to the address carried as the packet's extra data: broadcast, to
// the bridge node when it is on the bridged network, or directly.
#include "shared/ipx_global_conn.hpp"
// @ref ?Is_Broadcast@IPXAddressClass@@QAEHXZ=00523560
// @ref ?Broadcast@IPXConnClass@@SIHPADH@Z=00523f70
// @ref ?unknown_game_mode_a3d298@@3HA=00a3d298

int IPXGlobalConnClass::Send(char *buf, int buflen, void *extrabuf, int extralen, bool flagged, unsigned short id)
{
    IPXAddressClass *address = (IPXAddressClass *)extrabuf;
    if (address->Is_Broadcast()) {
        return Broadcast(buf, buflen);
    }
    if (unknown_game_mode_a3d298 == 3 && IsBridge && !memcmp(address, BridgeNet, 4)) {
        return Send_To(buf, buflen, address, BridgeNode, flagged, 0);
    }
    return Send_To(buf, buflen, address, 0, flagged, id);
}
