// int IPXManagerClass::unknown_525af0(int index, void *buf, int *buflen, IPXAddressClass *address, unsigned short *product_id, unsigned long *packet_id) (0x00525AF0)
// Reads a global packet without marking it (IPXGlobalConnClass slot 14).
#include "shared/ipx_manager.hpp"

int IPXManagerClass::unknown_525af0(int index, void *buf, int *buflen, IPXAddressClass *address, unsigned short *product_id, unsigned long *packet_id)
{
    if (!IPXStatus || !Listening) {
        return 0;
    }
    return GlobalChannel->unknown_slot14(index, buf, buflen, address, product_id, packet_id);
}
