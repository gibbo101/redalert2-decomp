// void *NullModemClass::Oldest_Send() (0x005D0920)
// The buffer of the oldest unacknowledged data packet that needs an ACK.
#include "shared/null_modem.hpp"
// @ref ?Get_Send@CommBufferClass@@QAEPAUSendQueueType@@H@Z=00480700

void *NullModemClass::Oldest_Send()
{
    void *buf = 0;
    for (int i = 0; i < Connection->Queue->SendCount; i++) {
        SendQueueType *send = Connection->Queue->Get_Send(i);
        if (send && ((CommHeaderType *)send->Buffer)->Code == 0 && !send->IsACK) {
            buf = send->Buffer;
            break;
        }
    }
    return buf;
}
