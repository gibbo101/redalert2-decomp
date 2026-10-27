// bool WinsockInterfaceClass::Passes_CRC_Check(WinsockBufferType *packet) (0x0076B310, slot 22)
#include "shared/winsock_interface.hpp"
// @ref ?Add_CRC@@YIXPAKK@Z=0062a340
// @ref ?Debug_Printf@@YAXPBDZZ=004068f0
// @ref ??_C@_0BN@DELG@Error?5in?5Winsock?5packet?5CRC?6?$AA@=00800d60

bool WinsockInterfaceClass::Passes_CRC_Check(WinsockBufferType *packet)
{
    if (packet->BufferLen >= (int)sizeof(packet->Buffer)) {
        return false;
    }
    unsigned long crc = 0;
    unsigned long *ptr = (unsigned long *)packet->Buffer;
    for (int i = 0; i < packet->BufferLen / 4; i++) {
        Add_CRC(&crc, *ptr++);
    }
    int remainder = packet->BufferLen & 3;
    if (remainder) {
        Add_CRC(&crc, *ptr & (0xFFFFFFFF >> (32 - remainder * 8)));
    }
    if (crc == packet->CRC) {
        return true;
    }
    Debug_Printf("Error in Winsock packet CRC\n");
    return false;
}
