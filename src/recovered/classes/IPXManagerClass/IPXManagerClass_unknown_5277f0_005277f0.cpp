// void IPXManagerClass::unknown_5277f0() (0x005277F0)
#include "shared/ipx_manager.hpp"

void IPXManagerClass::unknown_5277f0()
{
    if (GlobalChannel) {
        GlobalChannel->unknown_c8 = false;
    }
}
