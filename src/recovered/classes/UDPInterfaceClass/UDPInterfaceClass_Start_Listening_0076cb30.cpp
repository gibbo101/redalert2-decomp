// bool UDPInterfaceClass::Start_Listening() (0x0076CB30, slot 7)
// The base sockets, then read/write notifications on every spare socket.
#include "shared/udp_interface.hpp"
// @ref ?Start_Listening@WinsockInterfaceClass@@UAE_NXZ=0076ae80
// @ref _WSAAsyncSelect@16=00781bc0
// @ref ?unknown_window_b263d8@@3PAXA=00b263d8
// @ref ?Unknown_005B5EE0@@YAXXZ=005b5ee0
// @ref ?Debug_Printf@@YAXPBDZZ=004068f0
// @ref ??_C@_0CG@MABK@Async?5select?5failed?5on?5spare?5soc@=008010f0

bool UDPInterfaceClass::Start_Listening()
{
    if (WinsockInterfaceClass::Start_Listening()) {
        for (int i = 0; i < NumSockets; i++) {
            if (WSAAsyncSelect(Sockets[i], unknown_window_b263d8, unknown_slot14(-1), 3) == SOCKET_ERROR) {
                Debug_Printf("Async select failed on spare socket.\n");
                return false;
            }
        }
    }
    Unknown_005B5EE0();
    return true;
}
