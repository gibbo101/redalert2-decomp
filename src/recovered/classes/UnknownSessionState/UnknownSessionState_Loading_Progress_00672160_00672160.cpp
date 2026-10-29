#include "shared/serial_progress.hpp"
#include "shared/queue.hpp"
#include "shared/ipx_manager.hpp"
#include "shared/system_timer.hpp"
#include "shared/cd_timer.hpp"
#include "shared/win32_api.hpp"
#include "shared/debug_printf.hpp"
#include "shared/crt_string.hpp"
#include "shared/keyboard.hpp"
#include "shared/audio.hpp"

// Reports the local loading progress: the progress screen's own bar (half of it while unknown_223b is set), then,
// with other players, a 0x0F global packet (IPX; guaranteed to each player once at 99.95%) or a 0x6C serial packet,
// waiting up to 240 ticks while more than five packets are queued.
void UnknownSessionState::Loading_Progress_00672160(int percent)
{
    if (unknown_flag_a40d13) {
        return;
    }
    int progress = percent;
    if (unknown_id_source_a3d290->unknown_223b) {
        progress = progress / 2;
    }
    if (ProgressScreen.Get_Progress(0) * 100.0 < progress) {
        ProgressScreen.Set_Progress_006201c0(0, progress, Point2D(-1, -1));
    }
    if (Players.Count() == 1) {
        return;
    }
    CDTimerClass<SystemTimerClass> timeout(240);
    switch (Type) {
    case 3:
    case 4: {
        UnknownGlobalPacket packet;
        memset(&packet, 0, sizeof(packet));
        packet.Command = 0x0F;
        packet.Progress.Percent = (int)(ProgressScreen.Get_Progress(0) * 100.0);
        strcpy(packet.Name, Unknown_006FA120(unknown_players_a3fa7c[0]->Name));
        if (packet.Progress.Percent < 99.95) {
            unknown_ipx_manager_a40978.Send_Global_Message(&packet, 0x33, 0, 0, 0, 0);
        } else {
            for (int i = 1; i < unknown_players_a3fa7c.Count(); i++) {
                Debug_Printf("Sending guarenteed progress message to all players\n");
                unknown_ipx_manager_a40978.unknown_5259a0(&packet, 0x33, 1, unknown_players_a3fa7c[i]->Name);
            }
        }
        unknown_481fb0();
        while (unknown_ipx_manager_a40978.Global_Num_Send() > 5 && timeout > 0) {
            Sleep(20);
            Unknown_005B5EE0();
            unknown_481fb0();
        }
        break;
    }
    case 1:
    case 2: {
        UnknownSerialPacket packet;
        memset(&packet, 0, sizeof(packet));
        packet.Command = 0x6C;
        packet.Progress = (int)(ProgressScreen.Get_Progress(0) * 100.0);
        packet.ID = (unsigned char)serial_local_player_00a3fb38;
        serial_manager_00a40a28.Send_Message(&packet, sizeof(packet), 0);
        serial_manager_00a40a28.Service();
        while (serial_manager_00a40a28.Num_Send() > 5 && timeout > 0) {
            Sleep(20);
            WWKeyboard->Check();
            serial_manager_00a40a28.Service();
        }
        break;
    }
    }
    unknown_481fb0();
}
// @ref ??_C@_0DE@JLNH@Sending?5guarenteed?5progress?5mess@=007f3b7c
// @ref __real@8@4005c7e6666666666800=007a96a0
// @ref __real@8@4005c800000000000000=0079b7f0
