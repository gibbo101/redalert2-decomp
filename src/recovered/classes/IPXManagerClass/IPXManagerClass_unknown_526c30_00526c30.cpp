// unsigned long IPXManagerClass::unknown_526c30() (0x00526C30)
// The global channel's mean delay (0 without one).
#include "shared/ipx_manager.hpp"
// @ref ?Avg_Delay@CommBufferClass@@QAEKXZ=00480a60

unsigned long IPXManagerClass::unknown_526c30()
{
    if (GlobalChannel) {
        return GlobalChannel->Queue->Avg_Delay();
    }
    return 0;
}
