// int ConnectionClass::Get_Packet(void *buf, int *buflen) (0x004812E0, slot 4)
// Reads the next unread packet: the next sequenced one in order, or any
// unsequenced one; copies its data (without the header) out.
#include "shared/connection.hpp"
// @ref ?Get_Receive@CommBufferClass@@QAEPAUReceiveQueueType@@H@Z=004809c0

int ConnectionClass::Get_Packet(void *buf, int *buflen)
{
    for (int i = 0; i < Queue->ReceiveCount; i++) {
        ReceiveQueueType *rec = Queue->Get_Receive(i);
        if (rec != 0 && !rec->IsRead) {
            CommHeaderType *packet = (CommHeaderType *)rec->Buffer;
            if (packet->Code == PACKET_DATA_ACK && packet->PacketID == LastReadID + 1) {
                LastReadID = packet->PacketID;
            } else if (packet->Code != PACKET_DATA_NOACK) {
                continue;
            }
            rec->IsRead = 1;
            int packetlen = rec->BufLen - sizeof(CommHeaderType);
            if (packetlen > 0) {
                memcpy(buf, rec->Buffer + sizeof(CommHeaderType), packetlen);
            }
            *buflen = packetlen;
            return 1;
        }
    }
    return 0;
}
