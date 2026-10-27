// int IPXManagerClass::Global_Num_Send() (0x00526A40, slot 7)
#include "shared/ipx_manager.hpp"

int IPXManagerClass::Global_Num_Send()
{
    if (!IPXStatus || !Listening) {
        return 0;
    }
    return GlobalChannel->Queue->SendCount;
}
