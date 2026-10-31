// void Unknown_005c7570(HWND dialog) (0x005C7570)
// Remakes the dialogs' map preview for the session's map. In a modem game (modes 1 and 2) a map
// that is not among the local maps makes the host send its preview (serial command 0x77, for at
// most 1800 ticks); in a LAN game (3) the setup dialog 0xBD asks the host the same (global
// command 0x1B); in a World Online game (4) with the dialog 0xC9 open a local map keeps (or,
// unless 0x00672140 holds, drops) the current preview. Otherwise the preview is made from the
// map file when it is present.
#include "shared/lobby.hpp"
#include "shared/ipx_manager.hpp"
#include "shared/ipx_address.hpp"
#include "shared/serial_progress.hpp"
#include "shared/system_timer.hpp"
#include "shared/cd_timer.hpp"
#include "shared/debug_printf.hpp"
#include "shared/raw_file_class.hpp"
#include "shared/cc_file_class.hpp"
#include "shared/map_preview.hpp"
#include "shared/crt_string.hpp"
#include "shared/queue.hpp"
#include "shared/mix_file_class.hpp"
// @ref ??_C@_04MJPP@?4MPR?$AA@=007e7118
// @ref ??_C@_0CJ@BALP@Checking?5for?5file?5?$CFs?5in?5local?5di@=007e7120
// @ref ?Unknown_0061E2A0@UnknownPreview_0061D430@@QAEXPBD@Z=0061e2a0

void __fastcall Unknown_005c7570(HWND dialog)
{
    delete unknown_dialog_preview_a72ce8;
    unknown_dialog_preview_a72ce8 = 0;
    switch (unknown_game_mode_a3d298) {
    case 3:
        if (Current_Dialog_Id_00735b20() == 0xBD
            && !Find_Local_Scenario_0066c5b0(unknown_session_a3d298.ScenarioFileName_658, unknown_session_a3d298.ScenarioFileLength_87c,
                unknown_session_a3d298.ScenarioDigest_85a, unknown_session_a3d298.ScenarioIsOfficial_880, false)) {
            InvalidateRect(dialog, 0, FALSE);
            UnknownGlobalPacket packet;
            memset(&packet, 0, sizeof(packet));
            packet.Command = 0x1B;
            for (;;) {
                int sent;
                if (unknown_game_mode_a3d298 == 3) {
                    sent = unknown_ipx_manager_a40978.Send_Global_Message(&packet, 0x2F, 1, &unknown_address_a3db2c, 0, 0);
                } else {
                    WOL::User *host = Unknown_0074DA60();
                    sent = 0;
                    if (host != 0) {
                        sent = unknown_ipx_manager_a40978.unknown_5259a0(&packet, 0x2F, 1, Unknown_006FA180(host->name));
                    }
                }
                if (sent) {
                    break;
                }
                Service_Game_IO_00481fb0();
            }
            while (unknown_ipx_manager_a40978.Global_Num_Send()) {
                Service_Game_IO_00481fb0();
            }
            return;
        }
        break;
    case 4:
        if (Find_Dialog_00735940(0xC9) != 0) {
            bool present = false;
            if (Find_Local_Scenario_0066c5b0(unknown_session_a3d298.ScenarioFileName_658, unknown_session_a3d298.ScenarioFileLength_87c,
                    unknown_session_a3d298.ScenarioDigest_85a, unknown_session_a3d298.ScenarioIsOfficial_880, false)) {
                // 128 is a hypothesis: VC6 shares the case buffers' frame slot with the tail's CCFileClass
                // temporary (frame 0x1F4) only for a name buffer of 125..200 bytes.
                char name[128];
                strcpy(name, unknown_session_a3d298.ScenarioFileName_658);
                _strupr(name);
                Debug_Printf("Checking for file %s in local directory\n", name);
                if (!unknown_session_a3d298.ScenarioIsOfficial_880 && strstr(name, ".MPR") != 0) {
                    break;
                }
                {
                    RawFileClass file(unknown_session_a3d298.ScenarioFileName_658);
                    if (file.Is_Available()) {
                        present = true;
                    }
                }
                if (!present) {
                    break;
                }
            }
            if (!unknown_session_a3d298.Unknown_00672140() && unknown_dialog_preview_a72ce8 != 0) {
                delete unknown_dialog_preview_a72ce8;
                unknown_dialog_preview_a72ce8 = 0;
                InvalidateRect(dialog, 0, FALSE);
                return;
            }
            InvalidateRect(dialog, 0, FALSE);
            return;
        }
        break;
    case 1:
    case 2:
        if (!Find_Local_Scenario_0066c5b0(unknown_session_a3d298.ScenarioFileName_658, unknown_session_a3d298.ScenarioFileLength_87c,
                unknown_session_a3d298.ScenarioDigest_85a, unknown_session_a3d298.ScenarioIsOfficial_880, false)) {
            UnknownSerialPacket packet;
            memset(&packet, 0, sizeof(packet));
            packet.Command = 0x77;
            CDTimerClass<SystemTimerClass> timer(1800);
            while (timer) {
                int sent = serial_manager_00a40a28.Send_Message(&packet, sizeof(packet), 1);
                while (serial_manager_00a40a28.Num_Send() > 0 && timer) {
                    Service_Game_IO_00481fb0();
                }
                if (sent) {
                    break;
                }
            }
            return;
        }
        break;
    }
    if (unknown_dialog_preview_a72ce8 != 0) {
        delete unknown_dialog_preview_a72ce8;
        unknown_dialog_preview_a72ce8 = 0;
    }
    bool missing = !CCFileClass(unknown_session_a3d298.ScenarioFileName_658).Is_Available();
    if (!missing) {
        unknown_dialog_preview_a72ce8 = new UnknownPreview_0061D430;
    }
    if (unknown_dialog_preview_a72ce8 != 0) {
        unknown_dialog_preview_a72ce8->Unknown_0061E2A0(unknown_session_a3d298.ScenarioFileName_658);
        InvalidateRect(dialog, 0, FALSE);
    }
}
