// void IPXManagerClass::unknown_525b30(int index) (0x00525B30)
// Marks a global packet read (IPXGlobalConnClass slot 15).
#include "shared/ipx_manager.hpp"

void IPXManagerClass::unknown_525b30(int index)
{
    if (IPXStatus && Listening) {
        GlobalChannel->unknown_slot15(index);
    }
}
