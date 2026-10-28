// void NullModemClass::Configure_Debug(int index, int offset, int size, int names, int namestart, int namecount) (0x005D0970, slot 15)
#include "shared/null_modem.hpp"
// @ref ?Configure_Debug@CommBufferClass@@QAEXHHHHH@Z=00480ab0

void NullModemClass::Configure_Debug(int index, int offset, int size, int names, int namestart, int namecount)
{
    if (Connection) {
        Connection->Queue->Configure_Debug(offset, size, names, namestart, namecount);
    }
}
