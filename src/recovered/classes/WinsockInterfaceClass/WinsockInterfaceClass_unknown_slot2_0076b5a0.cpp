// int WinsockInterfaceClass::unknown_slot2(void *buf, int *buflen, void *address, int *addresslen, unsigned short *port) (0x0076B5A0, slot 2)
// Takes the oldest incoming packet: its data, sender address and port;
// returns its length (0 when none).
#include "shared/winsock_interface.hpp"
// @ref ?WWKeyboard@@3PAVWWKeyboardClass@@A=00832468
// @ref ?Check@WWKeyboardClass@@QAE?AW4KeyNumType@@XZ=005322d0
// @ref ??3@YAXPAX@Z=00781d3b

int WinsockInterfaceClass::unknown_slot2(void *buf, int *buflen, void *address, int *addresslen, unsigned short *port)
{
    WWKeyboard->Check();
    if (InBuffers.Count() == 0) {
        return 0;
    }
    WinsockBufferType *packet = InBuffers[0];
    memcpy(buf, packet->Buffer, packet->BufferLen);
    unsigned int length = *addresslen;
    if (length > sizeof(packet->Address)) {
        length = sizeof(packet->Address);
    }
    *addresslen = length;
    memcpy(address, packet->Address, length);
    *port = packet->unknown_1a;
    *buflen = packet->BufferLen;
    InBuffers.Delete(0);
    if (packet->IsAllocated) {
        delete packet;
    } else {
        packet->InUse = false;
        StaticInBuffersInUse--;
    }
    return *buflen;
}
