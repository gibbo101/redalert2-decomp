// ModemGuest::Process_Messages_00597680 (0x00597680)
#include "shared/modem_guest.hpp"
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
#include "shared/session_state.hpp"
// @ref ?Clip_Version_00713170@UnknownVersionObject@@QAEHKK@Z=00713170
// @ref ?Version_Protocol_00713130@UnknownVersionObject@@QAEHH@Z=00713130
// @ref ?unknown_a3fba4@@3HA=00a3fba4
// @ref ?version_object_00a40c88@@3UUnknownVersionObject@@A=00a40c88
// @ref ??_C@_06DN@TXT_OK?$AA@=007db8f4
// @ref ??_C@_0BB@BKJO@Received?5packet?6?$AA@=007e20c4
// @ref ??_C@_0BC@PPII@Received?5SignOff?6?$AA@=007e2218
// @ref ??_C@_0BE@IJFA@TXT_USER_SIGNED_OFF?$AA@=007e2204
// @ref ??_C@_0BE@PMHE@D?3?2Ra2?2ModemGst?4cpp?$AA@=007e2014
// @ref ??_C@_0BG@HINH@TXT_YOURGAME_OUTDATED?$AA@=007e21bc
// @ref ??_C@_0BG@LMNF@TXT_DESTGAME_OUTDATED?$AA@=007e21d4
// @ref ??_C@_0BH@HLKP@Received?5game?5options?6?$AA@=007e21ec
// @ref ??_C@_0BH@NCIJ@TXT_UNABLE_PLAY_WAAUGH?$AA@=007e2184
// @ref ??_C@_0BI@GJDM@Received?5timing?5packet?6?$AA@=007e2120
// @ref ??_C@_0BJ@KLKI@Received?5serial?5message?6?$AA@=007e2138
// @ref ??_C@_0BK@DBKP@Received?5own?5packet?5back?6?$AA@=007e2248
// @ref ??_C@_0BK@GPBE@TXT_SYSTEM_NOT_RESPONDING?$AA@=007e222c
// @ref ??_C@_0BO@MNHL@Received?5score?5screen?5packet?6?$AA@=007e2100
// @ref ??_C@_0CF@FCBJ@Received?5SERIAL_PREVIEW_MODE?5pac@=007e20d8
// @ref ??_C@_0CP@GEMF@Timeout?$CB?5?$CFd?5ticks?5since?5last?5inc@=007e2154
// @ref ??_C@_0M@FDHG@RandMap?4Sed?$AA@=007e16e8
// @ref ??_C@_0N@BAAD@TXT_MISMATCH?$AA@=007e21ac
// @ref ??_C@_0N@NADB@Received?5go?6?$AA@=007e219c
// @ref ??_C@_1BA@FNA@?$AA?$FL?$AA?$CF?$AAs?$AA?$FN?$AA?5?$AA?$CF?$AAs?$AA?$AA@=007e1e78
// @ref ?Compare_Narrow_00781f20@@YAHPBD0@Z=00781f20
// @ref ?Receive_Options_00597e50@ModemGuest@@QAE_NPBUUnknownSerialPacket@@@Z=00597e50
// @ref ?Receive_Preview_005989b0@ModemGuest@@QAEXXZ=005989b0
// @ref ?Service_Game_IO_00481fb0@@YIXXZ=00481fb0
// @ref ?Set_Host_00597130@ModemGuest@@QAEXPBGHH@Z=00597130
// @ref ?Show_Options_00597220@ModemGuest@@QAEXXZ=00597220
// @ref ?Start_Game_005986f0@ModemGuest@@QAE_N_N@Z=005986f0
// @ref ?Unknown_005C2DA0@@YIXHPBGPAUHWND__@@@Z=005c2da0
// @ref ?Unknown_006FA180@@YIPAGPBD@Z=006fa180
// @ref ?serial_local_player_00a3fb38@@3HA=00a3fb38
// @ref ?serial_manager_00a40a28@@3VNullModemClass@@A=00a40a28
// @ref ?unknown_color_7a737c@@3HA=007a737c
// @ref ?unknown_color_values_7e6d94@@3QBHB=007e6d94
// @ref ?unknown_id_source_a3d290@@3PAVUnknownIDSource@@A=00a3d290
// @ref ?unknown_math_4ba520@@YANN@Z=004ba520
// @ref ?unknown_math_4ba5b0@@YANN@Z=004ba5b0
// @ref ?unknown_session_a3d298@@3UUnknownSessionState@@A=00a3d298
// @ref ?unknown_session_a3d2ac@@3HA=00a3d2ac
// @ref ?unknown_sqrt_4ba410@@YANN@Z=004ba410
// @ref ??_C@_13ECNF@?$AA?5?$AA?$AA@=007d64f4
// @ref ?Find_Local_Scenario_0066c5b0@@YI_NPADH0_N1@Z=0066c5b0
// @ref ?Show_Chat_00598510@ModemGuest@@QAEXPBGH0@Z=00598510
// @ref ?Get_File_From_Host_0066aef0@@YI_NPADH_N@Z=0066aef0
// @ref ??_C@_13ECNF@?$AA?5?$AA?$AA@=007d64f4

