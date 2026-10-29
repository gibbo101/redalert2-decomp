#define VECTOR_IMPLEMENT_VECTOR_ACCESSORS
#define VECTOR_IMPLEMENT_DYNAMIC_ACCESSORS
#define VECTOR_IMPLEMENT_DYNAMIC_ADD
#include "shared/modem_host.hpp"
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
#include "shared/unknown_player_entry.hpp"
#include "shared/campaign.hpp"
#include "shared/id_source.hpp"
#include "shared/special.hpp"
#include "shared/cd_timer.hpp"
#include "shared/ww_message_box.hpp"
#include "shared/multi_mission.hpp"
#include "shared/session_state.hpp"
// @ref ??_C@_0BC@FOEB@Received?5message?6?$AA@=007e2674
// @ref ??_C@_0BF@BAJ@Received?5GO?5message?6?$AA@=007e265c
// @ref ??_C@_0BK@MEMK@TXT_NO_EXPANSION_SCENARIO?$AA@=007e2640
// @ref ??_C@_0BL@MMBK@ModemHost?4StartGame?$CIexit?$CJ?6?$AA@=007e25dc
// @ref ??_C@_0BM@CEMH@ModemHost?4StartGame?$CIenter?$CJ?6?$AA@=007e26d4
// @ref ??_C@_0BM@FKCC@Waiting?5for?5?8GO?8?5response?4?6?$AA@=007e2688
// @ref ??_C@_0CB@OOII@?$CK?$CK?$CKGuest?5doesn?8t?5have?5scenario?$CB?6@=007e261c
// @ref ??_C@_0CD@LJGE@About?5to?5call?5?8Send_Remote_File?8@=007e25f8
// @ref ??_C@_0P@FLNF@TXT_WAITING_GO?$AA@=007e26a4
// @ref ??_C@_0P@HMGP@TXT_SENDING_GO?$AA@=007e26b4
// @ref ??_C@_0P@OCIN@LoadGame?5?$DN?5?$CFs?6?$AA@=007e26c4
// @ref ??_C@_04NCCD@true?$AA@=007d24d8
// @ref ??_C@_05NAGO@false?$AA@=007d24d0
// @ref ??_C@_0BE@EBDB@D?3?2Ra2?2ModemHst?4cpp?$AA@=007e247c
// @ref ??_C@_0L@NPIH@TXT_CANCEL?$AA@=007db8c8
// @ref ??_C@_13ECNF@?$AA?5?$AA?$AA@=007d64f4
extern "C" unsigned short *__cdecl wcscpy(unsigned short *dest, unsigned short const *source);

