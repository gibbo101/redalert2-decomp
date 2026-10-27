// char *IPXManagerClass::unknown_5276a0() (0x005276A0)
// The packet of the oldest unacknowledged sequenced send across the
// connections (the first such entry of each), or null.
#include "shared/ipx_manager.hpp"
// @ref ?Get_Send@CommBufferClass@@QAEPAUSendQueueType@@H@Z=00480700

char *IPXManagerClass::unknown_5276a0()
{
    unsigned long oldest = 0xFFFFFFFF;
    char *packet = 0;
    for (int i = 0; i < NumConnections; i++) {
        SendQueueType *send = 0;
        for (int j = 0; j < Connection[i]->Queue->SendCount; j++) {
            send = Connection[i]->Queue->Get_Send(j);
            if (send != 0) {
                if (((CommHeaderType *)send->Buffer)->Code == PACKET_DATA_ACK && !send->IsACK) {
                    break;
                }
                send = 0;
            }
        }
        if (send != 0 && send->FirstTime < oldest) {
            oldest = send->FirstTime;
            packet = send->Buffer;
        }
    }
    return packet;
}
