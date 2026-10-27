// unsigned long IPXManagerClass::unknown_526c70() (0x00526C70)
// The multicast channel's mean delay (0 without one).
#include "shared/ipx_manager.hpp"
// @ref ?Avg_Delay@CommBufferClass@@QAEKXZ=00480a60

unsigned long IPXManagerClass::unknown_526c70()
{
    if (unknown_50) {
        return unknown_50->Queue->Avg_Delay();
    }
    return 0;
}
