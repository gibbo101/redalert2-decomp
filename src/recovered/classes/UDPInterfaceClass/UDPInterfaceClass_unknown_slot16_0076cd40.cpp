// int UDPInterfaceClass::unknown_slot16(int window, int message, int wparam, int lparam) (0x0076CD40, slot 16)
// The Winsock message handler (TibSun wspudp.cpp Message_Handler with RA2's spare sockets,
// alternate socket, unreachable list and packet-router address translation).
#include "shared/udp_interface.hpp"
#include "shared/crt_string.hpp"
#include "shared/crt_memory.hpp"
#include "shared/session_state.hpp"
#include "shared/unknown_globals.hpp"
#include "shared/random2.hpp"
#include "shared/unknown_player_entry.hpp"
// @ref ??_C@_0BJ@KJOH@sendto?5?$CFd?4?$CFd?4?$CFd?4?$CFd?5?$DL?5?$CFd?6?$AA@=0080120c
// @ref ??_C@_0BK@CMAK@sendto?5returned?5error?5?$CFd?6?$AA@=008011f0
// @ref ??_C@_0BL@DGAO@recvfrom?5?$CFd?4?$CFd?4?$CFd?4?$CFd?5?$DL?5?$CFd?6?$AA@=00801188
// @ref ??_C@_0BM@HFGK@FD_WRITE?5?9?5Using?5socket?5?$CFd?6?$AA@=008012ac
// @ref ??_C@_0BN@NKKG@FD_READ?5?9?5Got?5error?5code?5?$CFd?6?$AA@=008011a4
// @ref ??_C@_0BO@HLIP@FD_WRITE?5?9?5Got?5error?5code?5?$CFd?6?$AA@=0080128c
// @ref ??_C@_0CM@JJEL@FD_WRITE?5?9?5?$CFd?4?$CFd?4?$CFd?4?$CFd?5?$DL?5?$CFd?5is?5u@=008011c4
// @ref ??_C@_0CP@OHOC@FD_WRITE?5?9?5No?5OutBuffers?5left?5?9?5@=00801228
// @ref ??_C@_0DC@HLE@FD_WRITE?5?9?5No?5AltOutBuffers?5left@=00801258
// @ref ??_C@_0DM@HNIM@Throwing?5away?5malformed?5packet?5f@=0080114c
// @ref ?unknown_port_7f60d4@@3HA=007f60d4

// @ref ?unknown_b2af1c@@3_NA=00b2af1c

