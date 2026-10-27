// void WinsockInterfaceClass::Discard_Out_Buffers() (0x0076AFD0, slot 6)
#include "shared/winsock_interface.hpp"
// @ref ??3@YAXPAX@Z=00781d3b

void WinsockInterfaceClass::Discard_Out_Buffers()
{
    WinsockBufferType *packet;
    while (OutBuffers.Count()) {
        packet = OutBuffers[0];
        if (packet->IsAllocated) {
            delete packet;
        } else {
            packet->InUse = false;
            StaticOutBuffersInUse--;
        }
        OutBuffers.Delete(0);
    }
    StaticOutBuffersInUse = 0;
    NextOutBuffer = 0;
    while (AltBuffers.Count()) {
        packet = AltBuffers[0];
        if (packet->IsAllocated) {
            delete packet;
        } else {
            packet->InUse = false;
            StaticAltBuffersInUse--;
        }
        AltBuffers.Delete(0);
    }
    StaticAltBuffersInUse = 0;
    NextAltBuffer = 0;
}
