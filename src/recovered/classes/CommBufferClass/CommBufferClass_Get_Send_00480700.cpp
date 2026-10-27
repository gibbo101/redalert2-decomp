// SendQueueType *CommBufferClass::Get_Send(int index) (0x00480700)
// The index'th packet in send order, or null when that entry is free.
#include "shared/comm_buffer.hpp"

SendQueueType *CommBufferClass::Get_Send(int index)
{
    if (SendQueue[SendIndex[index]].IsActive == 0) {
        return 0;
    }
    return &SendQueue[SendIndex[index]];
}
