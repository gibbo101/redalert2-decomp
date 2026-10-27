// void IPXGlobalConnClass::unknown_524a10(int arg1) (0x00524A10)
// Clears IsBridge once the IPX class is configured (the argument is unused).
#include "shared/ipx_global_conn.hpp"
// @ref ?Configured@IPXConnClass@@2HA=00a52404

void IPXGlobalConnClass::unknown_524a10(int arg1)
{
    if (Configured) {
        IsBridge = 0;
    }
}
