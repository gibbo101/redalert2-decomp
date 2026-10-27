// CommBufferClass::~CommBufferClass() (0x004801D0)
// Frees every entry's buffers, both queues and their index tables.
#include "shared/comm_buffer.hpp"
// @ref ??3@YAXPAX@Z=00781d3b

CommBufferClass::~CommBufferClass()
{
    int index;
    for (index = 0; index < MaxSend; index++) {
        delete[] SendQueue[index].Buffer;
        if (SendQueue[index].ExtraBuffer) {
            delete[] SendQueue[index].ExtraBuffer;
        }
    }
    for (index = 0; index < MaxReceive; index++) {
        delete[] ReceiveQueue[index].Buffer;
        if (ReceiveQueue[index].ExtraBuffer) {
            delete[] ReceiveQueue[index].ExtraBuffer;
        }
    }
    delete[] SendQueue;
    delete[] ReceiveQueue;
    delete[] SendIndex;
    delete[] ReceiveIndex;
}
