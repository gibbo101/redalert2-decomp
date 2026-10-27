// void ConnectionClass::Init() (0x00480ED0, slot 1)
// Clears the counters and statistics and empties the queue.
#include "shared/connection.hpp"
// @ref ?Init@CommBufferClass@@QAEXXZ=00480280

void ConnectionClass::Init()
{
    NumRecNoAck = 0;
    NumRecAck = 0;
    NumSendNoAck = 0;
    NumSendAck = 0;
    unknown_08 = 0;
    unknown_0c = 0;
    unknown_10 = 0;
    unknown_14 = 0;
    unknown_18 = 0;
    LastSeqID = 0xFFFFFFFF;
    LastReadID = 0xFFFFFFFF;
    Queue->Init();
}
