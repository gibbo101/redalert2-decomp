// int IPXGlobalConnClass::Get_Packet(void *buf, int *buflen, IPXAddressClass *address, unsigned short *product_id) (0x00524670, slot 13)
// Reads the first received packet if unread: its data, product ID and
// sender address.
#include "shared/ipx_global_conn.hpp"
// @ref ?Get_Receive@CommBufferClass@@QAEPAUReceiveQueueType@@H@Z=004809c0

int IPXGlobalConnClass::Get_Packet(void *buf, int *buflen, IPXAddressClass *address, unsigned short *product_id)
{
    if (Queue->ReceiveCount == 0) {
        return 0;
    }
    ReceiveQueueType *rec = Queue->Get_Receive(0);
    if (rec == 0 || rec->IsRead) {
        return 0;
    }
    GlobalHeaderType *packet = (GlobalHeaderType *)rec->Buffer;
    rec->IsRead = 1;
    int packetlen = rec->BufLen - sizeof(GlobalHeaderType);
    if (packetlen > 0) {
        memcpy(buf, rec->Buffer + sizeof(GlobalHeaderType), packetlen);
    }
    *buflen = packetlen;
    *product_id = packet->ProductID;
    *address = *((IPXAddressClass *)rec->ExtraBuffer);
    return 1;
}
