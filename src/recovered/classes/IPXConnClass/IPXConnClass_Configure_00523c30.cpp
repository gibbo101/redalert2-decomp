// void __fastcall IPXConnClass::Configure(unsigned short socket, int conn_num, int arg3, int arg4, int arg5, int arg6, int arg7) (0x00523C30)
// Keeps the shared socket settings and marks the class configured.
#include "shared/ipx_conn.hpp"
// @ref ?Configured@IPXConnClass@@2HA=00a52404
// @ref ?ConnectionNum@IPXConnClass@@2HA=00a523b0
// @ref ?Socket@IPXConnClass@@2GA=00a523d0
// @ref ?unknown_a52370@IPXConnClass@@2HA=00a52370
// @ref ?unknown_a52398@IPXConnClass@@2HA=00a52398
// @ref ?unknown_a523c4@IPXConnClass@@2HA=00a523c4
// @ref ?unknown_a523d4@IPXConnClass@@2HA=00a523d4
// @ref ?unknown_a523e0@IPXConnClass@@2HA=00a523e0

void __fastcall IPXConnClass::Configure(unsigned short socket, int conn_num, int arg3, int arg4, int arg5, int arg6, int arg7)
{
    Socket = socket;
    ConnectionNum = conn_num;
    unknown_a523c4 = arg3;
    unknown_a523e0 = arg4;
    unknown_a52398 = arg5;
    unknown_a52370 = arg6;
    unknown_a523d4 = arg7;
    Configured = 1;
}