bool ModemHost::Start_Game_0059c290(bool load_game)
{
    Debug_Printf("ModemHost.StartGame(enter)\n");
    Debug_Printf("LoadGame = %s\n", load_game == true ? "true" : "false");
    if (load_game == true) {
        return false;
    }
    unknown_id_source_a3d290->TechLevel = unknown_session_a3d298.ScenarioIndex;
    strcpy(unknown_id_source_a3d290->FileName, unknown_session_a3d298.Scenarios[unknown_session_a3d298.ScenarioIndex]->unknown_58);
    unknown_id_source_a3d290->unknown_610 = 1;
    unknown_id_source_a3d290->Difficulty = 1;
    unknown_session_a3d55c = 0;
    NodeNameType *node = new NodeNameType;
    if (node) {
        wcscpy(node->Name, Unknown_006FA180(unknown_name_a3d3a0));
        node->unknown_4b = unknown_a3d3bc;
        node->unknown_53 = unknown_a3d3b4;
        node->unknown_63 = -1;
        unknown_players_a3fa7c.Add(node);
    }
    node = new NodeNameType;
    if (node) {
        wcscpy(node->Name, GuestName);
        node->unknown_4b = GuestHouse;
        node->unknown_53 = GuestColor;
        node->unknown_63 = -1;
        unknown_players_a3fa7c.Add(node);
    }
    if (unknown_players_a3fa7c.Count() != 2) {
        return false;
    }
    UnknownSerialPacket packet;
    memset(&packet, 0, sizeof(packet));
    packet.Command = 0x67;
    packet.Timing.ResponseTime = serial_manager_00a40a28.Response_Time();
    if (GuestResponseTime != 10000 && packet.Timing.ResponseTime < GuestResponseTime) {
        packet.Timing.ResponseTime = GuestResponseTime;
    }
    unknown_a40b18 = unknown_session_a3d298.GameSpeed_30;
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
    packet.ID = serial_local_player_00a3fb38;
    serial_manager_00a40a28.Send_Message(&packet, sizeof(packet), 1);
    HWND dialog = unknown_cancel_dialog_6001e0(
        StringTable::Load_String("TXT_SENDING_GO", 0, "D:\\Ra2\\ModemHst.cpp", 0x9EC), 0, 0);
    if (dialog) {
        unknown_dialog_5ff7c0(dialog);
    }
    unsigned long start = TickCount.Time();
    while ((serial_manager_00a40a28.Num_Send() && TickCount.Time() - start < 1800) || TickCount.Time() - start < 60) {
        Service_Game_IO_00481fb0();
        Unknown_005B5EE0();
        serial_manager_00a40a28.Service();
    }
    if (dialog) {
        unknown_set_dialog_item_5b0(dialog, (LPARAM)StringTable::Load_String("TXT_WAITING_GO", 0, "D:\\Ra2\\ModemHst.cpp", 0x9FD));
    }
    Debug_Printf("Waiting for 'GO' response.\n");
    start = TickCount.Time();
    do {
        Service_Game_IO_00481fb0();
        Unknown_005B5EE0();
        serial_manager_00a40a28.Service();
        UnknownSerialPacket reply;
        int length;
        if (serial_manager_00a40a28.Get_Message(&reply, &length) > 0) {
            Debug_Printf("Received message\n");
            if (reply.Command == 0x72) {
                Debug_Printf("Received GO message\n");
                break;
            }
            if (reply.Command == 0x73) {
                WWMessageBox(L" ").Process(StringTable::Load_String("TXT_NO_EXPANSION_SCENARIO", 0, "D:\\Ra2\\ModemHst.cpp", 0xA16),
                    StringTable::Load_String("TXT_CANCEL", 0, "D:\\Ra2\\ModemHst.cpp", 0xA16), 0, 0, 0);
                ReceiveTime = TickCount.Time();
                Debug_Printf("***Guest doesn't have scenario!\n");
                return false;
            }
            if (reply.Command == 0x6E) {
                Debug_Printf("About to call 'Send_Remote_File'.\n");
                Send_Remote_File_0066bb20(unknown_id_source_a3d290->FileName, 1, 0, 0);
                break;
            }
        }
    } while (TickCount.Time() - start < 1200);
    if (dialog) {
        unknown_dialog_5ff6e0(dialog);
    }
    serial_manager_00a40a28.Init_Send_Queue();
    unknown_session_a3f616 = 0;
    unknown_id_source_a3d290->TechLevel = unknown_session_a3d298.ScenarioIndex;
    unknown_session_a3d55c = unknown_players_a3fa7c.Count();
    Frame = 0;
    unknown_session_a3d2ac = 2;
    unknown_special_a40920.DestroyableBridges = unknown_session_a3d298.unknown_28;
    unknown_special_a40920.HarvesterImmune = unknown_session_a3d298.unknown_a5;
    unknown_special_a40920.TiberiumGrows = true;
    unknown_special_a40920.TiberiumSpreads = true;
    unknown_id_source_a3d290->Special().FixedAlliance = false;
    unknown_session_a3d298.unknown_a4 = true;
    unknown_special_a40920.Unknown_0068B410();
    Debug_Printf("ModemHost.StartGame(exit)\n");
    return true;
}
// @ref ??_EWstring@@QAEPAXI@Z=0040af40
// @ref ??_I@YGXPAXIHP6EX0@Z@Z=0040af00
