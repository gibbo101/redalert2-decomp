// void WinsockInterfaceClass::unknown_slot3(void *buf, int buflen, void *address, int addresslen, bool alternate, unsigned char arg6, unsigned short arg7) (0x0076B670, slot 3)
// Queues a packet for one address (checksummed) and posts a write
// notification for its socket.
#include "shared/winsock_interface.hpp"
// @ref __imp__SendMessageA@16=0079a4a0
// @ref ?unknown_window_b263d8@@3PAXA=00b263d8
// @ref ?WWKeyboard@@3PAVWWKeyboardClass@@A=00832468
// @ref ?Check@WWKeyboardClass@@QAE?AW4KeyNumType@@XZ=005322d0
// @ref ?Get_New_Out_Buffer@WinsockInterfaceClass@@QAEPAVWinsockBufferType@1@_N@Z=0076b3a0

void WinsockInterfaceClass::unknown_slot3(void *buf, int buflen, void *address, int addresslen, bool alternate, unsigned char arg6, unsigned short arg7)
{
    WinsockBufferType *packet = Get_New_Out_Buffer(alternate);
    memcpy(packet->Buffer, buf, buflen);
    packet->BufferLen = buflen;
    packet->IsBroadcast = false;
    packet->unknown_18 = arg6;
    memcpy(packet->Address, address, addresslen);
    packet->unknown_1a = arg7;
    Build_Packet_CRC(packet);
    SOCKET socket;
    if (alternate) {
        AltBuffers.Add(packet);
        socket = Socket2;
    } else {
        OutBuffers.Add(packet);
        socket = Socket;
    }
    SendMessageA((HWND)unknown_window_b263d8, unknown_slot14(socket), 0, 2);
    WWKeyboard->Check();
}
