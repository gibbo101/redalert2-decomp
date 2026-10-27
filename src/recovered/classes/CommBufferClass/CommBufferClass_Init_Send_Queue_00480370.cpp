// void CommBufferClass::Init_Send_Queue() (0x00480370)
// Empties the send queue.
#include "shared/comm_buffer.hpp"

void CommBufferClass::Init_Send_Queue()
{
    SendCount = 0;
    for (int index = 0; index < MaxSend; index++) {
        SendQueue[index].IsActive = 0;
        SendQueue[index].IsACK = 0;
        SendQueue[index].unknown_bit2 = 0;
        SendQueue[index].FirstTime = 0;
        SendQueue[index].LastTime = 0;
        SendQueue[index].SendCount = 0;
        SendQueue[index].BufLen = 0;
        SendQueue[index].ExtraLen = 0;
        SendQueue[index].unknown_20 = 0;
        SendIndex[index] = 0;
    }
}
