// int CommBufferClass::Queue_Receive(void *buf, int buflen, void *extrabuf, int extralen) (0x00480730)
// Copies an incoming packet (and its extra data) into a free receive entry
// stamped with the tick time and appends it to the receive order.
#include "shared/comm_buffer.hpp"
// @ref ?Debug_Printf@@YAXPBDZZ=004068f0
// @ref ??_C@_0EC@DB@Can?8t?5queue?5incoming?5packet?5?9?5Un@=007d3098
// @ref ?TickCount@@3V?$TTimerClass@VSystemTimerClass@@@@A=00839980
// @ref ??BSystemTimerClass@@QBEJXZ=0069a430

int CommBufferClass::Queue_Receive(void *buf, int buflen, void *extrabuf, int extralen)
{
    if (ReceiveCount == MaxReceive || buflen > MaxPacketSize) {
        return 0;
    }
    int index = -1;
    for (int i = 0; i < MaxReceive; i++) {
        if (ReceiveQueue[i].IsActive == 0) {
            index = i;
            break;
        }
    }
    if (index == -1) {
        Debug_Printf("Can't queue incoming packet - Unable to find free slot in array.\n");
        return 0;
    }
    ReceiveQueue[index].IsActive = 1;
    ReceiveQueue[index].IsRead = 0;
    ReceiveQueue[index].IsACK = 0;
    ReceiveQueue[index].ReceiveTime = TickCount.Time();
    ReceiveQueue[index].BufLen = buflen;
    memcpy(ReceiveQueue[index].Buffer, buf, buflen);
    if (extrabuf != 0 && extralen > 0 && extralen <= MaxExtraSize) {
        memcpy(ReceiveQueue[index].ExtraBuffer, extrabuf, extralen);
        ReceiveQueue[index].ExtraLen = extralen;
    } else {
        ReceiveQueue[index].ExtraLen = 0;
    }
    ReceiveIndex[ReceiveCount] = index;
    ReceiveCount++;
    ReceiveTotal++;
    return 1;
}
