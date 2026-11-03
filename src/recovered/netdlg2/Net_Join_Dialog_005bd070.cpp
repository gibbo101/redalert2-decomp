// bool Net_Join_Dialog_005bd070() (0x005BD070): the LAN join dialog's driver loop (Red Alert's
// Net_Join_Dialog, TibSun's Net2Remote_Connect): opens the join dialog 0xBB, pumps messages and the
// join queries until a button result arrives, then handles cancel/back (0x5C0, 2), join (0x6CD,
// 0x6CE), new game (0x6CC: the host dialog 0xBC), the guest's start (1 from 0xBD) and the host's
// GO (0x588). true when a game starts.
#include "shared/lobby.hpp"
#include "shared/win_util.hpp"
#include "shared/ipx_manager.hpp"
#include "shared/string_table.hpp"
#include "shared/debug_printf.hpp"
#include "shared/id_source.hpp"
#include "shared/session_state.hpp"
#include "shared/multiplayer_game_mode.hpp"
#include "shared/map_preview.hpp"
#include "shared/comm_buffer.hpp"
#include "shared/cd_timer.hpp"
#include "shared/crt_string.hpp"
#include "shared/modem_host.hpp"
#include "shared/win32_window.hpp"
// @ref ??_C@_0BG@PBPB@GUI?3HostGameStartHost?$AA@=007e6b5c
// @ref ??_C@_0BL@HPCJ@TXT_GAMENAME_MUSTBE_UNIQUE?$AA@=007e6b94
// @ref ??_C@_0BO@KNPM@Received?5READY_TO_GO?5packet?4?6?$AA@=007e6af8
// @ref ??_C@_0BP@JJMG@Received?5REQ_SCENARIO?5packet?4?6?$AA@=007e6b18
// @ref ??_C@_0CC@DLJC@About?5to?5wait?5for?5?8GO?8?5response?4@=007e6b38
// @ref ??_C@_0N@JOIL@TXT_ONLY_ONE?$AA@=007e6b84
// @ref ??_C@_0P@GEF@TXT_NAME_BLANK?$AA@=007e6bb0
// @ref ??_C@_0BH@KOPH@TXT_SCENARIO_TOO_SMALL?$AA@=007e24cc
// @ref ??_C@_0O@DPOL@GUI?3HostNoMap?$AA@=007e6b74
// @ref ??_C@_0BD@ELLL@D?3?2Ra2?2netdlg2?4cpp?$AA@=007e69c8

void __fastcall unknown_5eac30();
// @ref ?unknown_5eac30@@YIXXZ=005eac30
// The join dialog's packet pump (0x005C08A0), defined later in this unit.
void __fastcall Get_Join_Responses_005c08a0();
long __stdcall Host_Dialog_Proc_005befe0(HWND window, unsigned message, unsigned wparam, long lparam);
// @ref ?Host_Dialog_Proc_005befe0@@YGJPAUHWND__@@IIJ@Z=005befe0
// A joiner's start of the game: the scenario is found or fetched (NET_READY_TO_GO 0x13 to the host),
// the IPX timing is set from the response time; otherwise TXT_UNABLE_PLAY_WAAUGH and a sign-off
// (0x005BE3B0; from Red Alert's Net_Join_Dialog). The argument is unused (0 for join state 3, 1 for
// state 4). Declared here, its only caller: a new parameter in shared/lobby.hpp changes the code of
// Pick_Lobby 0x00744090 and Print_CRCs 0x0062A360.
bool __fastcall Start_Joined_Game_005be3b0(int unknown);
// Seats the first session player (the host) in a slot and makes it the current slot (0x005C8CD0).
void __fastcall Seat_First_Player_005c8cd0(int slot);
// @ref ?Seat_First_Player_005c8cd0@@YIXH@Z=005c8cd0
// @ref ?Unknown_005c3b70@@YIXXZ=005c3b70
// VersionClass::Version_Number (0x00712B50; declared only in the version unit, as Probe_Launcher_Registry 0x00491B70 does).
unsigned int __fastcall Unknown_Version_ID_00712b50(VersionClass *object);
// @ref ?Unknown_Version_ID_00712b50@@YIIPAVVersionClass@@@Z=00712b50
// The version the session plays against (session +0x63C; Red Alert's Session.PlayingAgainstVersion).
extern unsigned long unknown_version_a3d8d4;
// @ref ?unknown_version_a3d8d4@@3KA=00a3d8d4
extern int unknown_global_length_a3f808;
// @ref ?unknown_global_length_a3f808@@3HA=00a3f808
extern unsigned short unknown_global_product_a3f818;
// @ref ?unknown_global_product_a3f818@@3GA=00a3f818

