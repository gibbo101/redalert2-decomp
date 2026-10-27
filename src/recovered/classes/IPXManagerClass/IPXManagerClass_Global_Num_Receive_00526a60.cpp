// int IPXManagerClass::Global_Num_Receive() (0x00526A60, slot 8)
#include "shared/ipx_manager.hpp"

int IPXManagerClass::Global_Num_Receive()
{
    if (!IPXStatus || !Listening) {
        return 0;
    }
    return GlobalChannel->Queue->ReceiveCount;
}
