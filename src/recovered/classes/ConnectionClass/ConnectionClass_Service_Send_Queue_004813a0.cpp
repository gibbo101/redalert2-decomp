// int ConnectionClass::Service_Send_Queue() (0x004813A0, slot 7)
// Drops acknowledged packets (timing the round trip of sequenced ones),
// then resends whatever is due, flagging entries past the retry or time
// limits; 0 when the connection has gone bad.
#include "shared/connection.hpp"
// @ref ?Debug_Printf@@YAXPBDZZ=004068f0
// @ref ?Get_Send@CommBufferClass@@QAEPAUSendQueueType@@H@Z=00480700
// @ref ?UnQueue_Send@CommBufferClass@@QAEHPAXPAHH01PAG@Z=00480550
// @ref ?Add_Delay@CommBufferClass@@QAEXK@Z=004809f0
// @ref ?TickCount@@3V?$TTimerClass@VSystemTimerClass@@@@A=00839980
// @ref ??BSystemTimerClass@@QBEJXZ=0069a430
// @ref ?unknown_connection_a409c4@@3PAVConnectionClass@@A=00a409c4
// @ref ??_C@_0DE@IMCJ@ConnectionClass?3?3Service_Send_Qu@=007d3304

int ConnectionClass::Service_Send_Queue()
{
    int i;
    int bad_conn = 0;
    SendQueueType *send;

    for (i = 0; i < Queue->SendCount; i++) {
        send = Queue->Get_Send(i);
        if (send->IsACK) {
            if (((CommHeaderType *)send->Buffer)->Code == PACKET_DATA_ACK) {
                Queue->Add_Delay(Time() - send->FirstTime);
            }
            Queue->UnQueue_Send(0, 0, i, 0, 0, 0);
            i--;
        }
    }

    int count = Queue->SendCount;
    for (i = 0; i < count; i++) {
        send = Queue->Get_Send(i);
        if (send->IsACK) {
            continue;
        }
        unsigned long time = Time();
        if (time - send->LastTime > RetryDelta) {
            Send(send->Buffer, send->BufLen, send->ExtraBuffer, send->ExtraLen,
                this == unknown_connection_a409c4, send->unknown_20);
            send->LastTime = time;
            if (send->SendCount == 0) {
                send->FirstTime = time;
                if (((CommHeaderType *)send->Buffer)->Code == PACKET_DATA_NOACK) {
                    send->IsACK = 1;
                }
            } else {
                unknown_08++;
            }
            send->SendCount++;
            if (MaxRetries != 0xFFFFFFFF && send->SendCount > MaxRetries) {
                bad_conn = 1;
                send->unknown_bit2 = 1;
            }
            if (Timeout != 0xFFFFFFFF && send->LastTime - send->FirstTime > Timeout) {
                bad_conn = 1;
                send->unknown_bit2 = 1;
            }
        }
    }

    if (bad_conn) {
        Debug_Printf("ConnectionClass::Service_Send_Queue bad connection\n");
        return 0;
    }
    return 1;
}
