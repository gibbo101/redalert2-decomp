// int IPXManagerClass::Get_Global_Message(void *buf, int *buflen, IPXAddressClass *address, unsigned short *product_id) (0x00525AB0)
#include "shared/ipx_manager.hpp"

int IPXManagerClass::Get_Global_Message(void *buf, int *buflen, IPXAddressClass *address, unsigned short *product_id)
{
    if (!IPXStatus || !Listening) {
        return 0;
    }
    return GlobalChannel->Get_Packet(buf, buflen, address, product_id);
}