int UDPInterfaceClass::unknown_slot16(int window, int message, int wparam, int lparam)
{
    sockaddr_in addr;
    int addr_len;
    union {
        unsigned long Address;
        unsigned char Bytes[4];
    } ip;
    bool alternate = false;
    SOCKET socket;
    int rc;

    if (message == 0x474) {
        socket = Socket;
        if ((SOCKET)wparam != socket) {
            for (int i = 0; i < NumSockets; i++) {
                if (Sockets[i] == (SOCKET)wparam) {
                    socket = Sockets[i];
                    break;
                }
            }
        }
    } else if (message == 0x475) {
        socket = Socket2;
        alternate = true;
    } else {
        return 1;
    }

    switch (WSAGETSELECTEVENT(lparam)) {
    case FD_READ:
    {
        rc = WSAGETSELECTERROR(lparam);
        if (rc != 0) {
            Debug_Printf("FD_READ - Got error code %d\n", rc);
            Clear_Socket_Error(socket);
            return 0;
        }
        addr_len = sizeof(addr);
        rc = recvfrom(socket, ReceiveBuffer, sizeof(ReceiveBuffer), 0, &addr, &addr_len);
        if (rc == SOCKET_ERROR) {
            Clear_Socket_Error(socket);
            return 0;
        }
        if (rc != 0) {
            ip.Address = addr.sin_addr;
            Debug_Printf("recvfrom %d.%d.%d.%d ; %d\n", ip.Bytes[0], ip.Bytes[1], ip.Bytes[2], ip.Bytes[3], ntohs(addr.sin_port));
            if (!alternate && !unknown_session_a3d298.ViaPacketRouter) {
                for (int i = 0; i < LocalAddresses.Count(); i++) {
                    if (!memcmp(LocalAddresses[i], &addr.sin_addr, 4)) {
                        return 0;
                    }
                }
            }
            int loss = unknown_76b9f0();
            if (loss > 0 && unknown_random_839218(0, 99) <= loss) {
                return 0;
            }
            WinsockBufferType *packet = Get_New_In_Buffer();
            packet->BufferLen = rc - sizeof(packet->CRC);
            packet->CRC = *(unsigned long *)&ReceiveBuffer[0];
            packet->IsAlternate = alternate;
            packet->unknown_18 = 0;
            memcpy(packet->Buffer, ReceiveBuffer + sizeof(packet->CRC), packet->BufferLen);
            if (!Passes_CRC_Check(packet)) {
                *(unsigned long *)&packet->Address[4] = addr.sin_addr;
                unsigned long from = addr.sin_addr;
                Debug_Printf("Throwing away malformed packet from %d . %d . %d . %d ; %d\n", from & 0xFF, (from >> 8) & 0xFF, (from >> 16) & 0xFF, from >> 24, ntohs(addr.sin_port));
                if (!unknown_b2af1c) {
                    unknown_b2af1c = true;
                }
                if (packet->IsAllocated) {
                    delete packet;
                } else {
                    packet->InUse = false;
                    StaticOutBuffersInUse--;
                }
                return 0;
            }
            memset(packet->Address, 0, sizeof(packet->Address));
            if (addr.sin_addr == htonl(0x7F000001)) {
                packet->unknown_1a = 0;
                *(IPXAddressClass *)packet->Address = unknown_forward_address_a3fbb8;
            } else {
                packet->unknown_1a = ntohs(addr.sin_port);
                *(unsigned long *)&packet->Address[4] = addr.sin_addr;
            }
            InBuffers.Add(packet);
        }
        return 0;
    }

    case FD_WRITE:
    {
        if (unknown_3f334 != -1) {
            for (int i = 0; i < NumSockets; i++) {
                if (Sockets[i] == unknown_3f334) {
                    socket = unknown_3f334;
                    Debug_Printf("FD_WRITE - Using socket %d\n", socket);
                }
            }
        }
        rc = WSAGETSELECTERROR(lparam);
        if (rc != 0) {
            Debug_Printf("FD_WRITE - Got error code %d\n", rc);
            Clear_Socket_Error(socket);
            return 0;
        }
        WinsockBufferType *packet;
        if (alternate) {
            if (AltBuffers.Count() == 0) {
                Debug_Printf("FD_WRITE - No AltOutBuffers left - nothing to do\n");
                return 0;
            }
            packet = AltBuffers[0];
        } else {
            if (OutBuffers.Count() == 0) {
                Debug_Printf("FD_WRITE - No OutBuffers left - nothing to do\n");
                return 0;
            }
            packet = OutBuffers[0];
        }
        addr.sin_addr = *(unsigned long *)&packet->Address[4];
        addr.sin_port = htons(packet->unknown_1a);
        addr.sin_family = AF_INET;
        if (alternate) {
            if (addr.sin_addr != htonl(0x7F000001)) {
                addr.sin_port = htons((unsigned short)unknown_port_7f60d4);
                addr.sin_addr = htonl(0x7F000001);
            }
        } else {
            if (packet->unknown_1a) {
                addr.sin_port = htons(packet->unknown_1a);
            } else {
                addr.sin_port = htons(unknown_default_port_7f60d0);
            }
            if (!memcmp(&packet->Address[4], unknown_forward_address_a3fbb8.NodeAddress, 4)
                && (unknown_session_a3d298.Players.Count() == 0 || unknown_forward_address_a3fbb8 == unknown_session_a3d298.Players[0]->Address)) {
                addr.sin_addr = htonl(0x7F000001);
                addr.sin_port = htons((unsigned short)unknown_port_7f60dc);
            }
        }
        ip.Address = addr.sin_addr;
        unsigned short port = ntohs(addr.sin_port);
        bool unreachable = false;
        for (int i = 0; i < NumUnreachable; i++) {
            if (port == UnreachablePorts[i] && !memcmp(&ip, &UnreachableAddresses[i], 4)) {
                unreachable = true;
                break;
            }
        }
        if (!unreachable) {
            Debug_Printf("sendto %d.%d.%d.%d ; %d\n", ip.Bytes[0], ip.Bytes[1], ip.Bytes[2], ip.Bytes[3], ntohs(addr.sin_port));
            rc = sendto(socket, (char const *)&packet->CRC, packet->BufferLen + sizeof(packet->CRC), 0, &addr, sizeof(addr));
            if (rc == SOCKET_ERROR && WSAGetLastError() != WSAEWOULDBLOCK) {
                Debug_Printf("sendto returned error %d\n", WSAGetLastError());
                Clear_Socket_Error(socket);
                return 0;
            }
        } else {
            Debug_Printf("FD_WRITE - %d.%d.%d.%d ; %d is unreachable\n", ip.Bytes[0], ip.Bytes[1], ip.Bytes[2], ip.Bytes[3], ntohs(addr.sin_port));
        }
        if (alternate) {
            AltBuffers.Delete(0);
            if (packet->IsAllocated) {
                delete packet;
            } else {
                packet->InUse = false;
                StaticAltBuffersInUse--;
            }
            return 0;
        }
        OutBuffers.Delete(0);
        if (packet->IsAllocated) {
            delete packet;
        } else {
            packet->InUse = false;
            StaticOutBuffersInUse--;
        }
        return 0;
    }
    }
    return 0;
}
