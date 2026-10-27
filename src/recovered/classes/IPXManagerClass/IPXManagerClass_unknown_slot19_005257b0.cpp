// int IPXManagerClass::unknown_slot19(ConnectionClass *connection) (0x005257B0, slot 19)
// The index of a private connection, or -4 (multicast), -3 (second global
// channel), -2 (global channel), -1 (unknown).
#include "shared/ipx_manager.hpp"

int IPXManagerClass::unknown_slot19(ConnectionClass *connection)
{
    for (int i = 0; i < NumConnections; i++) {
        if (Connection[i] == connection) {
            return i;
        }
    }
    if (connection == unknown_50) {
        return -4;
    }
    if (connection == unknown_4c) {
        return -3;
    }
    if (connection == GlobalChannel) {
        return -2;
    }
    return -1;
}
