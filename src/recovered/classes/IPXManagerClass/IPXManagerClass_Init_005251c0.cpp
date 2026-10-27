// int IPXManagerClass::Init() (0x005251C0)
// Resets the transport, recreates both global channels with the current
// timing, configures the IPX socket and starts listening.
#include "shared/ipx_manager.hpp"
// @ref ?Debug_Printf@@YAXPBDZZ=004068f0
// @ref ?PacketTransport@@3PAVWinsockInterfaceClass@@A=00839c50
// @ref ?unknown_game_mode_a3d298@@3HA=00a3d298
// @ref ?Stop_Listening@IPXConnClass@@SAHXZ=00523cf0
// @ref ?Start_Listening@IPXConnClass@@SAHXZ=00523c80
// @ref ?Configure@IPXConnClass@@SIXGHHHHHH@Z=00523c30
// @ref ??0IPXGlobalConnClass@@QAE@HHHGG@Z=005241b0
// @ref ??2@YAPAXI@Z=00782017
// @ref ??_C@_0CA@GGJA@?$CK?$CK?$CK?$CK?5IPXManagerClass?3?3Init?5?$CK?$CK?$CK?6?$AA@=007ddf50

int IPXManagerClass::Init()
{
    Debug_Printf("**** IPXManagerClass::Init ***\n");
    if (PacketTransport) {
        PacketTransport->Discard_In_Buffers();
        PacketTransport->Discard_Out_Buffers();
    }
    if (unknown_game_mode_a3d298 != 4) {
        if (!IPXStatus) {
            return 0;
        }
        if (Listening) {
            IPXConnClass::Stop_Listening();
            Listening = false;
        }
    } else {
        IPXStatus = true;
    }
    if (GlobalChannel) {
        delete GlobalChannel;
        GlobalChannel = 0;
    }
    if (unknown_4c) {
        delete unknown_4c;
        unknown_4c = 0;
    }
    if (unknown_50) {
        delete unknown_50;
        unknown_50 = 0;
    }
    for (int i = 0; i < NumConnections; i++) {
        delete Connection[i];
        Connection[i] = 0;
    }
    NumConnections = 0;

    GlobalChannel = new IPXGlobalConnClass(Glb_NumPackets, Glb_NumPackets * 2, Glb_MaxPacketLen, ProductID, 0x1236);
    if (!GlobalChannel) {
        return 0;
    }
    GlobalChannel->Init();
    GlobalChannel->RetryDelta = RetryDelta;
    GlobalChannel->MaxRetries = MaxRetries;
    GlobalChannel->Timeout = Timeout;

    unknown_4c = new IPXGlobalConnClass(unknown_1c, unknown_1c * 2, unknown_18, ProductID, 0xCDEF);
    if (!unknown_4c) {
        return 0;
    }
    unknown_4c->Init();
    unknown_4c->RetryDelta = RetryDelta;
    unknown_4c->MaxRetries = MaxRetries;
    unknown_4c->Timeout = Timeout;

    IPXConnClass::Configure(Socket, ConnectionNum, unknown_7c, unknown_94, unknown_80, unknown_98, unknown_74);
    if (!PacketTransport) {
        return 0;
    }
    if (unknown_game_mode_a3d298 != 4) {
        if (!IPXConnClass::Start_Listening()) {
            return 0;
        }
    }
    Listening = true;
    return 1;
}
