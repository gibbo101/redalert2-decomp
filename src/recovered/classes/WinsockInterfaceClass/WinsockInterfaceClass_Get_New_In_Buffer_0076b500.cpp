// WinsockInterfaceClass::WinsockBufferType *WinsockInterfaceClass::Get_New_In_Buffer() (0x0076B500)
// A free static incoming buffer (round-robin), or an allocated one when the
// pool is exhausted.
#include "shared/winsock_interface.hpp"
// @ref ??2@YAPAXI@Z=00782017

WinsockInterfaceClass::WinsockBufferType *WinsockInterfaceClass::Get_New_In_Buffer()
{
    WinsockBufferType *buffer = 0;
    if (StaticInBuffersInUse == 128) {
        buffer = new WinsockBufferType;
        buffer->IsAllocated = true;
        buffer->InUse = true;
    } else {
        for (int i = 0; i < 128; i++) {
            int index = NextInBuffer++;
            if (NextInBuffer > 127) {
                NextInBuffer = 0;
            }
            if (!StaticInBuffers[index].InUse) {
                buffer = &StaticInBuffers[index];
                buffer->InUse = true;
                StaticInBuffersInUse++;
                break;
            }
        }
    }
    if (buffer) {
        buffer->IsAlternate = false;
        buffer->unknown_18 = 0;
    }
    return buffer;
}
