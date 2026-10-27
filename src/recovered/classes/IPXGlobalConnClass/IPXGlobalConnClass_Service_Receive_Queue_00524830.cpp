// int IPXGlobalConnClass::Service_Receive_Queue() (0x00524830, slot 8)
// Drops every packet already read.
#include "shared/ipx_global_conn.hpp"
// @ref ?Get_Receive@CommBufferClass@@QAEPAUReceiveQueueType@@H@Z=004809c0
// @ref ?UnQueue_Receive@CommBufferClass@@QAEHPAXPAHH01@Z=00480870

int IPXGlobalConnClass::Service_Receive_Queue()
{
    for (int i = 0; i < Queue->ReceiveCount; i++) {
        if (Queue->Get_Receive(i)->IsRead) {
            Queue->UnQueue_Receive(0, 0, i, 0, 0);
            i--;
        }
    }
    return 1;
}
