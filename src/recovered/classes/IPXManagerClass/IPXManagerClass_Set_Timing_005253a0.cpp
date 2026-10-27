// void IPXManagerClass::Set_Timing(unsigned long retrydelta, unsigned long maxretries, unsigned long timeout, bool global) (0x005253A0, slot 13)
// Keeps the timing and applies it to every connection and the multicast
// connection (and the global channel when asked).
#include "shared/ipx_manager.hpp"
// @ref ?Debug_Printf@@YAXPBDZZ=004068f0
// @ref ?unknown_max_ahead_a3d560@@3HA=00a3d560
// @ref ??_C@_0BA@BBAO@MaxAhead?5is?5?$CFd?6?$AA@=007ddf70
// @ref ??_C@_0BO@DNBK@IPX?5Manager?3?5RetryDelta?5?$DN?5?$CFd?6?$AA@=007ddf80

void IPXManagerClass::Set_Timing(unsigned long retrydelta, unsigned long maxretries, unsigned long timeout, bool global)
{
    RetryDelta = retrydelta;
    MaxRetries = maxretries;
    Timeout = timeout;
    Debug_Printf("IPX Manager: RetryDelta = %d\n", retrydelta);
    Debug_Printf("MaxAhead is %d\n", unknown_max_ahead_a3d560);
    if (global) {
        unknown_slot14(RetryDelta, MaxRetries, Timeout);
    }
    for (int i = 0; i < NumConnections; i++) {
        Connection[i]->RetryDelta = RetryDelta;
        Connection[i]->MaxRetries = MaxRetries;
        Connection[i]->Timeout = Timeout;
    }
    if (unknown_50) {
        unknown_50->RetryDelta = RetryDelta;
        unknown_50->MaxRetries = MaxRetries;
        unknown_50->Timeout = Timeout;
    }
}
