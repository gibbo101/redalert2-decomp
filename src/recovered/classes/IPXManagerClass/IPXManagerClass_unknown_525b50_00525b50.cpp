// int IPXManagerClass::unknown_525b50(void *buf, int buflen, bool ack_req) (0x00525B50)
// Sends on the second global channel to its own address; counts overflows.
#include "shared/ipx_manager.hpp"
// @ref ?Debug_Printf@@YAXPBDZZ=004068f0
// @ref ??_C@_0BC@EBI@Send?5overflow?5?$CFd?6?$AA@=007ddfac

int IPXManagerClass::unknown_525b50(void *buf, int buflen, bool ack_req)
{
    if (!IPXStatus || !Listening || !unknown_4c) {
        return 0;
    }
    int rc = unknown_4c->Send_Packet(buf, buflen, &unknown_4c->Address, ack_req, 0, 0);
    if (!rc) {
        SendOverflows++;
        Debug_Printf("Send overflow %d\n", SendOverflows);
    }
    return rc;
}
