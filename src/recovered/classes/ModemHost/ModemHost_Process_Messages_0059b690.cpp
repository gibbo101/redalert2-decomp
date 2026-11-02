// ModemHost::Process_Messages_0059b690 (0x0059B690)
#include "shared/modem_host.hpp"
#include "shared/queue.hpp"
#include "shared/serial_progress.hpp"
#include "shared/trigger_type.hpp"
#include "shared/lobby.hpp"
#include "shared/house_type.hpp"
#include "shared/rules.hpp"
#include "shared/sound_play.hpp"
#include "shared/ms_message_box.hpp"
#include "shared/comm_buffer.hpp"
#include "shared/null_dlg.hpp"
#include "shared/string_table.hpp"
#include "shared/keyboard.hpp"
#include "shared/map_preview.hpp"
#include "shared/options_dialog.hpp"
#include "shared/ww_message_box.hpp"
#include "shared/id_source.hpp"
// @ref ?Clip_Version_00713170@VersionClass@@QAEHKK@Z=00713170
// @ref ?Version_Protocol_00713130@VersionClass@@QAEHH@Z=00713130
// @ref ??_C@_13ECNF@?$AA?5?$AA?$AA@=007d64f4
// @ref ??_C@_06DN@TXT_OK?$AA@=007db8f4
// @ref ??_C@_0BB@BKJO@Received?5packet?6?$AA@=007e20c4
// @ref ??_C@_0BD@NMJA@Received?5SignOff?$CB?6?$AA@=007e2588
// @ref ??_C@_0BE@EBDB@D?3?2Ra2?2ModemHst?4cpp?$AA@=007e247c
// @ref ??_C@_0BE@IJFA@TXT_USER_SIGNED_OFF?$AA@=007e2204
// @ref ??_C@_0BG@HINH@TXT_YOURGAME_OUTDATED?$AA@=007e21bc
// @ref ??_C@_0BG@LMNF@TXT_DESTGAME_OUTDATED?$AA@=007e21d4
// @ref ??_C@_0BH@HLKP@Received?5game?5options?6?$AA@=007e21ec
// @ref ??_C@_0BI@GJDM@Received?5timing?5packet?6?$AA@=007e2120
// @ref ??_C@_0BJ@KHMC@Received?5Accept?5Options?6?$AA@=007e256c
// @ref ??_C@_0BJ@KLKI@Received?5serial?5message?6?$AA@=007e2138
// @ref ??_C@_0BK@GPBE@TXT_SYSTEM_NOT_RESPONDING?$AA@=007e222c
// @ref ??_C@_0BO@DHPD@Received?5our?5own?5packet?5back?6?$AA@=007e259c
// @ref ??_C@_0BO@MNHL@Received?5score?5screen?5packet?6?$AA@=007e2100
// @ref ??_C@_0CP@GEMF@Timeout?$CB?5?$CFd?5ticks?5since?5last?5inc@=007e2154
// @ref ??_C@_0N@BAAD@TXT_MISMATCH?$AA@=007e21ac
// @ref ?Send_Preview_0059c8b0@ModemHost@@QAEXXZ=0059c8b0
// @ref ?Service_Game_IO_00481fb0@@YIXXZ=00481fb0
// @ref ?Set_Guest_0059ab80@ModemHost@@QAEXPBGHH@Z=0059ab80
// @ref ?Show_Chat_0059c0b0@ModemHost@@QAEXPBGH0@Z=0059c0b0
// @ref ?Unknown_006FA180@@YIPAGPBD@Z=006fa180
// @ref ?serial_local_player_00a3fb38@@3HA=00a3fb38
// @ref ?serial_manager_00a40a28@@3VNullModemClass@@A=00a40a28
// @ref ?unknown_math_4ba520@@YANN@Z=004ba520
// @ref ?unknown_math_4ba5b0@@YANN@Z=004ba5b0
// @ref ?unknown_session_a3d2ac@@3HA=00a3d2ac
// @ref ?unknown_sqrt_4ba410@@YANN@Z=004ba410
// @ref ?version_object_00a40c88@@3VVersionClass@@A=00a40c88
// @ref? ??_C@_13ECNF@?$AA?5?$AA?$AA@ hits 007a0190 007a01f0 007a0250 007a02b0 007a0310

