// void IPXManagerClass::unknown_527830(int index) (0x00527830)
#include "shared/ipx_manager.hpp"

void IPXManagerClass::unknown_527830(int index)
{
    if (GlobalChannel) {
        GlobalChannel->unknown_slot17(index);
    }
}
