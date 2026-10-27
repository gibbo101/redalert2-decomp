// unsigned long IPXManagerClass::Response_Time() (0x00526BC0, slot 12)
// The largest mean round-trip delay of the connections and the multicast
// connection.
#include "shared/ipx_manager.hpp"
// @ref ?Avg_Delay@CommBufferClass@@QAEKXZ=00480a60

unsigned long IPXManagerClass::Response_Time()
{
    unsigned long resp = 0;
    unsigned long time;
    for (int i = 0; i < NumConnections; i++) {
        time = Connection[i]->Queue->Avg_Delay();
        if (time > resp) {
            resp = time;
        }
    }
    if (unknown_50) {
        time = unknown_50->Queue->Avg_Delay();
        if (time > resp) {
            resp = time;
        }
    }
    return resp;
}
