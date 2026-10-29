// void UDPInterfaceClass::unknown_slot4(void *buf, int buflen, bool alternate) (0x0076C9C0, slot 4)
// A broadcast goes to every broadcast address as its own checksummed
// packet, each followed by a write notification.
#include "shared/udp_interface.hpp"
#include "shared/crt_string.hpp"
// @ref __imp__SendMessageA@16=0079a4a0
// @ref ?unknown_window_b263d8@@3PAXA=00b263d8
// @ref ?Unknown_005B5EE0@@YAXXZ=005b5ee0
// @ref ?Get_New_Out_Buffer@WinsockInterfaceClass@@QAEPAVWinsockBufferType@1@_N@Z=0076b3a0

void UDPInterfaceClass::unknown_slot4(void *buf, int buflen, bool alternate)
{
    for (int i = 0; i < BroadcastAddresses.Count(); i++) {
        WinsockBufferType *packet = Get_New_Out_Buffer(alternate);
        memcpy(packet->Buffer, buf, buflen);
        packet->BufferLen = buflen;
        packet->IsBroadcast = true;
        memset(packet->Address, 0, sizeof(packet->Address));
        *(unsigned long *)&packet->Address[4] = *(unsigned long *)BroadcastAddresses[i];
        packet->unknown_1a = BroadcastPorts[i];
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
        Unknown_005B5EE0();
    }
}
