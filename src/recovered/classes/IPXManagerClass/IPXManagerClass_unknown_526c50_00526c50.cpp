// unsigned long IPXManagerClass::unknown_526c50() (0x00526C50)
// The second global channel's mean delay (0 without one).
#include "shared/ipx_manager.hpp"
// @ref ?Avg_Delay@CommBufferClass@@QAEKXZ=00480a60

unsigned long IPXManagerClass::unknown_526c50()
{
    if (unknown_4c) {
        return unknown_4c->Queue->Avg_Delay();
    }
    return 0;
}
