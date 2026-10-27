// void IPXGlobalConnClass::unknown_slot15(int index) (0x00524790, slot 15)
// Marks the index'th received packet read.
#include "shared/ipx_global_conn.hpp"
// @ref ?Get_Receive@CommBufferClass@@QAEPAUReceiveQueueType@@H@Z=004809c0

void IPXGlobalConnClass::unknown_slot15(int index)
{
    if (index < Queue->ReceiveCount) {
        Queue->Get_Receive(index)->IsRead = 1;
    }
}
