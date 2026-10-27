// int IPXManagerClass::Private_Num_Send(int id) (0x00526AC0, slot 9)
// A connection's queued sends, or the most of any connection (-1).
#include "shared/ipx_manager.hpp"

int IPXManagerClass::Private_Num_Send(int id)
{
    if (!IPXStatus || !Listening || NumConnections == 0) {
        return 0;
    }
    if (id != -1) {
        int index = Connection_Index(id);
        if (index == -1) {
            return 0;
        }
        return Connection[index]->Queue->SendCount;
    }
    int maxnum = 0;
    for (int i = 0; i < NumConnections; i++) {
        if (Connection[i]->Queue->SendCount > maxnum) {
            maxnum = Connection[i]->Queue->SendCount;
        }
    }
    return maxnum;
}
