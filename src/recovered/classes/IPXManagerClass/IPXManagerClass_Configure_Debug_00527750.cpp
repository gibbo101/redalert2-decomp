// void IPXManagerClass::Configure_Debug(int index, int offset, int size, int names, int namestart, int namecount) (0x00527750, slot 15)
// Debug configuration for the global channel (-1) or a connection's queue.
#include "shared/ipx_manager.hpp"
// @ref ?Configure_Debug@CommBufferClass@@QAEXHHHHH@Z=00480ab0

void IPXManagerClass::Configure_Debug(int index, int offset, int size, int names, int namestart, int namecount)
{
    if (index == -1) {
        GlobalChannel->Queue->Configure_Debug(offset, size, names, namestart, namecount);
    } else if (Connection[index]) {
        Connection[index]->Queue->Configure_Debug(offset, size, names, namestart, namecount);
    }
}
