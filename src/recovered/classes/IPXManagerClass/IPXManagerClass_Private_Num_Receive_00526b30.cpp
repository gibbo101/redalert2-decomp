// int IPXManagerClass::Private_Num_Receive(int id) (0x00526B30, slot 10)
// A connection's queued receives, or the most of any connection (-1).
#include "shared/ipx_manager.hpp"

int IPXManagerClass::Private_Num_Receive(int id)
{
    if (!IPXStatus || !Listening || NumConnections == 0) {
        return 0;
    }
    if (id != -1) {
        int index = Connection_Index(id);
        if (index == -1) {
            return 0;
        }
        return Connection[index]->Queue->ReceiveCount;
    }
    int maxnum = 0;
    for (int i = 0; i < NumConnections; i++) {
        if (Connection[i]->Queue->ReceiveCount > maxnum) {
            maxnum = Connection[i]->Queue->ReceiveCount;
        }
    }
    return maxnum;
}
