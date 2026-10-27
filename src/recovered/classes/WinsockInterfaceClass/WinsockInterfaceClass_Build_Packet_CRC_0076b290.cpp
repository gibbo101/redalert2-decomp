// void WinsockInterfaceClass::Build_Packet_CRC(WinsockBufferType *packet) (0x0076B290, slot 21)
// Checksums the packet's data a word at a time (the last partial word masked).
#include "shared/winsock_interface.hpp"
// @ref ?Add_CRC@@YIXPAKK@Z=0062a340

void WinsockInterfaceClass::Build_Packet_CRC(WinsockBufferType *packet)
{
    packet->CRC = 0;
    unsigned long *ptr = (unsigned long *)packet->Buffer;
    for (int i = 0; i < packet->BufferLen / 4; i++) {
        Add_CRC(&packet->CRC, *ptr++);
    }
    int remainder = packet->BufferLen & 3;
    if (remainder) {
        Add_CRC(&packet->CRC, *ptr & (0xFFFFFFFF >> (32 - remainder * 8)));
    }
}
