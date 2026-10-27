// int IPXManagerClass::unknown_525bc0(void *buf, int *buflen, IPXAddressClass *address, unsigned short *product_id) (0x00525BC0)
// Reads from the second global channel.
#include "shared/ipx_manager.hpp"

int IPXManagerClass::unknown_525bc0(void *buf, int *buflen, IPXAddressClass *address, unsigned short *product_id)
{
    if (!IPXStatus || !Listening) {
        return 0;
    }
    return unknown_4c->Get_Packet(buf, buflen, address, product_id);
}