bool __fastcall Net_Join_Dialog_005bd070()
{
    unknown_a71e9c = Unknown_006525F0();
    Read_Art_INI();
    unknown_a71ea0 = unknown_art_ini_unique_id();
    unknown_a71ea4 = unknown_ini_8397a0_unique_id();
    Get_Serial_005bce90(unknown_a71bc4);
    unknown_ipx_manager_a40978.Set_Timing(30, -1, 600, true);
    unknown_session_a3f614 = false;
    unknown_host_name_a3f618[0] = 0;
    unknown_session_a3f616 = true;
    unknown_lock_a71e98 = false;
    unknown_5eac30();
    HWND dialog = (HWND)unknown_create_dialog_735700(ProgramInstance, 0xBB, MainWindow, Join_Dialog_Proc_005be6b0, 0);
    unknown_show_dialog_5ff7e0(dialog, 0xBB);
    ShowWindow(dialog, 1);
    Unknown_005bbdd0(false);
    unknown_game_index_a71e90 = 0;
    unknown_lobby_result_a71e8c = 0;
    unknown_join_state_a71e94 = 0;
    unknown_join_list_7e699c = true;

    while (true) {
        while (unknown_lobby_result_a71e8c == 0) {
            unknown_ipx_manager_a40978.Service();
            Sleep(0);
            Service_Game_IO_00481fb0();
            unknown_ipx_manager_a40978.Service();
            unknown_517370(false);
            unknown_message_count_a52298++;
            MSG msg;
            while (unknown_peek_message_522ed0(&msg, 0, 0, 0, 1)) {
                TranslateMessage(&msg);
                DispatchMessageA(&msg);
            }
            Service_Game_IO_00481fb0();
            if (unknown_lobby_result_a71e8c != 0) {
                break;
            }
            if (Unknown_00735B10()) {
                Unknown_005c01d0(0, 0, 0, 0);
                Get_Join_Responses_005c08a0();
                if (Current_Dialog_Id_00735b20() == 0xBC) {
                    Unknown_005c3810(false, false);
                }
                Process_Timeouts_005bc500();
            }
        }

        if (unknown_lobby_result_a71e8c == 0x5C0 || unknown_lobby_result_a71e8c == 2) {
            unknown_session_a3d298.Write_MultiPlayer_Settings();
            if (Current_Dialog_Id_00735b20() == 0xBB) {
                if (unknown_join_state_a71e94 > 0) {
                    Unjoin_Game_005c00b0(unknown_game_index_a71e90);
                    unknown_ipx_manager_a40978.Service();
                }
                End_Dialog_007357e0(0, 0);
                Clear_Slot_Lists_005c8a70();
                Fill_Slots_005c8a10();
                Free_Pointers_005a7480(&unknown_players_a3fa7c);
                Free_Pointers_005a7480(&unknown_games_a3fa64);
                Free_Pointers_005a7480(&unknown_chat_a3fa4c);
                unknown_session_a3f616 = false;
                unknown_ipx_manager_a40978.Service();
                return false;
            }
            if (Current_Dialog_Id_00735b20() == 0xBC) {
                Unjoin_Game_005c00b0(unknown_game_index_a71e90);
                unknown_join_state_a71e94 = 0;
                End_Dialog_007357e0(Unknown_00735B10(), 0);
                Unknown_Reset_Slots_005c8a90();
                dialog = (HWND)unknown_create_dialog_735700(ProgramInstance, 0xBB, MainWindow, Join_Dialog_Proc_005be6b0, 0);
                unknown_show_dialog_5ff7e0(dialog, 0xBB);
                ShowWindow(dialog, 1);
                Unknown_005c01d0(0, 0, 1, 0);
            } else if (Current_Dialog_Id_00735b20() == 0xBD) {
                if (unknown_join_state_a71e94 == 2) {
                    Unjoin_Game_005c00b0(unknown_game_index_a71e90);
                    unknown_join_state_a71e94 = 0;
                } else {
                    UnknownGlobalPacket packet;
                    memset(&packet, 0, sizeof(packet));
                    packet.Command = 10;
                    strcpy(packet.Name, unknown_name_a3d3a0);
                    for (int i = 1; i < unknown_chat_a3fa4c.Count(); i++) {
                        unknown_ipx_manager_a40978.Send_Global_Message(&packet, sizeof(packet), 1, &unknown_chat_a3fa4c[i]->Address, 0, 0);
                        Service_Game_IO_00481fb0();
                    }
                    unknown_ipx_manager_a40978.Send_Global_Message(&packet, sizeof(packet), 0, 0, 0, 0);
                    if (unknown_dest_net_set_a3f604) {
                        unknown_ipx_manager_a40978.Send_Global_Message(&packet, sizeof(packet), 0, &unknown_dest_net_a3f608, 0, 0);
                    }
                }
                CDTimerClass<SystemTimerClass> timeout = 600;
                while (unknown_ipx_manager_a40978.Global_Num_Send() > 0) {
                    if (unknown_ipx_manager_a40978.Service() == 0) {
                        break;
                    }
                    if (timeout == 0) {
                        break;
                    }
                    Service_Game_IO_00481fb0();
                }
                unknown_host_name_a3f618[0] = 0;
                unknown_join_state_a71e94 = 0;
                End_Dialog_007357e0(0, 0);
                unknown_lobby_result_a71e8c = 0;
                unknown_game_index_a71e90 = 0;
                Free_Pointers_005a7480(&unknown_players_a3fa7c);
                Clear_Slot_Lists_005c8a70();
                Unknown_Reset_Slots_005c8a90();
                dialog = (HWND)unknown_create_dialog_735700(ProgramInstance, 0xBB, MainWindow, Join_Dialog_Proc_005be6b0, 0);
                unknown_show_dialog_5ff7e0(dialog, 0xBB);
                ShowWindow(dialog, 1);
            } else {
                if (unknown_join_state_a71e94 == 2) {
                    Unjoin_Game_005c00b0(unknown_game_index_a71e90);
                    unknown_join_state_a71e94 = 0;
                } else {
                    UnknownGlobalPacket packet;
                    memset(&packet, 0, sizeof(packet));
                    packet.Command = 10;
                    strcpy(packet.Name, unknown_name_a3d3a0);
                    for (int i = 1; i < unknown_chat_a3fa4c.Count(); i++) {
                        unknown_ipx_manager_a40978.Send_Global_Message(&packet, sizeof(packet), 1, &unknown_chat_a3fa4c[i]->Address, 0, 0);
                        Service_Game_IO_00481fb0();
                    }
                    unknown_ipx_manager_a40978.Send_Global_Message(&packet, sizeof(packet), 0, 0, 0, 0);
                    if (unknown_dest_net_set_a3f604) {
                        unknown_ipx_manager_a40978.Send_Global_Message(&packet, sizeof(packet), 0, &unknown_dest_net_a3f608, 0, 0);
                    }
                }
                CDTimerClass<SystemTimerClass> timeout = 600;
                while (unknown_ipx_manager_a40978.Global_Num_Send() > 0) {
                    if (unknown_ipx_manager_a40978.Service() == 0) {
                        break;
                    }
                    if (timeout == 0) {
                        break;
                    }
                    Service_Game_IO_00481fb0();
                }
                unknown_host_name_a3f618[0] = 0;
                unknown_join_state_a71e94 = 0;
                unknown_lobby_result_a71e8c = 0;
                unknown_game_index_a71e90 = 0;
                Free_Pointers_005a7480(&unknown_players_a3fa7c);
                Clear_Slot_Lists_005c8a70();
                Unknown_Reset_Slots_005c8a90();
                dialog = (HWND)unknown_create_dialog_735700(ProgramInstance, 0xBB, MainWindow, Join_Dialog_Proc_005be6b0, 0);
                unknown_show_dialog_5ff7e0(dialog, 0xBB);
                ShowWindow(dialog, 1);
            }
        }

        if (unknown_lobby_result_a71e8c == 0x6CD) {
            unknown_session_a3f614 = false;
            unknown_session_a3d298.Write_MultiPlayer_Settings();
            if (Request_To_Join_005bfc40(unknown_game_index_a71e90, unknown_a72c68 != 0)) {
                unknown_join_state_a71e94 = 1;
            } else {
                HWND top = Unknown_00735B10();
                if (top) {
                    EnableWindow(top, TRUE);
                    HWND button = GetDlgItem(top, 0x541);
                    if (button) {
                        EnableWindow(button, TRUE);
                    }
                }
            }
            if (unknown_session_a3d298.Mode) {
                unknown_session_a3d298.Mode->unknown_slot9();
            }
        }

        if (unknown_lobby_result_a71e8c == 0x6CE) {
            unknown_session_a3f614 = false;
            unknown_session_a3d298.Write_MultiPlayer_Settings();
            if (Request_To_Join_005bfc40(unknown_game_index_a71e90, true)) {
                unknown_join_state_a71e94 = 1;
            } else {
                HWND top = Unknown_00735B10();
                if (top) {
                    EnableWindow(top, TRUE);
                    HWND button = GetDlgItem(top, 0x541);
                    if (button) {
                        EnableWindow(button, TRUE);
                    }
                }
            }
            if (unknown_session_a3d298.Mode) {
                unknown_session_a3d298.Mode->unknown_slot9();
            }
        }

        if (unknown_lobby_result_a71e8c == 0x6CC) {
            bool ok = true;
            if (strlen(unknown_name_a3d3a0) < 1) {
                Message_Box_005c3230(StringTable::Load_String("TXT_NAME_BLANK", 0, "D:\\Ra2\\netdlg2.cpp", 0x623), 0, Unknown_005bbd10, false);
                ok = false;
            }
            for (int i = 0; i < unknown_games_a3fa64.Count(); i++) {
                if (ok && !_stricmp(Unknown_006FA120(unknown_games_a3fa64[i]->Name), unknown_name_a3d3a0)) {
                    Message_Box_005c3230(StringTable::Load_String("TXT_GAMENAME_MUSTBE_UNIQUE", 0, "D:\\Ra2\\netdlg2.cpp", 0x62D), 0, Unknown_005bbd10, false);
                    ok = false;
                    break;
                }
            }
            if (ok) {
                wcscpy(unknown_host_name_a3f618, Unknown_006FA180(unknown_name_a3d3a0));
                unknown_session_a3f616 = true;
                unknown_session_a3f614 = false;
                unknown_session_a3d2b4 = 0;
                unknown_version_a3d8d4 = Unknown_Version_ID_00712b50(&version_object_00a40c88);
                Select_Scenario_005c7c30(unknown_session_a3d2b4);
                End_Dialog_007357e0(0, 0);
                unknown_lobby_result_a71e8c = 0;
                Free_Pointers_005a7480(&unknown_players_a3fa7c);

                NodeNameType *who = new NodeNameType;
                memset(who, 0, sizeof(*who));
                wcscpy(who->Name, Unknown_006FA180(unknown_name_a3d3a0));
                strcpy(who->unknown_34, unknown_a71bc4);
                who->unknown_66e2d0(unknown_session_a3d298.Value_0124_006729f0());
                who->unknown_66e300(unknown_session_a3d298.Value_011c_00672a10());
                who->unknown_67 = 1;
                who->Team = 0;
                unknown_lobby_flag_7e6d90 = 7;
                if (unknown_a71e99) {
                    unknown_lobby_flag_7e6d90 = 0;
                    who->Team = -1;
                } else if (who->unknown_66e290() == -3) {
                    who->unknown_66e2d0(-2);
                }
                unknown_session_a3d298.Players.Add(who);
                if (unknown_session_a3d298.Mode) {
                    unknown_session_a3d298.Mode->unknown_slot9();
                }
                Clear_Slot_Lists_005c8a70();
                Unknown_Reset_Slots_005c8a90();
                Seat_First_Player_005c8cd0(0);
                if (unknown_lobby_flag_7e6d90 == 0) {
                    unknown_player_slots_a3fa98[0]->unknown_66e2d0(-3);
                    unknown_player_slots_a3fa98[0]->Team = -1;
                }
                unknown_join_state_a71e94 = 2;

                NodeNameType *game = new NodeNameType;
                wcscpy(game->Name, Unknown_006FA180(unknown_name_a3d3a0));
                game->Address = unknown_address_a3f80c;
                game->Game.IsOpen = true;
                game->Game.LastTime = TickCount.Time();
                unknown_session_a3d298.NodeList_27cc.Add(game);
                unknown_game_index_a71e90 = unknown_games_a3fa64.Count() - 1;

                HWND host = (HWND)unknown_create_dialog_735700(ProgramInstance, 0xBC, MainWindow, Host_Dialog_Proc_005befe0, 0);
                unknown_show_dialog_5ff7e0(host, 0xBC);
                SendMessageA(host, 0x4A9, 0, 1);
                ShowWindow(host, 1);
            } else {
                HWND top = Unknown_00735B10();
                if (top) {
                    EnableWindow(top, TRUE);
                    HWND button = GetDlgItem(top, 0x541);
                    if (button) {
                        EnableWindow(button, TRUE);
                    }
                }
            }
        }

        if (unknown_lobby_result_a71e8c == 1 && Current_Dialog_Id_00735b20() == 0xBD) {
            while (End_Dialog_007357e0(0, 0) == true) {
            }
            if (unknown_join_state_a71e94 == 3) {
                if (!Start_Joined_Game_005be3b0(0)) {
                    unknown_lobby_result_a71e8c = 2;
                    unknown_lock_a71e98 = false;
                    continue;
                }
                unknown_lock_a71e98 = true;
            } else if (unknown_join_state_a71e94 == 4) {
                Start_Joined_Game_005be3b0(1);
            }
            unknown_lobby_result_a71e8c = 0;
            Unknown_Pregame_Setup_005c74f0();
            unknown_session_a3d298.unknown_2cc = 5;
            unknown_a3fba4 = 0;
            unknown_session_a3d298.unknown_2e4 = 0;
            unknown_a3d580 = 0;
            if (unknown_session_a3d2ac == 2) {
                unknown_max_ahead_a3d560 = ((unknown_ipx_manager_a40978.unknown_526c30() / 8 + unknown_session_a3d298.unknown_2cc - 1) / unknown_session_a3d298.unknown_2cc) * unknown_session_a3d298.unknown_2cc > unknown_session_a3d298.unknown_2cc * 2 ? ((unknown_ipx_manager_a40978.unknown_526c30() / 8 + unknown_session_a3d298.unknown_2cc - 1) / unknown_session_a3d298.unknown_2cc) * unknown_session_a3d298.unknown_2cc : unknown_session_a3d298.unknown_2cc * 2;
            } else {
                unknown_max_ahead_a3d560 = (int)unknown_ipx_manager_a40978.unknown_526c30() / 8 > 2 ? (int)unknown_ipx_manager_a40978.unknown_526c30() / 8 : 2;
            }
            unknown_session_a3f616 = false;
            unknown_session_a3d298.Write_MultiPlayer_Settings();
            return true;
        }

        if (unknown_lobby_result_a71e8c == 0x588) {
            unknown_lock_a71e98 = false;
            unknown_session_a3d298.Write_MultiPlayer_Settings();
        }
        int count = unknown_players_a3fa7c.Count();
        int observers = 0;
        for (int i = 0; i < count; i++) {
            if (unknown_players_a3fa7c[i]->Team == -1) {
                observers++;
            }
        }
        if (unknown_lobby_result_a71e8c == 0x588) {
            if (count - observers <= 1) {
                Unknown_005C2C80(-1, StringTable::Load_String("TXT_ONLY_ONE", 0, "D:\\Ra2\\netdlg2.cpp", 0x6E0));
                unknown_lobby_result_a71e8c = 0;
                EnableWindow(GetDlgItem(Unknown_00735B10(), 0x588), TRUE);
            }
            if (unknown_lobby_result_a71e8c == 0x588) {
                bool nomap = false;
                for (int i = 1; i < count; i++) {
                    NodeNameType *player = unknown_players_a3fa7c[i];
                    if (player->unknown_map_state_6f == 0) {
                        Unknown_005C2C80(-1, StringTable::Load_String("GUI:HostNoMap", 0, "D:\\Ra2\\netdlg2.cpp", 0x6EC), player->Name, unknown_map_name_a3d342);
                        nomap = true;
                    }
                }
                if (nomap) {
                    unknown_lobby_result_a71e8c = 0;
                    EnableWindow(GetDlgItem(Unknown_00735B10(), 0x588), TRUE);
                }
            }
        }
        MultiplayerGameMode *mode = unknown_session_a3d298.Mode;
        if (unknown_lobby_result_a71e8c == 0x588) {
            int map_players = Unknown_005c6600(unknown_session_a3d2b4);
            if (map_players < unknown_session_a3d298.AICount - observers + count) {
                Unknown_005C2C80(-1, StringTable::Load_String("TXT_SCENARIO_TOO_SMALL", 0, "D:\\Ra2\\netdlg2.cpp", 0x6FF), map_players);
                EnableWindow(GetDlgItem(Unknown_00735B10(), 0x588), TRUE);
                unknown_lobby_result_a71e8c = 0;
            }
            {
                WideString message;
                if (!mode->unknown_slot5(&message)) {
                    Unknown_005C2C80(-1, message.Get());
                    EnableWindow(GetDlgItem(Unknown_00735B10(), 0x588), TRUE);
                    unknown_lobby_result_a71e8c = 0;
                }
            }
            if (unknown_lobby_result_a71e8c == 0x588) {
                for (int i = 0; i < count; i++) {
                    if (unknown_players_a3fa7c[i]->unknown_67 == 0) {
                        Unknown_005c3b70();
                        Unknown_005C2C80(-1, StringTable::Load_String("GUI:HostGameStartHost", 0, "D:\\Ra2\\netdlg2.cpp", 0x719));
                        unknown_lobby_result_a71e8c = 0;
                        EnableWindow(GetDlgItem(Unknown_00735B10(), 0x588), TRUE);
                        break;
                    }
                }
                if (unknown_lobby_result_a71e8c == 0x588) {
                    unknown_lock_a71e98 = true;
                    int i;
                    for (i = 0; i < unknown_players_a3fa7c.Count(); i++) {
                        if (unknown_players_a3fa7c[i]->Team == -1) {
                            unknown_players_a3fa7c[i]->unknown_66e300(-2);
                        }
                    }
                    mode->unknown_slot22();
                    unknown_session_a3d298.Unknown_00672BB0();
                    Unknown_005c3810(true, true);
                    {
                        UnknownGlobalPacket packet;
                        memset(&packet, 0, sizeof(packet));
                        packet.Command = 0x16;
                        strcpy(packet.Name, unknown_name_a3d3a0);
                        Unknown_Slot_Names_005c8cf0(packet.Slots.Names);
                        int players = unknown_players_a3fa7c.Count();
                        for (i = 1; i < players; i++) {
                            unknown_ipx_manager_a40978.Send_Global_Message(&packet, sizeof(packet), 1, &unknown_players_a3fa7c[i]->Address, 0, 0);
                            Service_Game_IO_00481fb0();
                        }
                    }
                    mode->unknown_slot21();
                    if (unknown_dialog_preview_a72ce8 != 0) {
                        delete unknown_dialog_preview_a72ce8;
                        unknown_dialog_preview_a72ce8 = 0;
                    }
                    Unknown_Pregame_Setup_005c74f0();
                    unknown_session_a3d298.unknown_2cc = 5;
                    unknown_a3fba4 = 0;
                    unknown_session_a3d298.unknown_2e4 = 0;
                    unknown_a3d580 = 0;
                    if (unknown_session_a3d2ac == 2) {
                        unknown_max_ahead_a3d560 = ((unknown_ipx_manager_a40978.unknown_526c30() / 8 + unknown_session_a3d298.unknown_2cc - 1) / unknown_session_a3d298.unknown_2cc) * unknown_session_a3d298.unknown_2cc > unknown_session_a3d298.unknown_2cc * 2 ? ((unknown_ipx_manager_a40978.unknown_526c30() / 8 + unknown_session_a3d298.unknown_2cc - 1) / unknown_session_a3d298.unknown_2cc) * unknown_session_a3d298.unknown_2cc : unknown_session_a3d298.unknown_2cc * 2;
                    } else {
                        unknown_max_ahead_a3d560 = (int)unknown_ipx_manager_a40978.unknown_526c30() / 8 > 2 ? (int)unknown_ipx_manager_a40978.unknown_526c30() / 8 : 2;
                    }
                    unknown_ipx_manager_a40978.Set_Timing(30 > unknown_ipx_manager_a40978.unknown_526c30() + 2 ? 30 : unknown_ipx_manager_a40978.unknown_526c30() + 2, -1, 600, true);

                    UnknownGlobalPacket packet;
                    memset(&packet, 0, sizeof(packet));
                    packet.Command = 0x0B;
                    packet.Progress.Percent = unknown_max_ahead_a3d560;   // NET_GO carries MaxAhead at +0x2F
                    for (i = 1; i < unknown_players_a3fa7c.Count(); i++) {
                        unknown_ipx_manager_a40978.Send_Global_Message(&packet, sizeof(packet), 1, &unknown_players_a3fa7c[i]->Address, 0, 0);
                    }

                    CDTimerClass<SystemTimerClass> timeout = 1200;
                    while (unknown_ipx_manager_a40978.Global_Num_Send() > 0 && !timeout) {
                        Service_Game_IO_00481fb0();
                    }

                    int responses[8];
                    memset(responses, 0, sizeof(responses));
                    int num_responses = 0;
                    bool send_scenario = false;
                    Debug_Printf("About to wait for 'GO' response.\n");
                    CDTimerClass<SystemTimerClass> response_timer;
                    response_timer = 600;
                    do {
                        Service_Game_IO_00481fb0();
                        if (unknown_ipx_manager_a40978.Get_Global_Message(&unknown_gpacket_a3f640, &unknown_global_length_a3f808, &unknown_address_a3f80c, &unknown_global_product_a3f818)
                            && unknown_global_product_a3f818 == 0xAA03) {
                            for (i = 1; i < unknown_players_a3fa7c.Count(); i++) {
                                if (unknown_players_a3fa7c[i]->Address == unknown_address_a3f80c) {
                                    if (!responses[i]) {
                                        if (unknown_gpacket_a3f640.Command == 0x10) {
                                            Debug_Printf("Received REQ_SCENARIO packet.\n");
                                            responses[i] = unknown_gpacket_a3f640.Command;
                                            send_scenario = true;
                                            num_responses++;
                                        }
                                        if (unknown_gpacket_a3f640.Command == 0x13) {
                                            Debug_Printf("Received READY_TO_GO packet.\n");
                                            responses[i] = unknown_gpacket_a3f640.Command;
                                            num_responses++;
                                        }
                                    }
                                }
                            }
                        }
                    } while (num_responses < unknown_players_a3fa7c.Count() - 1 && response_timer);

                    End_Dialog_007357e0(0, 0);
                    unknown_5159b0(0, true);
                    if (send_scenario) {
                        memset(unknown_session_a3d298.ScenarioRequests, 0, sizeof(unknown_session_a3d298.ScenarioRequests));
                        unknown_session_a3d298.RequestCount = 0;
                        for (i = 1; i < unknown_session_a3d298.Players.Count(); i++) {
                            if (responses[i] == 0x10) {
                                unknown_session_a3d298.ScenarioRequests[unknown_session_a3d298.RequestCount] = i;
                                unknown_session_a3d298.RequestCount++;
                            }
                        }
                        Send_Remote_File_0066bb20(unknown_id_source_a3d290->FileName, 3, false, true);
                    }
                    unknown_ipx_manager_a40978.Set_Timing(unknown_ipx_manager_a40978.unknown_526c30() + 2 > 30 ? unknown_ipx_manager_a40978.unknown_526c30() + 2 : 30,
                        -1, 120 > unknown_ipx_manager_a40978.unknown_526c30() * 8 ? 120 : unknown_ipx_manager_a40978.unknown_526c30() * 8, true);
                    break;
                }
            }
        }
        unknown_lobby_result_a71e8c = 0;
    }

    unknown_session_a3f616 = false;
    unknown_session_a3d298.Write_MultiPlayer_Settings();
    return true;
}
