// ReceiveQueueType *CommBufferClass::Get_Receive(int index) (0x004809C0)
// The index'th packet in receive order, or null when that entry is free.
#include "shared/comm_buffer.hpp"

ReceiveQueueType *CommBufferClass::Get_Receive(int index)
{
    if (ReceiveQueue[ReceiveIndex[index]].IsActive == 0) {
        return 0;
    }
    return &ReceiveQueue[ReceiveIndex[index]];
}
