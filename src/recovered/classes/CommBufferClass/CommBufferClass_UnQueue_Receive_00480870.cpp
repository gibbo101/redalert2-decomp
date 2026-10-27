// int CommBufferClass::UnQueue_Receive(void *buf, int *buflen, int index, void *extrabuf, int *extralen) (0x00480870)
// Copies out (when asked) and frees the index'th packet in receive order,
// closing the gap in the order; 0 when there is none.
#include "shared/comm_buffer.hpp"

int CommBufferClass::UnQueue_Receive(void *buf, int *buflen, int index, void *extrabuf, int *extralen)
{
    if (ReceiveCount == 0 || ReceiveQueue[ReceiveIndex[index]].IsActive == 0) {
        return 0;
    }
    if (buf != 0) {
        memcpy(buf, ReceiveQueue[ReceiveIndex[index]].Buffer, ReceiveQueue[ReceiveIndex[index]].BufLen);
        *buflen = ReceiveQueue[ReceiveIndex[index]].BufLen;
    }
    if (extrabuf != 0 && extralen != 0) {
        memcpy(extrabuf, ReceiveQueue[ReceiveIndex[index]].ExtraBuffer, ReceiveQueue[ReceiveIndex[index]].ExtraLen);
        *extralen = ReceiveQueue[ReceiveIndex[index]].ExtraLen;
    }
    ReceiveQueue[ReceiveIndex[index]].IsActive = 0;
    ReceiveQueue[ReceiveIndex[index]].IsRead = 0;
    ReceiveQueue[ReceiveIndex[index]].IsACK = 0;
    ReceiveQueue[ReceiveIndex[index]].BufLen = 0;
    ReceiveQueue[ReceiveIndex[index]].ExtraLen = 0;
    for (int i = index; i < ReceiveCount - 1; i++) {
        ReceiveIndex[i] = ReceiveIndex[i + 1];
    }
    ReceiveIndex[ReceiveCount - 1] = 0;
    ReceiveCount--;
    return 1;
}
