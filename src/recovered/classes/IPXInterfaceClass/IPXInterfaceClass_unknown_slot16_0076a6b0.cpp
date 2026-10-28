// int IPXInterfaceClass::unknown_slot16(int window, int message, int wparam, int lparam) (0x0076A6B0, slot 16)
// The socket notification handler (message 0x473): FD_READ queues an
// incoming packet that is not our own and passes its CRC check; FD_WRITE
// sends every queued outgoing packet.
#include "shared/ipx_interface.hpp"
#include "shared/ipx_address.hpp"
#include "shared/random2.hpp"
// @ref _recvfrom@24=00781bae
// @ref _sendto@24=00781bb4
// @ref _htons@4=00781b6c
// @ref _WSAGetLastError@0=00781b7e
// @ref ??3@YAXPAX@Z=00781d3b
// @ref ?Get_New_In_Buffer@WinsockInterfaceClass@@QAEPAVWinsockBufferType@1@XZ=0076b500
// @ref ?unknown_76b9f0@WinsockInterfaceClass@@SAHXZ=0076b9f0
// @ref ?unknown_random_839218@@3VRandom2Class@@A=00839218
// @ref ??RRandom2Class@@QAEHHH@Z=006388a0
// @ref ?Get_Address@IPXAddressClass@@QAEXQAE0@Z=00523500
// @ref ?Set_Address@IPXAddressClass@@QAEXQAE0H@Z=00523480
// @ref ?unknown_malformed_seen_b2ae24@@3_NA=00b2ae24
// @ref ?Debug_Printf@@YAXPBDZZ=004068f0
// @ref ??_C@_0CA@CMFA@Throwing?5away?5malformed?5packet?6?$AA@=00800a90

int IPXInterfaceClass::unknown_slot16(int window, int message, int wparam, int lparam)
{
    UnknownIPXSocketAddress address;
    NetNumType network;
    NetNodeType node;
    WinsockBufferType *packet;

    if (message != 0x473) {
        return 1;
    }
    switch (WSAGETSELECTEVENT(lparam)) {
        case FD_READ: {
            int error = WSAGETSELECTERROR(lparam);
            if (error) {
                Clear_Socket_Error(Socket);
                return 0;
            }
            int length = sizeof(address);
            int received = recvfrom(Socket, ReceiveBuffer, sizeof(ReceiveBuffer), 0, &address, &length);
            if (received == SOCKET_ERROR) {
                if (WSAGetLastError() != WSAEWOULDBLOCK) {
                    Clear_Socket_Error(Socket);
                }
                return 0;
            }
            if (received) {
                memcpy(network, address.sa_netnum, sizeof(network));
                memcpy(node, address.sa_nodenum, sizeof(node));
                if (!memcmp(network, Network, sizeof(network)) && !memcmp(node, unknown_3f306, sizeof(node))) {
                    return 0;
                }
                int loss = WinsockInterfaceClass::unknown_76b9f0();
                if (loss > 0 && unknown_random_839218(0, 99) <= loss) {
                    return 0;
                }
                packet = Get_New_In_Buffer();
                packet->BufferLen = received - 4;
                packet->CRC = *(unsigned long *)ReceiveBuffer;
                memcpy(packet->Buffer, &ReceiveBuffer[4], received - 4);
                if (!Passes_CRC_Check(packet)) {
                    Debug_Printf("Throwing away malformed packet\n");
                    if (!unknown_malformed_seen_b2ae24) {
                        unknown_malformed_seen_b2ae24 = true;
                    }
                    if (packet->IsAllocated) {
                        delete packet;
                        return 0;
                    }
                    packet->InUse = false;
                    StaticOutBuffersInUse--;
                    return 0;
                }
                ((IPXAddressClass *)packet->Address)->Set_Address(network, node, 0);
                InBuffers.Add(packet);
            }
            return 0;
        }

        case FD_WRITE: {
            int error = WSAGETSELECTERROR(lparam);
            if (error) {
                Clear_Socket_Error(Socket);
                return 0;
            }
            while (OutBuffers.Count()) {
                packet = OutBuffers[0];
                address.sa_family = 6;
                address.sa_socket = htons(SocketNumber);
                if (packet->IsBroadcast) {
                    memcpy(address.sa_netnum, Network, sizeof(address.sa_netnum));
                    memcpy(address.sa_nodenum, Node, sizeof(address.sa_nodenum));
                } else {
                    ((IPXAddressClass *)packet->Address)->Get_Address(network, node);
                    memcpy(address.sa_netnum, network, sizeof(address.sa_netnum));
                    memcpy(address.sa_nodenum, node, sizeof(address.sa_nodenum));
                }
                if (sendto(Socket, (char *)&packet->CRC, packet->BufferLen + 4, 0, &address, sizeof(address)) == SOCKET_ERROR
                    && WSAGetLastError() != WSAEWOULDBLOCK) {
                    Clear_Socket_Error(Socket);
                    return 0;
                }
                OutBuffers.Delete(0);
                if (packet->IsAllocated) {
                    delete packet;
                } else {
                    packet->InUse = false;
                    StaticOutBuffersInUse--;
                }
            }
            return 0;
        }
    }
    return 0;
}
