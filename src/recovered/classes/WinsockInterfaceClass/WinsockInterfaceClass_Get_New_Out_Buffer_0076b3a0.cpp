// WinsockInterfaceClass::WinsockBufferType *WinsockInterfaceClass::Get_New_Out_Buffer(bool alternate) (0x0076B3A0)
// A free static outgoing buffer (round-robin) from the normal or alternate
// pool, or an allocated one when the pool is exhausted.
#include "shared/winsock_interface.hpp"
// @ref ??2@YAPAXI@Z=00782017

WinsockInterfaceClass::WinsockBufferType *WinsockInterfaceClass::Get_New_Out_Buffer(bool alternate)
{
    WinsockBufferType *buffer = 0;
    int i;
    if (!alternate) {
        if (StaticOutBuffersInUse == 128) {
            buffer = new WinsockBufferType;
            buffer->IsAllocated = true;
            buffer->InUse = true;
        } else {
            for (i = 0; i < 128; i++) {
                int index = NextOutBuffer++;
                if (NextOutBuffer > 127) {
                    NextOutBuffer = 0;
                }
                if (!StaticOutBuffers[index].InUse) {
                    buffer = &StaticOutBuffers[index];
                    buffer->InUse = true;
                    StaticOutBuffersInUse++;
                    break;
                }
            }
        }
        if (buffer) {
            buffer->IsAlternate = false;
            buffer->unknown_18 = 0;
        }
    } else {
        if (StaticAltBuffersInUse == 128) {
            buffer = new WinsockBufferType;
            buffer->IsAllocated = true;
            buffer->InUse = true;
        } else {
            for (i = 0; i < 128; i++) {
                int index = NextAltBuffer++;
                if (NextAltBuffer > 127) {
                    NextAltBuffer = 0;
                }
                if (!StaticAltBuffers[index].InUse) {
                    buffer = &StaticAltBuffers[index];
                    buffer->InUse = true;
                    StaticAltBuffersInUse++;
                    break;
                }
            }
        }
        if (buffer) {
            buffer->IsAlternate = true;
            buffer->unknown_18 = 0;
        }
    }
    return buffer;
}
