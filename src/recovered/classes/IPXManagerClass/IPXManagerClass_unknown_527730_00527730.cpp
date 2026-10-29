// void IPXManagerClass::Set_Bridge(NetNumType bridge) (0x00527730; Red Alert's Set_Bridge).
#include "shared/ipx_manager.hpp"
// @ref ?Set_Bridge@IPXGlobalConnClass@@QAEXQAE@Z=00524a10

void IPXManagerClass::Set_Bridge(NetNumType bridge)
{
    if (GlobalChannel) {
        GlobalChannel->Set_Bridge(bridge);
    }
}
