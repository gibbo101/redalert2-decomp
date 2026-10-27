// wchar_t *IPXManagerClass::Connection_Name(int id) (0x00525700)
#include "shared/ipx_manager.hpp"

wchar_t *IPXManagerClass::Connection_Name(int id)
{
    for (int i = 0; i < NumConnections; i++) {
        if (Connection[i]->ID == id) {
            return Connection[i]->Name;
        }
    }
    return 0;
}
