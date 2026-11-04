// Server-array lookup -- 0x00765E60; complete existing41-byte body +7NOP.
// Callers742FD0 use globalB2A700: count+0, items+8, stride248 equalsWOL::Server.
#define RA2_WOL_SERVER_ARRAY_GET_SOURCE
#include "shared/wol_sink.hpp"
bool WolServerArray::Get(WOL::Server *&server, int index)
{
    if (index >= 0 && index < Count) {
        server = Items + index;
        return true;
    }
    return false;
}
// @ref ??_E?$rc_ptr@VWDTTerritory@@@@UAEPAXI@Z=0051e600
