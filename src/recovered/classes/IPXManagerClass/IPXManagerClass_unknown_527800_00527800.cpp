// void IPXManagerClass::unknown_527800() (0x00527800)
#include "shared/ipx_manager.hpp"

void IPXManagerClass::unknown_527800()
{
    if (GlobalChannel) {
        GlobalChannel->unknown_c8 = true;
    }
}