bool ModemGuest::Process_Messages_00597680()
{
    UnknownSerialPacket packet;
    int length;
    serial_manager_00a40a28.Service();
    if (serial_manager_00a40a28.Get_Message(&packet, &length) > 0) {
        ReceiveTime = TickCount.Time();
        ReceiveTimeout = 1200;
        if (packet.Command >= 0x64 && packet.Command < 0x6D && packet.Command != 0x68
            && packet.ID == serial_local_player_00a3fb38) {
            Debug_Printf("Received own packet back\n");
            WWMessageBox(L" ").Process(StringTable::Load_String("TXT_SYSTEM_NOT_RESPONDING", 0, "D:\\Ra2\\ModemGst.cpp", 0x499),
                StringTable::Load_String("TXT_OK", 0, "D:\\Ra2\\ModemGst.cpp", 0x499), 0, 0, 0);
            return true;
        }
        switch (packet.Command) {
        case 0x66: {
            Debug_Printf("Received SignOff\n");
            unsigned long start = TickCount.Time();
            while (TickCount.Time() - start < 60) {
                Service_Game_IO_00481fb0();
                serial_manager_00a40a28.Service();
            }
            WWMessageBox(L" ").Process(StringTable::Load_String("TXT_USER_SIGNED_OFF", 0, "D:\\Ra2\\ModemGst.cpp", 0x4A9),
                StringTable::Load_String("TXT_OK", 0, "D:\\Ra2\\ModemGst.cpp", 0x4A9), 0, 0, 0);
            ReceiveTime = TickCount.Time();
            Shutdown_Modem();
            return true;
        }
        case 0x65: {
            Debug_Printf("Received game options\n");
            int version = version_object_00a40c88.Clip_Version_00713170(packet.Options.MinVersion, packet.Options.MaxVersion);
            if (version == 0) {
                WWMessageBox(L" ").Process(StringTable::Load_String("TXT_DESTGAME_OUTDATED", 0, "D:\\Ra2\\ModemGst.cpp", 0x4B9),
                    StringTable::Load_String("TXT_OK", 0, "D:\\Ra2\\ModemGst.cpp", 0x4B9), 0, 0, 0);
                ReceiveTime = TickCount.Time();
                return true;
            }
            if (version == -1) {
                WWMessageBox(L" ").Process(StringTable::Load_String("TXT_YOURGAME_OUTDATED", 0, "D:\\Ra2\\ModemGst.cpp", 0x4BF),
                    StringTable::Load_String("TXT_OK", 0, "D:\\Ra2\\ModemGst.cpp", 0x4BF), 0, 0, 0);
                ReceiveTime = TickCount.Time();
                return true;
            }
            bool match = true;
            if (packet.Options.Checksum != unknown_50) {
                match = false;
            }
            if (packet.Options.INIID != unknown_58) {
                match = false;
            }
            if (packet.Options.ArtID != unknown_54) {
                match = false;
            }
            if (!match) {
                WWMessageBox(L" ").Process(StringTable::Load_String("TXT_MISMATCH", 0, "D:\\Ra2\\ModemGst.cpp", 0x4EE),
                    StringTable::Load_String("TXT_OK", 0, "D:\\Ra2\\ModemGst.cpp", 0x4EE), 0, 0, 0);
                ReceiveTime = TickCount.Time();
                return true;
            }
            unknown_session_a3d2ac = version_object_00a40c88.Version_Protocol_00713130(version);
            unsigned short *host = Unknown_006FA180(packet.Name);
            Set_Host_00597130(host, packet.Options.Color, packet.Options.House);
            if (Receive_Options_00597e50(&packet) == true) {
                Show_Options_00597220();
            }
            break;
        }
        case 0x67:
        case 0x6B:
            Debug_Printf("Received go\n");
            if (Find_Local_Scenario_0066c5b0(unknown_session_a3d298.ScenarioFileName_658, unknown_session_a3d298.ScenarioFileLength_87c, unknown_session_a3d298.ScenarioDigest_85a, unknown_session_a3d298.ScenarioIsOfficial_880, true) == true) {
                UnknownSerialPacket reply;
                memset(&reply, 0, sizeof(reply));
                reply.Command = 0x72;
                serial_manager_00a40a28.Send_Message(&reply, sizeof(reply), 1);
            } else if (unknown_session_a3d298.ScenarioIsOfficial_880 && Compare_Narrow_00781f20(unknown_session_a3d298.ScenarioFileName_658, "RandMap.Sed")) {
                UnknownSerialPacket reply;
                memset(&reply, 0, sizeof(reply));
                reply.Command = 0x73;
                serial_manager_00a40a28.Send_Message(&reply, sizeof(reply), 1);
                Service_Game_IO_00481fb0();
                serial_manager_00a40a28.Service();
                WWMessageBox(L" ").Process(StringTable::Load_String("TXT_UNABLE_PLAY_WAAUGH", 0, "D:\\Ra2\\ModemGst.cpp", 0x51C),
                    StringTable::Load_String("TXT_OK", 0, "D:\\Ra2\\ModemGst.cpp", 0x51C), 0, 0, 0);
                ReceiveTime = TickCount.Time();
                return true;
            } else {
                if (!Get_File_From_Host_0066aef0(unknown_session_a3d298.ScenarioFileName_658, 1, false)) {
                    return true;
                }
                ReceiveTime = TickCount.Time();
            }
            strcpy(unknown_id_source_a3d290->FileName, unknown_session_a3d298.ScenarioFileName_658);
            unknown_session_a3d298.unknown_2cc = 5;
            unknown_a3fba4 = 0;
            unknown_session_a3d298.unknown_2e4 = 0;
            unknown_session_a3d298.unknown_2e8 = 0;
            if (unknown_session_a3d2ac == 2) {
                unsigned int ahead = ((packet.Timing.ResponseTime >> 3) + 4) / 5 * 5;
                if (ahead > 10) {
                    unknown_session_a3d298.MaxAhead_2c8 = ahead;
                } else {
                    unknown_session_a3d298.MaxAhead_2c8 = 10;
                }
            } else {
                unknown_session_a3d298.MaxAhead_2c8 = packet.Timing.ResponseTime >> 3;
                if ((int)unknown_session_a3d298.MaxAhead_2c8 <= 5) {
                    unknown_session_a3d298.MaxAhead_2c8 = 5;
                }
            }
            if (Start_Game_005986f0(packet.Command == 0x6B) == true) {
                Result = 1;
            } else {
                Result = 2;
            }
            break;
        case 0x68: {
            Debug_Printf("Received serial message\n");
            unsigned short *name = Unknown_006FA180(packet.Name);
            Show_Chat_00598510(name, packet.ID, packet.Message);
            Voc_Play(Rules->IncomingMessage, 1.0f, 0x2000, 0);
            break;
        }
        case 0x69:
            Debug_Printf("Received timing packet\n");
            break;
        case 0x6A:
            Debug_Printf("Received score screen packet\n");
            OptionsChanged = true;
            OptionsTime = TickCount.Time();
            break;
        case 0x75:
            Debug_Printf("Received SERIAL_PREVIEW_MODE packet\n");
            Receive_Preview_005989b0();
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
        WWMessageBox(L" ").Process(StringTable::Load_String("TXT_SYSTEM_NOT_RESPONDING", 0, "D:\\Ra2\\ModemGst.cpp", 0x56F),
            StringTable::Load_String("TXT_OK", 0, "D:\\Ra2\\ModemGst.cpp", 0x56F), 0, 0, 0);
        return true;
    }
    return false;
}

