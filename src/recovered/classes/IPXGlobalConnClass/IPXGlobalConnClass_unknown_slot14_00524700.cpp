// int IPXGlobalConnClass::unknown_slot14(int index, void *buf, int *buflen, IPXAddressClass *address, unsigned short *product_id, unsigned long *packet_id) (0x00524700, slot 14)
// Reads the index'th received packet if unread, without marking it read.
#include "shared/ipx_global_conn.hpp"
// @ref ?Get_Receive@CommBufferClass@@QAEPAUReceiveQueueType@@H@Z=004809c0

int IPXGlobalConnClass::unknown_slot14(int index, void *buf, int *buflen, IPXAddressClass *address, unsigned short *product_id, unsigned long *packet_id)
{
    if (Queue->ReceiveCount < index) {
        return 0;
    }
    ReceiveQueueType *rec = Queue->Get_Receive(index);
    if (rec == 0 || rec->IsRead) {
        return 0;
    }
    GlobalHeaderType *packet = (GlobalHeaderType *)rec->Buffer;
    int packetlen = rec->BufLen - sizeof(GlobalHeaderType);
    if (packetlen > 0) {
        memcpy(buf, rec->Buffer + sizeof(GlobalHeaderType), packetlen);
    }
    *buflen = packetlen;
    *product_id = packet->ProductID;
    *address = *((IPXAddressClass *)rec->ExtraBuffer);
    if (packet_id) {
        *packet_id = packet->PacketID;
    }
    return 1;
}
