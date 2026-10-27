// CommBufferClass::CommBufferClass(int numsend, int numreceive, int maxlen, int extralen) (0x004800C0)
// Allocates both queues, their index tables and a packet (and extra) buffer
// per entry, then clears everything.
#include "shared/comm_buffer.hpp"
// @ref ??_7CommBufferClass@@6B@=0079ddb4
// @ref ??2@YAPAXI@Z=00782017
// @ref ?Init@CommBufferClass@@QAEXXZ=00480280

CommBufferClass::CommBufferClass(int numsend, int numreceive, int maxlen, int extralen)
{
    MaxSend = numsend;
    MaxReceive = numreceive;
    MaxPacketSize = maxlen;
    MaxExtraSize = extralen;
    SendQueue = new SendQueueType[numsend];
    ReceiveQueue = new ReceiveQueueType[numreceive];
    SendIndex = new int[numsend];
    ReceiveIndex = new int[numreceive];
    int index;
    for (index = 0; index < MaxSend; index++) {
        SendQueue[index].Buffer = new char[maxlen];
        if (MaxExtraSize > 0) {
            SendQueue[index].ExtraBuffer = new char[MaxExtraSize];
        } else {
            SendQueue[index].ExtraBuffer = 0;
        }
    }
    for (index = 0; index < MaxReceive; index++) {
        ReceiveQueue[index].Buffer = new char[maxlen];
        if (MaxExtraSize > 0) {
            ReceiveQueue[index].ExtraBuffer = new char[MaxExtraSize];
        } else {
            ReceiveQueue[index].ExtraBuffer = 0;
        }
    }
    Init();
}
