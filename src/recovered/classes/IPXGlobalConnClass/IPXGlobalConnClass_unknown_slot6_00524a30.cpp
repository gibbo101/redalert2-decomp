// int IPXGlobalConnClass::unknown_slot6() (0x00524A30, slot 6)
// Removes the sends that failed (retry or time limit) without an ACK and
// returns how many.
#include "shared/ipx_global_conn.hpp"
// @ref ?Get_Send@CommBufferClass@@QAEPAUSendQueueType@@H@Z=00480700
// @ref ?UnQueue_Send@CommBufferClass@@QAEHPAXPAHH01PAG@Z=00480550
// @ref ??0IPXAddressClass@@QAE@XZ=00523410

int IPXGlobalConnClass::unknown_slot6()
{
    int count = 0;
    for (int i = 0; i < Queue->SendCount; i++) {
        SendQueueType *send = Queue->Get_Send(i);
        if (send->unknown_bit2 && !send->IsACK) {
            char buffer[1024];
            int buflen;
            IPXAddressClass address;
            int addresslen = sizeof(address);
            Queue->UnQueue_Send(buffer, &buflen, i, &address, &addresslen, 0);
            i--;
            count++;
        }
    }
    return count;
}
