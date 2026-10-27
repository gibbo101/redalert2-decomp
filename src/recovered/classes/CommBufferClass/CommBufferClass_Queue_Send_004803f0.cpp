// int CommBufferClass::Queue_Send(void *buf, int buflen, void *extrabuf, int extralen, unsigned short id) (0x004803F0)
// Copies a packet (and its extra data) into a free send entry and appends
// it to the send order; 0 when full or too long.
#include "shared/comm_buffer.hpp"
// @ref ?Debug_Printf@@YAXPBDZZ=004068f0
// @ref ??_C@_0CE@DDIM@Queue_Send?5?9?5No?5room?5in?5send?5que@=007d3074
// @ref ??_C@_0CE@GELF@buflen?5?$DO?5MaxPacketSize?5by?5?$CFd?5byt@=007d3050

int CommBufferClass::Queue_Send(void *buf, int buflen, void *extrabuf, int extralen, unsigned short id)
{
    if (SendCount == MaxSend || buflen > MaxPacketSize) {
        if (SendCount == MaxSend) {
            Debug_Printf("Queue_Send - No room in send queue\n");
        } else {
            Debug_Printf("buflen > MaxPacketSize by %d bytes\n", MaxPacketSize - buflen);
        }
        return 0;
    }
    int index = -1;
    for (int i = 0; i < MaxSend; i++) {
        if (SendQueue[i].IsActive == 0) {
            index = i;
            break;
        }
    }
    if (index == -1) {
        return 0;
    }
    SendQueue[index].IsActive = 1;
    SendQueue[index].IsACK = 0;
    SendQueue[index].unknown_bit2 = 0;
    SendQueue[index].FirstTime = 0;
    SendQueue[index].LastTime = 0;
    SendQueue[index].SendCount = 0;
    SendQueue[index].BufLen = buflen;
    SendQueue[index].unknown_20 = id;
    memcpy(SendQueue[index].Buffer, buf, buflen);
    if (extrabuf != 0 && extralen > 0 && extralen <= MaxExtraSize) {
        memcpy(SendQueue[index].ExtraBuffer, extrabuf, extralen);
        SendQueue[index].ExtraLen = extralen;
    } else {
        SendQueue[index].ExtraLen = 0;
    }
    SendIndex[SendCount] = index;
    SendCount++;
    SendTotal++;
    return 1;
}
