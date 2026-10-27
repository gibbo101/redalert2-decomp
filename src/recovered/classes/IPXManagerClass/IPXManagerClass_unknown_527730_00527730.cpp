// void IPXManagerClass::unknown_527730(int arg1) (0x00527730)
#include "shared/ipx_manager.hpp"
// @ref ?unknown_524a10@IPXGlobalConnClass@@QAEXH@Z=00524a10

void IPXManagerClass::unknown_527730(int arg1)
{
    if (GlobalChannel) {
        GlobalChannel->unknown_524a10(arg1);
    }
}
