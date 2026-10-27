// WinsockInterfaceClass::WinsockInterfaceClass() (0x0076AC80)
// Empty buffer lists, no sockets, every static buffer free.
#include "shared/winsock_interface.hpp"
// @ref ??_7WinsockInterfaceClass@@6B@=007afa7c
// @ref ??_7?$DynamicVectorClass@PAVWinsockBufferType@WinsockInterfaceClass@@@@6B@=007afadc
// @ref ?Debug_Printf@@YAXPBDZZ=004068f0
// @ref ?Fetch@?$VectorClass@PAVWinsockBufferType@WinsockInterfaceClass@@@@UBEPAVWinsockBufferType@WinsockInterfaceClass@@H@Z=0076bb50
// @ref ??8?$VectorClass@PAVWinsockBufferType@WinsockInterfaceClass@@@@UBE_NABV0@@Z=0076bb60
// @ref ?Clear@?$VectorClass@PAVWinsockBufferType@WinsockInterfaceClass@@@@UAEXXZ=0076bc50
// @ref ?ID@?$VectorClass@PAVWinsockBufferType@WinsockInterfaceClass@@@@UAEHABQAVWinsockBufferType@WinsockInterfaceClass@@@Z=0076bc80
// @ref ?ID@?$VectorClass@PAVWinsockBufferType@WinsockInterfaceClass@@@@UAEHPBQAVWinsockBufferType@WinsockInterfaceClass@@@Z=0076bcc0
// @ref ?Resize@?$VectorClass@PAVWinsockBufferType@WinsockInterfaceClass@@@@UAE_NHPBQAVWinsockBufferType@WinsockInterfaceClass@@@Z=0076bba0
// @ref ??_C@_0BO@KMPH@WinsockInterface?5constructed?6?$AA@=00800b68

WinsockInterfaceClass::WinsockInterfaceClass()
{
    Socket = INVALID_SOCKET;
    Socket2 = INVALID_SOCKET;
    WinsockInitialised = false;
    for (int i = 0; i < 128; i++) {
        StaticInBuffers[i].InUse = false;
        StaticInBuffers[i].IsAllocated = false;
        StaticOutBuffers[i].InUse = false;
        StaticOutBuffers[i].IsAllocated = false;
        StaticOutBuffers[i].IsAlternate = false;
        StaticOutBuffers[i].unknown_18 = false;
        StaticAltBuffers[i].InUse = false;
        StaticAltBuffers[i].IsAllocated = false;
        StaticAltBuffers[i].IsAlternate = true;
        StaticAltBuffers[i].unknown_18 = false;
    }
    StaticInBuffersInUse = 0;
    StaticOutBuffersInUse = 0;
    StaticAltBuffersInUse = 0;
    NextInBuffer = 0;
    NextOutBuffer = 0;
    unknown_04 = 0x240;
    Debug_Printf("WinsockInterface constructed\n");
}
