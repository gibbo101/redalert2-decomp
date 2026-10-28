// void UDPInterfaceClass::Close_Spare_Socket(unsigned short port) (0x0076C5B0, slot 27)
// Closes the spare socket bound to the port and closes up the list.
#include "shared/udp_interface.hpp"
// @ref _closesocket@4=00781b96
// @ref ?Debug_Printf@@YAXPBDZZ=004068f0
// @ref ??_C@_0BJ@LEI@Closing?5spare?5socket?5?$CFd?6?$AA@=00801014

void UDPInterfaceClass::Close_Spare_Socket(unsigned short port)
{
    if (port) {
        for (int i = 0; i < NumSockets; i++) {
            if (SocketPorts[i] == port) {
                Debug_Printf("Closing spare socket %d\n", Sockets[i]);
                closesocket(Sockets[i]);
                if (Sockets[i] == unknown_3f334) {
                    unknown_3f334 = INVALID_SOCKET;
                }
                for (int j = i; j < NumSockets - 1; j++) {
                    Sockets[j] = Sockets[j + 1];
                    SocketPorts[j] = SocketPorts[j + 1];
                }
                NumSockets--;
                return;
            }
        }
    }
}
