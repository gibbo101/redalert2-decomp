// int IPXManagerClass::Send_Global_Message(void *buf, int buflen, int ack_req, IPXAddressClass *address, unsigned short id, unsigned long packet_id) (0x00525830)
// Sends on the global channel (never acknowledged when broadcast or
// unaddressed); counts and reports overflows.
#include "shared/ipx_manager.hpp"
// @ref ?Debug_Printf@@YAXPBDZZ=004068f0
// @ref ?Is_Broadcast@IPXAddressClass@@QAEHXZ=00523560
// @ref ??_C@_0BC@EBI@Send?5overflow?5?$CFd?6?$AA@=007ddfac

int IPXManagerClass::Send_Global_Message(void *buf, int buflen, int ack_req, IPXAddressClass *address, unsigned short id, unsigned long packet_id)
{
    if (!IPXStatus || !Listening) {
        return 0;
    }
    if (ack_req && (!address || address->Is_Broadcast())) {
        ack_req = 0;
    }
    int rc = GlobalChannel->Send_Packet(buf, buflen, address, ack_req, id, packet_id);
    if (!rc) {
        SendOverflows++;
        Debug_Printf("Send overflow %d\n", SendOverflows);
    }
    return rc;
}
