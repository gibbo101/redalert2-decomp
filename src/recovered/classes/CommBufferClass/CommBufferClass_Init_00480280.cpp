// void CommBufferClass::Init() (0x00480280)
// Clears the counters, the delay statistics, every queue entry and index,
// and the debug configuration.
#include "shared/comm_buffer.hpp"

void CommBufferClass::Init()
{
    SendTotal = 0;
    ReceiveTotal = 0;
    DelaySum = 0;
    NumDelay = 0;
    MeanDelay = 0;
    MaxDelay = 0;
    SendCount = 0;
    ReceiveCount = 0;
    int index;
    for (index = 0; index < MaxSend; index++) {
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
    for (index = 0; index < MaxReceive; index++) {
        ReceiveQueue[index].IsActive = 0;
        ReceiveQueue[index].IsRead = 0;
        ReceiveQueue[index].IsACK = 0;
        ReceiveQueue[index].ReceiveTime = 0;
        ReceiveQueue[index].BufLen = 0;
        ReceiveQueue[index].ExtraLen = 0;
        ReceiveIndex[index] = 0;
    }
    DebugOffset = 0;
    DebugSize = 0;
    DebugNames = 0;
    DebugNameCount = 0;
}
