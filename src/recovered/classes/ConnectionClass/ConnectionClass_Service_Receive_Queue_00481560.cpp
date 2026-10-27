// int ConnectionClass::Service_Receive_Queue() (0x00481560, slot 8)
// Drops packets already read that are unsequenced or older than the
// in-order sequence.
#include "shared/connection.hpp"
// @ref ?Get_Receive@CommBufferClass@@QAEPAUReceiveQueueType@@H@Z=004809c0
// @ref ?UnQueue_Receive@CommBufferClass@@QAEHPAXPAHH01@Z=00480870

int ConnectionClass::Service_Receive_Queue()
{
    for (int i = 0; i < Queue->ReceiveCount; i++) {
        ReceiveQueueType *rec = Queue->Get_Receive(i);
        if (rec->IsRead) {
            if (((CommHeaderType *)rec->Buffer)->Code == PACKET_DATA_NOACK
                || ((CommHeaderType *)rec->Buffer)->PacketID < LastSeqID) {
                Queue->UnQueue_Receive(0, 0, i, 0, 0);
                i--;
            }
        }
    }
    return 1;
}
