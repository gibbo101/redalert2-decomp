// int IPXGlobalConnClass::unknown_slot16(IPXAddressClass *address, unsigned short id) (0x00524AA0, slot 16)
// Removes the unacknowledged sends to an address (same node) with the given ID and
// returns how many.
#include "shared/ipx_global_conn.hpp"
// @ref ?Get_Send@CommBufferClass@@QAEPAUSendQueueType@@H@Z=00480700
// @ref ?UnQueue_Send@CommBufferClass@@QAEHPAXPAHH01PAG@Z=00480550
// @ref ??0IPXAddressClass@@QAE@XZ=00523410
// @ref ?unknown_523690@IPXAddressClass@@QAE_NAAV1@@Z=00523690

int IPXGlobalConnClass::unknown_slot16(IPXAddressClass *address, unsigned short id)
{
    int count = 0;
    for (int i = 0; i < Queue->SendCount; i++) {
        SendQueueType *send = Queue->Get_Send(i);
        if (!send->IsACK && send->ExtraLen
            && ((IPXAddressClass *)send->ExtraBuffer)->unknown_523690(*address) && send->unknown_20 == id) {
            char buffer[1024];
            int buflen;
            IPXAddressClass dest;
            int destlen = sizeof(dest);
            Queue->UnQueue_Send(buffer, &buflen, i, &dest, &destlen, 0);
            i--;
            count++;
        }
    }
    return count;
}
