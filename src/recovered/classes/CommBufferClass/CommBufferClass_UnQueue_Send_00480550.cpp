// int CommBufferClass::UnQueue_Send(void *buf, int *buflen, int index, void *extrabuf, int *extralen, unsigned short *id) (0x00480550)
// Copies out (when asked) and frees the index'th packet in send order,
// closing the gap in the order; 0 when there is none.
#include "shared/comm_buffer.hpp"

int CommBufferClass::UnQueue_Send(void *buf, int *buflen, int index, void *extrabuf, int *extralen, unsigned short *id)
{
    if (SendCount == 0 || SendQueue[SendIndex[index]].IsActive == 0) {
        return 0;
    }
    if (buf != 0) {
        memcpy(buf, SendQueue[SendIndex[index]].Buffer, SendQueue[SendIndex[index]].BufLen);
        *buflen = SendQueue[SendIndex[index]].BufLen;
    }
    if (extrabuf != 0 && extralen != 0) {
        memcpy(extrabuf, SendQueue[SendIndex[index]].ExtraBuffer, SendQueue[SendIndex[index]].ExtraLen);
        *extralen = SendQueue[SendIndex[index]].ExtraLen;
    }
    if (id != 0) {
        *id = SendQueue[SendIndex[index]].unknown_20;
    }
    SendQueue[SendIndex[index]].IsActive = 0;
    SendQueue[SendIndex[index]].IsACK = 0;
    SendQueue[SendIndex[index]].unknown_bit2 = 0;
    SendQueue[SendIndex[index]].FirstTime = 0;
    SendQueue[SendIndex[index]].LastTime = 0;
    SendQueue[SendIndex[index]].SendCount = 0;
    SendQueue[SendIndex[index]].BufLen = 0;
    SendQueue[SendIndex[index]].ExtraLen = 0;
    SendQueue[SendIndex[index]].unknown_20 = 0;
    for (int i = index; i < SendCount - 1; i++) {
        SendIndex[i] = SendIndex[i + 1];
    }
    SendIndex[SendCount - 1] = 0;
    SendCount--;
    return 1;
}
