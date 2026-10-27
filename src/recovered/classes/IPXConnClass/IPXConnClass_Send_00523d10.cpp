// int IPXConnClass::Send(char *buf, int buflen, void *extrabuf, int extralen, bool flagged, unsigned short id) (0x00523D10, slot 9)
// Sends to this connection's address.
#include "shared/ipx_conn.hpp"

int IPXConnClass::Send(char *buf, int buflen, void *extrabuf, int extralen, bool flagged, unsigned short id)
{
    return Send_To(buf, buflen, &Address, 0, flagged, 0);
}
