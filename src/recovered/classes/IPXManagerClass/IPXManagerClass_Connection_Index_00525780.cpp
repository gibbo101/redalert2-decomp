// int IPXManagerClass::Connection_Index(int id) (0x00525780, slot 6)
#include "shared/ipx_manager.hpp"

int IPXManagerClass::Connection_Index(int id)
{
    for (int i = 0; i < NumConnections; i++) {
        if (Connection[i]->ID == id) {
            return i;
        }
    }
    return -1;
}
