// void __fastcall Unknown_0053F780() (0x0053F780; traces "Disconnect_Gracefully")
// In a game-mode 4 game with an active transport and the forwarding route: lets the
// flagged connection's owner signal the router and waits up to 480 ticks for the
// router to shut down, then sends NET_PORT_UNREACHABLE unless the session's slot 2
// says otherwise. Do_Win, Do_Lose and 0x0053F840 call it at the end of a game.
#include "shared/unknown_globals.hpp"
#include "shared/connection.hpp"
#include "shared/owner_talk.hpp"
#include "shared/winsock_interface.hpp"
#include "shared/cd_timer.hpp"
#include "shared/system_timer.hpp"
#include "shared/queue.hpp"
#include "shared/debug_printf.hpp"
// @ref ??_H@YGXPAXIHP6EX0@Z@Z=0040aed0
// @ref ??_C@_0BH@NLBJ@Disconnect_Gracefully?6?$AA@=007dfb84

void __fastcall Unknown_0053F780()
{
    Debug_Printf("Disconnect_Gracefully\n");
    if (unknown_game_mode_a3d298 == 4 && PacketTransport != 0 && unknown_flag_a3fba8) {
        if (unknown_connection_a409c4 != 0) {
            unknown_OwnerTalkClass_00ab6d18.Unknown_0063FC90();
            CDTimerClass<SystemTimerClass> timer = 480;
            while (timer.Value() != 0) {
                Service_Game_IO_00481fb0();
                if (unknown_OwnerTalkClass_00ab6d18.Wait_For_Router_Shutdown(10, false)) {
                    break;
                }
            }
        }
        if (unknown_session_a3d29c == 0 || !unknown_session_a3d29c->unknown_slot2()) {
            Send_Port_Unreachable();
        }
    }
}
