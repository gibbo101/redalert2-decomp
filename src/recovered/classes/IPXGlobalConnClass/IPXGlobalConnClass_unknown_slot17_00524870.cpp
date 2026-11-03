// void IPXGlobalConnClass::unknown_slot17(unsigned long age) (0x00524870, slot 17)
// Strips received global packets older than AGE ticks from the receive queue
// and forgets their packet IDs in the duplicate ring (unknown_d0).
#include "shared/ipx_global_conn.hpp"
// @ref ??_C@_07GIJF@i?5?$DN?5?$CFd?6?$AA@=007ddec0
// @ref ??_C@_0BE@PLEB@Checking?5packet?5?$CFd?6?$AA@=007ddeac
// @ref ??_C@_0CC@HHEB@Done?5stripping?4?5Num?5receive?5?$DN?5?$CFd@=007dde24
// @ref ??_C@_0DA@NBJF@Leaving?5global?5packet?5due?5to?5age@=007dde48
// @ref ??_C@_0DC@DNOD@Stripping?5global?5packet?5due?5to?5a@=007dde78
// @ref ??_C@_0EB@BOPL@Stripping?5queue?5entries?5older?5th@=007ddec8
// @ref ?Get_Receive@CommBufferClass@@QAEPAUReceiveQueueType@@H@Z=004809c0
// @ref ?UnQueue_Receive@CommBufferClass@@QAEHPAXPAHH01@Z=00480870

void IPXGlobalConnClass::unknown_slot17(unsigned long age)
{
    Debug_Printf("Stripping queue entries older than %d seconds. Num receive = %d\n", age / 60, Queue->ReceiveCount);
    for (int i = 0; i < Queue->ReceiveCount; i++) {
        ReceiveQueueType *rec = Queue->Get_Receive(i);
        Debug_Printf("i = %d\n", i);
        if (rec) {
            Debug_Printf("Checking packet %d\n", i);
            unsigned long const &received = rec->ReceiveTime;
            if ((long)(received + age) < TickCount.Time()) {
                Debug_Printf("Stripping global packet due to age of %d seconds\n", (int)(TickCount.Time() - rec->ReceiveTime) / 60);
                unsigned long id = ((CommHeaderType *)rec->Buffer)->PacketID;
                for (int j = 0; j < unknown_d4; j++) {
                    if (unknown_d0[j] == id) {
                        unknown_d0[j] = -1;
                        break;
                    }
                }
                Queue->UnQueue_Receive(0, 0, i, 0, 0);
                i--;
            } else {
                Debug_Printf("Leaving global packet due to age of %d seconds\n", (int)(TickCount.Time() - rec->ReceiveTime) / 60);
            }
        }
    }
    Debug_Printf("Done stripping. Num receive = %d\n", Queue->ReceiveCount);
}
