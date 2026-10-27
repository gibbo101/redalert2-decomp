// void IPXManagerClass::Reset_Response_Time(bool clear) (0x00527630, slot 11)
// Resets the connections' delay statistics (the channels' are cleared).
#include "shared/ipx_manager.hpp"
// @ref ?Reset_Delay@CommBufferClass@@QAEX_N@Z=00480a80

void IPXManagerClass::Reset_Response_Time(bool clear)
{
    for (int i = 0; i < NumConnections; i++) {
        Connection[i]->Queue->Reset_Delay(clear);
    }
    if (GlobalChannel) {
        GlobalChannel->Queue->Reset_Delay(true);
    }
    if (unknown_4c) {
        unknown_4c->Queue->Reset_Delay(true);
    }
    if (unknown_50) {
        unknown_50->Queue->Reset_Delay(true);
    }
}