bool ModemHost::Process_Messages_0059b690(bool quiet)
{
    UnknownSerialPacket packet;
    int length;
    if (serial_manager_00a40a28.Get_Message(&packet, &length) > 0) {
        ReceiveTime = TickCount.Time();
        ReceiveTimeout = 1200;
        if (packet.Command >= 0x64 && packet.Command < 0x6D && packet.Command != 0x68
            && packet.ID == serial_local_player_00a3fb38) {
            Debug_Printf("Received our own packet back\n");
            if (!quiet) {
                WWMessageBox(L" ").Process(StringTable::Load_String("TXT_SYSTEM_NOT_RESPONDING", 0, "D:\\Ra2\\ModemHst.cpp", 0x7E2),
                    StringTable::Load_String("TXT_OK", 0, "D:\\Ra2\\ModemHst.cpp", 0x7E2), 0, 0, 0);
            }
            return true;
        }
        switch (packet.Command) {
        case 0x66: {
            Debug_Printf("Received SignOff!\n");
            unsigned long start = TickCount.Time();
            while (TickCount.Time() - start < 60) {
                Service_Game_IO_00481fb0();
                serial_manager_00a40a28.Service();
            }
            if (!quiet) {
                WWMessageBox(L" ").Process(StringTable::Load_String("TXT_USER_SIGNED_OFF", 0, "D:\\Ra2\\ModemHst.cpp", 0x7F6),
                    StringTable::Load_String("TXT_OK", 0, "D:\\Ra2\\ModemHst.cpp", 0x7F6), 0, 0, 0);
            }
            ReceiveTime = TickCount.Time();
            Shutdown_Modem();
            return true;
        }
        case 0x65: {
            Debug_Printf("Received game options\n");
            int version = version_object_00a40c88.Clip_Version_00713170(packet.Options.MinVersion, packet.Options.MaxVersion);
            if (version == 0) {
                if (!quiet) {
                    WWMessageBox(L" ").Process(StringTable::Load_String("TXT_DESTGAME_OUTDATED", 0, "D:\\Ra2\\ModemHst.cpp", 0x80B),
                        StringTable::Load_String("TXT_OK", 0, "D:\\Ra2\\ModemHst.cpp", 0x80B), 0, 0, 0);
                }
                ReceiveTime = TickCount.Time();
                return true;
            }
            if (version == -1) {
                if (!quiet) {
                    WWMessageBox(L" ").Process(StringTable::Load_String("TXT_YOURGAME_OUTDATED", 0, "D:\\Ra2\\ModemHst.cpp", 0x814),
                        StringTable::Load_String("TXT_OK", 0, "D:\\Ra2\\ModemHst.cpp", 0x814), 0, 0, 0);
                }
                ReceiveTime = TickCount.Time();
                return true;
            }
            bool match = true;
            if (packet.Options.Checksum != unknown_54) {
                match = false;
            }
            if (packet.Options.INIID != unknown_5c) {
                match = false;
            }
            if (packet.Options.ArtID != unknown_58) {
                match = false;
            }
            if (!match) {
                if (!quiet) {
                    WWMessageBox(L" ").Process(StringTable::Load_String("TXT_MISMATCH", 0, "D:\\Ra2\\ModemHst.cpp", 0x851),
                        StringTable::Load_String("TXT_OK", 0, "D:\\Ra2\\ModemHst.cpp", 0x851), 0, 0, 0);
                }
                ReceiveTime = TickCount.Time();
                return true;
            }
            unknown_session_a3d2ac = version_object_00a40c88.Version_Protocol_00713130(version);
            unsigned short *guest = Unknown_006FA180(packet.Name);
            Set_Guest_0059ab80(guest, packet.Options.Color, packet.Options.House);
            unknown_20 = true;
            break;
        }
        case 0x74:
            Debug_Printf("Received Accept Options\n");
            EnableWindow(GetDlgItem(Window, 1), 1);
            break;
        case 0x68: {
            Debug_Printf("Received serial message\n");
            unsigned short *name = Unknown_006FA180(packet.Name);
            Show_Chat_0059c0b0(name, packet.ID, packet.Message);
            if (!quiet) {
                Voc_Play(Rules->IncomingMessage, 1.0f, 0x2000, 0);
            }
            break;
        }
        case 0x69:
            Debug_Printf("Received timing packet\n");
            GuestResponseTime = packet.Timing.ResponseTime;
            if (!unknown_20) {
                OptionsChanged = true;
            }
            break;
        case 0x6A:
            Debug_Printf("Received score screen packet\n");
            break;
        case 0x77:
            Send_Preview_0059c8b0();
            ReceiveTime = TickCount.Time();
            break;
        default:
            Debug_Printf("Received packet\n");
            break;
        }
    }
    unsigned long elapsed = TickCount.Time() - ReceiveTime;
    if (elapsed > ReceiveTimeout) {
        Debug_Printf("Timeout! %d ticks since last incoming message\n", elapsed);
        if (!quiet) {
            WWMessageBox(L" ").Process(StringTable::Load_String("TXT_SYSTEM_NOT_RESPONDING", 0, "D:\\Ra2\\ModemHst.cpp", 0x895),
                StringTable::Load_String("TXT_OK", 0, "D:\\Ra2\\ModemHst.cpp", 0x895), 0, 0, 0);
        }
        return true;
    }
    return false;
}
