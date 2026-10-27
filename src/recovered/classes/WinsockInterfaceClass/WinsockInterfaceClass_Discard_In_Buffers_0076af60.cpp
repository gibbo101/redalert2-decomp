// void WinsockInterfaceClass::Discard_In_Buffers() (0x0076AF60, slot 5)
#include "shared/winsock_interface.hpp"
// @ref ??3@YAXPAX@Z=00781d3b

void WinsockInterfaceClass::Discard_In_Buffers()
{
    while (InBuffers.Count()) {
        WinsockBufferType *packet = InBuffers[0];
        if (packet->IsAllocated) {
            delete packet;
        } else {
            packet->InUse = false;
            StaticInBuffersInUse--;
        }
        InBuffers.Delete(0);
    }
    StaticInBuffersInUse = 0;
    NextInBuffer = 0;
}
