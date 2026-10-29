// void __fastcall Send_Port_Unreachable() (0x0062E840): NET_PORT_UNREACHABLE to every router connection.
#include "shared/queue.hpp"
#include "shared/unknown_player_entry.hpp"
#include "shared/lobby.hpp"
#include "shared/system_timer.hpp"
#include "shared/audio.hpp"
// @ref ?unknown_ipx_manager_a40978@@3VIPXManagerClass@@A=00a40978
// @ref ?unknown_OwnerTalkClass_00ab6d18@@3VOwnerTalkClass@@A=00ab6d18
// @ref ?Unknown_0063FB40@OwnerTalkClass@@QAEPADH@Z=0063fb40
// @ref ?Unknown_0063FA00@OwnerTalkClass@@QAEPAVIPXAddressClass@@PAD@Z=0063fa00
// @ref ?Unknown_0063FAF0@OwnerTalkClass@@QAEGPAD@Z=0063faf0
// @ref ??_C@_0CG@MOKF@Sending?5NET_PORT_UNREACHABLE?5pac@=007ee03c
// @ref ??_C@_0CE@HGJM@Sending?5NET_PORT_UNREACHABLE?5to?5@=007ee018

void __fastcall Send_Port_Unreachable()
{
    UnknownGlobalPacket packet;
    int start;
    int i;
    char *name;

    Debug_Printf("Sending NET_PORT_UNREACHABLE packets\n");
    if (unknown_game_mode_a3d298 != 4) {
        return;
    }
    Unknown_00623280();
    start = unknown_ipx_manager_a40978.Global_Num_Send();
    for (i = 0; i < unknown_OwnerTalkClass_00ab6d18.Connections.Count(); i++) {
        memset(&packet, 0, 0x2F);
        packet.Command = 0x2F;
        strcpy(packet.Name, Unknown_006FA120(unknown_session_a3d298.Players[0]->Name));
        name = unknown_OwnerTalkClass_00ab6d18.Unknown_0063FB40(i);
        if (name && _stricmp(name, Unknown_006FA120(unknown_session_a3d298.Players[0]->Name))) {
            Debug_Printf("Sending NET_PORT_UNREACHABLE to %s\n", name);
            IPXAddressClass address = *unknown_OwnerTalkClass_00ab6d18.Unknown_0063FA00(name);
            unknown_ipx_manager_a40978.Send_Global_Message(&packet, 0x2F, 1, &address, unknown_OwnerTalkClass_00ab6d18.Unknown_0063FAF0(name), 0);
        }
    }
    CDTimerClass<SystemTimerClass> timer(300);
    while (unknown_ipx_manager_a40978.Global_Num_Send() > start && timer) {
        unknown_481fb0();
    }
    Unknown_00623260();
}
