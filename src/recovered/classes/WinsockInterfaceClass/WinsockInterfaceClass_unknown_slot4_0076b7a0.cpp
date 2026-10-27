// void WinsockInterfaceClass::unknown_slot4(void *buf, int buflen, bool alternate) (0x0076B7A0, slot 4)
// Queues a broadcast packet (checksummed) and posts a write notification.
#include "shared/winsock_interface.hpp"
// @ref __imp__PostMessageA@16=0079a4a0
// @ref ?unknown_window_b263d8@@3PAXA=00b263d8
// @ref ?WWKeyboard@@3PAVWWKeyboardClass@@A=00832468
// @ref ?Check@WWKeyboardClass@@QAE?AW4KeyNumType@@XZ=005322d0
// @ref ?Get_New_Out_Buffer@WinsockInterfaceClass@@QAEPAVWinsockBufferType@1@_N@Z=0076b3a0

void WinsockInterfaceClass::unknown_slot4(void *buf, int buflen, bool alternate)
{
    WinsockBufferType *packet = Get_New_Out_Buffer(alternate);
    memcpy(packet->Buffer, buf, buflen);
    packet->BufferLen = buflen;
    Build_Packet_CRC(packet);
    packet->IsBroadcast = true;
    SOCKET socket;
    if (alternate) {
        AltBuffers.Add(packet);
        socket = Socket2;
    } else {
        OutBuffers.Add(packet);
        socket = Socket;
    }
    PostMessageA(unknown_window_b263d8, unknown_slot14(socket), 0, 2);
    WWKeyboard->Check();
}
