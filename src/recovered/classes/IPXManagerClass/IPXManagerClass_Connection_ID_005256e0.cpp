// int IPXManagerClass::Connection_ID(int index) (0x005256E0, slot 5)
#include "shared/ipx_manager.hpp"

int IPXManagerClass::Connection_ID(int index)
{
    if (index >= 0 && index < NumConnections) {
        return Connection[index]->ID;
    }
    return -1;
}
