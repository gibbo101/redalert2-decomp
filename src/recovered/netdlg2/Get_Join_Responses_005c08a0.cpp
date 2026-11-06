// void Get_Join_Responses_005c08a0() (0x005C08A0): the join dialog's packet pump (TibSun netdlg2.cpp
// Get_Join_Responses): reads every global packet while no dialog result is pending, answers queries,
// tracks games, players and chat users, follows the join handshake and the game options, and
// refreshes the user and game lists at the end. __fastcall, as Net_Join_Dialog 0x005BD070 declares it
// (cdecl scores lower). Matching levers: the commands form one if/else-if chain (separate ifs ending in
// continue change the constant registers: 2 in edi, 8 in ebx); the inlined DynamicVectorClass Adds go
// through the session members (NodeList_27cc, Players, NodeList_27b4); the NET_ANSWER_GAME IsOpen store
// reads the packet through unknown_session_a3d298.GPacket, so it is not shared with the compare's load;
// the serial loop keeps TibSun's dups count (now unused); NET_MESSAGE reads the colour once.
#include "shared/lobby.hpp"
#include "shared/win_util.hpp"
#include "shared/ipx_manager.hpp"
#include "shared/string_table.hpp"
#include "shared/debug_printf.hpp"
#include "shared/session_state.hpp"
#include "shared/map_preview.hpp"
#include "shared/comm_buffer.hpp"
#include "shared/crt_string.hpp"
#include "shared/sound_play.hpp"
#include "shared/rules.hpp"
#include "shared/netdlg.hpp"
#include "shared/win32_window.hpp"
// @ref ??_C@_0BD@ELLL@D?3?2Ra2?2netdlg2?4cpp?$AA@=007e69c8

extern int unknown_global_length_a3f808;
// @ref ?unknown_global_length_a3f808@@3HA=00a3f808
extern unsigned short unknown_global_product_a3f818;
// @ref ?unknown_global_product_a3f818@@3GA=00a3f818
// Seats a player entry in a lobby slot (0x005C8CC0).
void __fastcall Set_Player_Slot_005c8cc0(int slot, NodeNameType *player);
// @ref ?Set_Player_Slot_005c8cc0@@YIXHPAUNodeNameType@@@Z=005c8cc0
// Seats the first session player (the host) in a slot and makes it the current slot (0x005C8CD0).
void __fastcall Seat_First_Player_005c8cd0(int slot);
// @ref ?Seat_First_Player_005c8cd0@@YIXH@Z=005c8cd0
// Applies the host's public game options (TibSun DecodePubGameopt; 0x005C3FF0).
bool __fastcall Decode_Pub_Gameopt_005c3ff0(char const *options, char const *name);
// @ref ?Decode_Pub_Gameopt_005c3ff0@@YI_NPBD0@Z=005c3ff0
// Enables the start control and clears the guests' ready flags (0x005C9700).
void Unknown_Enable_Start_005c9700();
// @ref ?Unknown_Enable_Start_005c9700@@YAXXZ=005c9700
// Frees the slot of a player that left (0x005C91C0).
void __fastcall Unknown_Release_Slot_005c91c0(IPXAddressClass &address);
// @ref ?Unknown_Release_Slot_005c91c0@@YIXAAVIPXAddressClass@@@Z=005c91c0
extern unsigned long unknown_version_a3d8d4;
// @ref ?unknown_version_a3d8d4@@3KA=00a3d8d4
extern "C" char *__cdecl _strdup(char const *string);
extern "C" char *__cdecl strtok(char *string, char const *delimiters);
extern "C" long __cdecl atol(char const *string);
extern "C" void __cdecl free(void *block);
// @ref ??_C@_0BC@NDCC@TXT_OBSERVER_FULL?$AA@=007e6cdc
// @ref ??_C@_0BD@CACI@TXT_GAME_CANCELLED?$AA@=007e6cc8
// @ref ??_C@_0BD@MDDN@TXT_REQUEST_DENIED?$AA@=007e6d18
// @ref ??_C@_0BG@GABH@TXT_S_FORMED_NEW_GAME?$AA@=007e6d54
// @ref ??_C@_0BH@EMGE@TXT_NAME_MUSTBE_UNIQUE?$AA@=007e6d00
// @ref ??_C@_0BJ@FACH@TXT_GAME_NOW_IN_PROGRESS?$AA@=007e6d38
// @ref ??_C@_0L@GBGI@New?5Player?$AA@=007e6d2c
// @ref ??_C@_0O@IOII@TXT_GAME_FULL?$AA@=007e6cf0
// @ref ??_C@_0P@EFOJ@TXT_SERIAL_DUP?$AA@=007e6cb8
// @ref ??_C@_0BG@HINH@TXT_YOURGAME_OUTDATED?$AA@=007e21bc
// @ref ??_C@_0BG@LMNF@TXT_DESTGAME_OUTDATED?$AA@=007e21d4
// @ref ??_C@_0N@BAAD@TXT_MISMATCH?$AA@=007e21ac
// @ref ??_C@_01KMAE@?0?$AA@=007ce9c0

void __fastcall Get_Join_Responses_005c08a0()
{
    NodeNameType *who;
    int i;
    int found;
    int why;
    wchar_t txt[80];
    bool display_users = false;
    bool display_games = false;

    while (unknown_lobby_result_a71e8c == 0) {
        Service_Game_IO_00481fb0();
        if (!unknown_ipx_manager_a40978.Get_Global_Message(&unknown_gpacket_a3f640, &unknown_global_length_a3f808, &unknown_address_a3f80c, &unknown_global_product_a3f818)) {
            break;
        }
        if (unknown_global_product_a3f818 != 0xAA03) {
            continue;
        }
        if (Answer_Query_005c05f0(&unknown_gpacket_a3f640, &unknown_address_a3f80c)) {
            continue;
        }

        // The commands of TibSun's Get_Join_Responses, in its order (RA2 adds the map preview,
        // slot and observer packets).
        if (unknown_gpacket_a3f640.Command == 0x19) {
            if (Current_Dialog_Id_00735b20() == 0xBD) {
                Download_Map_Preview_005c7970();
            }
        } else if (unknown_gpacket_a3f640.Command == 0x1B) {
            if (Current_Dialog_Id_00735b20() == 0xBC) {
                Unknown_Enable_Start_005c9700();
                display_users = true;
                unknown_dialog_preview_a72ce8->unknown_005c7ef0();
            }
        } else if (unknown_gpacket_a3f640.Command == 1) {
            // NET_ANSWER_GAME
            found = 0;
            for (i = 1; i < unknown_games_a3fa64.Count(); i++) {
                if (!_stricmp(Unknown_006FA120(unknown_games_a3fa64[i]->Name), unknown_gpacket_a3f640.Name)) {
                    found = 1;
                    unknown_games_a3fa64[i]->Game.LastTime = TickCount.Time();
                    if (unknown_games_a3fa64[i]->Game.IsOpen != unknown_gpacket_a3f640.GameInfo.IsOpen) {
                        display_games = true;
                        unknown_games_a3fa64[i]->Game.IsOpen = unknown_session_a3d298.GPacket.GameInfo.IsOpen;
                        if (unknown_games_a3fa64[i]->Game.IsOpen) {
                            unknown_games_a3fa64[i]->Address = unknown_address_a3f80c;
                        }
                        if (unknown_join_state_a71e94 < 2) {
                            if (unknown_games_a3fa64[i]->Game.IsOpen) {
                                swprintf(txt, StringTable::Load_String("TXT_S_FORMED_NEW_GAME", 0, "D:\\Ra2\\netdlg2.cpp", 0xF64), Unknown_006FA180(unknown_gpacket_a3f640.Name));
                                Voc_Play(Rules->GameForming, 1.0f, 0x2000, 0);
                            } else {
                                swprintf(txt, StringTable::Load_String("TXT_GAME_NOW_IN_PROGRESS", 0, "D:\\Ra2\\netdlg2.cpp", 0xF69), Unknown_006FA180(unknown_gpacket_a3f640.Name));
                                Voc_Play(Rules->GameClosed, 1.0f, 0x2000, 0);
                            }
                            Unknown_005C2C80(unknown_color_7a7360, txt);
                        }
                    }
                    break;
                }
            }
            if (found == 0) {
                who = new NodeNameType;
                wcscpy(who->Name, Unknown_006FA180(unknown_gpacket_a3f640.Name));
                who->Address = unknown_address_a3f80c;
                who->Game.IsOpen = unknown_gpacket_a3f640.GameInfo.IsOpen;
                who->Game.LastTime = TickCount.Time();
                unknown_session_a3d298.NodeList_27cc.Add(who);
                for (i = 1; i < unknown_chat_a3fa4c.Count(); i++) {
                    if (unknown_chat_a3fa4c[i]->Address == unknown_address_a3f80c) {
                        delete unknown_chat_a3fa4c[i];
                        unknown_chat_a3fa4c.Delete(unknown_chat_a3fa4c[i]);
                        break;
                    }
                }
                if (unknown_gpacket_a3f640.GameInfo.IsOpen && unknown_join_state_a71e94 < 2) {
                    swprintf(txt, StringTable::Load_String("TXT_S_FORMED_NEW_GAME", 0, "D:\\Ra2\\netdlg2.cpp", 0xF92), Unknown_006FA180(unknown_gpacket_a3f640.Name));
                    Unknown_005C2C80(unknown_color_7a7360, txt);
                    Voc_Play(Rules->GameForming, 1.0f, 0x2000, 0);
                }
                display_users = true;
                display_games = true;
            }
        } else if (unknown_gpacket_a3f640.Command == 3) {
            // NET_ANSWER_PLAYER
            found = 0;
            for (i = 0; i < unknown_players_a3fa7c.Count(); i++) {
                if (unknown_players_a3fa7c[i]->Address == unknown_address_a3f80c) {
                    found = 1;
                    break;
                }
            }
            if (unknown_games_a3fa64.Count() && unknown_gpacket_a3f640.PlayerInfo.unknown_37 != (int)Compute_Name_CRC(unknown_host_name_a3f618)) {
                found = 1;
            }
            if (!_stricmp(unknown_name_a3d3a0, unknown_gpacket_a3f640.Name)) {
                found = 1;
            }
            if (found == 0) {
                who = new NodeNameType;
                memset(who, 0, sizeof(*who));
                wcscpy(who->Name, Unknown_006FA180(unknown_gpacket_a3f640.Name));
                strcpy(who->unknown_34, unknown_gpacket_a3f640.unknown_18);
                who->Address = unknown_address_a3f80c;
                who->unknown_66e2d0(unknown_gpacket_a3f640.PlayerInfo.unknown_2f);
                who->unknown_66e300(unknown_gpacket_a3f640.PlayerInfo.unknown_33);
                if (unknown_gpacket_a3f640.PlayerInfo.Observer) {
                    who->Team = -1;
                }
                unknown_session_a3d298.Players.Add(who);
                Set_Player_Slot_005c8cc0(unknown_gpacket_a3f640.PlayerInfo.Slot, who);
                for (i = 1; i < unknown_chat_a3fa4c.Count(); i++) {
                    if (unknown_chat_a3fa4c[i]->Address == unknown_address_a3f80c) {
                        delete unknown_chat_a3fa4c[i];
                        unknown_chat_a3fa4c.Delete(unknown_chat_a3fa4c[i]);
                        break;
                    }
                }
                Unknown_Enable_Start_005c9700();
                HWND dialog = Find_Dialog_00735940(0xBD);
                Unknown_005cd030(dialog, true);
                Debug_Printf("New Player");
                display_users = true;
                if (unknown_join_state_a71e94 >= 2) {
                    Voc_Play(Rules->PlayerJoined, 1.0f, 0x2000, 0);
                }
            }
        } else if (unknown_gpacket_a3f640.Command == 0x16) {
            if (!Is_Host_005c86a0()) {
                Set_Slot_Names_005c8dd0(unknown_gpacket_a3f640.Slots.Names);
                display_users = true;
            }
        } else if (unknown_gpacket_a3f640.Command == 0x28) {
            if (!Is_Host_005c86a0()) {
                Unknown_005c3c20();
            }
        } else if (unknown_gpacket_a3f640.Command == 7) {
            // NET_CONFIRM_JOIN
            if (unknown_join_state_a71e94 != 2) {
                wcscpy(unknown_host_name_a3f618, Unknown_006FA180(unknown_gpacket_a3f640.Name));
                unknown_session_a3d298.Set_Value_00672a30(unknown_gpacket_a3f640.PlayerInfo.unknown_2f, false);
                unknown_session_a3d298.Set_Value_00672ae0(unknown_gpacket_a3f640.PlayerInfo.unknown_33, false);
                unknown_join_state_a71e94 = 2;
                unknown_address_a3db2c = unknown_address_a3f80c;
                Free_Pointers_005a7480(&unknown_players_a3fa7c);
                who = new NodeNameType;
                memset(who, 0, sizeof(*who));
                wcscpy(who->Name, Unknown_006FA180(unknown_name_a3d3a0));
                who->unknown_66e2d0(unknown_session_a3d298.Value_0124_006729f0());
                who->unknown_66e300(unknown_session_a3d298.Value_011c_00672a10());
                unknown_lobby_flag_7e6d90 = unknown_gpacket_a3f640.PlayerInfo.Observer;
                if (unknown_gpacket_a3f640.PlayerInfo.Slot == unknown_gpacket_a3f640.PlayerInfo.Observer && unknown_gpacket_a3f640.PlayerInfo.unknown_2f == -3) {
                    who->Team = -1;
                }
                unknown_session_a3d298.Players.Add(who);
                unknown_join_list_7e699c = false;
                End_Dialog_007357e0(0, 0);
                unknown_lobby_result_a71e8c = 0;
                Clear_Slot_Lists_005c8a70();
                Unknown_Reset_Slots_005c8a90();
                Seat_First_Player_005c8cd0(unknown_gpacket_a3f640.PlayerInfo.Slot);
                HWND dialog = (HWND)unknown_create_dialog_735700(ProgramInstance, 0xBD, MainWindow, Join_Lobby_Dialog_Proc_005c2330, 0);
                unknown_show_dialog_5ff7e0(dialog, 0xBD);
                ShowWindow(dialog, 1);
                display_users = true;
                Unknown_005c01d0(1, 1, 1, 0);
            }
        } else if (unknown_gpacket_a3f640.Command == 8) {
            // NET_REJECT_JOIN
            why = 0;
            if (unknown_join_state_a71e94 == 2) {
                UnknownGlobalPacket packet;
                memset(&packet, 0, sizeof(packet));
                packet.Command = 10;
                strcpy(packet.Name, unknown_name_a3d3a0);
                for (i = 1; i < unknown_players_a3fa7c.Count(); i++) {
                    unknown_ipx_manager_a40978.Send_Global_Message(&packet, sizeof(packet), 1, &unknown_players_a3fa7c[i]->Address, 0, 0);
                    Service_Game_IO_00481fb0();
                }
                unknown_ipx_manager_a40978.Send_Global_Message(&packet, sizeof(packet), 0, 0, 0, 0);
                if (unknown_dest_net_set_a3f604) {
                    unknown_ipx_manager_a40978.Send_Global_Message(&packet, sizeof(packet), 0, &unknown_dest_net_a3f608, 0, 0);
                }
                while (unknown_ipx_manager_a40978.Global_Num_Send() > 0 && unknown_ipx_manager_a40978.Service() != 0) {
                    Service_Game_IO_00481fb0();
                }
                unknown_host_name_a3f618[0] = 0;
                Clear_Slot_Lists_005c8a70();
                Fill_Slots_005c8a10();
                Free_Pointers_005a7480(&unknown_players_a3fa7c);
                Free_Pointers_005a7480(&unknown_chat_a3fa4c);
                unknown_game_index_a71e90 = 0;
                unknown_join_list_7e699c = true;
                unknown_join_state_a71e94 = -1;
                why = 4;
                display_users = true;
            } else if (unknown_join_state_a71e94 == 1) {
                why = unknown_gpacket_a3f640.Reject.Why;
                unknown_join_state_a71e94 = -1;
            }
            if (unknown_join_state_a71e94 == -1) {
                Unknown_005C2C80(unknown_color_7a7360, StringTable::Load_String("TXT_REQUEST_DENIED", 0, "D:\\Ra2\\netdlg2.cpp", 0x108F));
                Voc_Play(Rules->SystemError, 1.0f, 0x2000, 0);
                wchar_t const *item = 0;
                if (why == 0) {
                    item = StringTable::Load_String("TXT_NAME_MUSTBE_UNIQUE", 0, "D:\\Ra2\\netdlg2.cpp", 0x1095);
                } else if (why == 1) {
                    if (unknown_a72c68 == 0) {
                        item = StringTable::Load_String("TXT_GAME_FULL", 0, "D:\\Ra2\\netdlg2.cpp", 0x1097);
                    } else {
                        item = StringTable::Load_String("TXT_OBSERVER_FULL", 0, "D:\\Ra2\\netdlg2.cpp", 0x1099);
                    }
                } else if (why == 2) {
                    item = StringTable::Load_String("TXT_YOURGAME_OUTDATED", 0, "D:\\Ra2\\netdlg2.cpp", 0x109B);
                } else if (why == 3) {
                    item = StringTable::Load_String("TXT_DESTGAME_OUTDATED", 0, "D:\\Ra2\\netdlg2.cpp", 0x109D);
                } else if (why == 6) {
                    item = StringTable::Load_String("TXT_MISMATCH", 0, "D:\\Ra2\\netdlg2.cpp", 0x109F);
                } else if (why == 5) {
                    item = StringTable::Load_String("TXT_GAME_CANCELLED", 0, "D:\\Ra2\\netdlg2.cpp", 0x10A1);
                } else if (why == 7) {
                    item = StringTable::Load_String("TXT_SERIAL_DUP", 0, "D:\\Ra2\\netdlg2.cpp", 0x10A3);
                }
                if (item) {
                    Message_Box_005c3230(item, 0, Unknown_005bbd10, false);
                }
                if (Current_Dialog_Id_00735b20() == 0xBB) {
                    HWND window = Unknown_00735B10();
                    if (window) {
                        EnableWindow(window, TRUE);
                        HWND button = GetDlgItem(window, 0x541);
                        if (button) {
                            EnableWindow(button, TRUE);
                        }
                    }
                } else {
                    unknown_lobby_result_a71e8c = 2;
                }
                Unknown_005c01d0(0, 0, 1, 0);
            }
        } else if (unknown_gpacket_a3f640.Command == 0x17) {
            // NET_PUB_GAMEOPT
            for (i = 0; i < unknown_players_a3fa7c.Count(); i++) {
                if (!_stricmp(Unknown_006FA120(unknown_players_a3fa7c[i]->Name), unknown_gpacket_a3f640.Name)) {
                    if (i != -1 && !unknown_lock_a71e98) {
                        Decode_Pub_Gameopt_005c3ff0(&unknown_gpacket_a3f640.unknown_2f[0], unknown_gpacket_a3f640.Name);
                    }
                    break;
                }
            }
        } else if (unknown_gpacket_a3f640.Command == 0x18) {
            // NET_PRIV_GAMEOPT
            char *opts = _strdup(&unknown_gpacket_a3f640.unknown_2f[1]);
            for (i = 0; i < 8; i++) {
                char *name = Unknown_006FA120(unknown_player_slots_a3fa98[i]->Name);
                if (!_stricmp(name, unknown_gpacket_a3f640.Name)) {
                    if (i != -1 && !unknown_lock_a71e98) {
                        char *tok = strtok(opts, ",");
                        int newhouse = 0;
                        if (tok) {
                            newhouse = atol(tok);
                        }
                        tok = strtok(0, ",");
                        int newcolor = 0;
                        if (tok) {
                            newcolor = atol(tok);
                        }
                        HWND dialog = Find_Dialog_00735940(0xBC);
                        if (!dialog) {
                            dialog = Find_Dialog_00735940(0xBD);
                        }
                        bool house_changed = unknown_player_slots_a3fa98[i]->unknown_66e290() != newhouse;
                        if (house_changed) {
                            unknown_player_slots_a3fa98[i]->unknown_66e2d0(newhouse);
                        }
                        bool color_changed = unknown_player_slots_a3fa98[i]->Get_Color_0066e2a0() != newcolor;
                        if (color_changed) {
                            if (unknown_session_a3d298.Unknown_006728D0(newcolor)) {
                                newcolor = -2;
                            }
                            unknown_player_slots_a3fa98[i]->unknown_66e300(newcolor);
                        }
                        if (house_changed || color_changed) {
                            display_users = true;
                            Unknown_005c3810(true, false);
                        }
                    }
                    break;
                }
            }
            free(opts);
        } else if (unknown_gpacket_a3f640.Command == 10) {
            // NET_SIGN_OFF
            for (i = 1; i < unknown_games_a3fa64.Count(); i++) {
                if (!_stricmp(Unknown_006FA120(unknown_games_a3fa64[i]->Name), unknown_gpacket_a3f640.Name) && unknown_games_a3fa64[i]->Address == unknown_address_a3f80c) {
                    if (i == unknown_game_index_a71e90) {
                        Clear_Slot_Lists_005c8a70();
                        Fill_Slots_005c8a10();
                        Free_Pointers_005a7480(&unknown_players_a3fa7c);
                        if (Current_Dialog_Id_00735b20() != 0xBB && Current_Dialog_Id_00735b20() == 0xBD) {
                            unknown_lobby_result_a71e8c = 2;
                        }
                    }
                    if (unknown_join_state_a71e94 > 0 && i == unknown_game_index_a71e90) {
                        unknown_join_state_a71e94 = -1;
                        why = 5;
                    }
                    delete unknown_games_a3fa64[i];
                    unknown_games_a3fa64.Delete(unknown_games_a3fa64[i]);
                    unknown_game_index_a71e90 = i - 1;
                    display_games = true;
                    Unknown_005c01d0(0, 1, 1, 0);
                }
            }
            bool player_removed = false;
            Unknown_Release_Slot_005c91c0(unknown_address_a3f80c);
            for (i = 0; i < unknown_players_a3fa7c.Count(); i++) {
                if (unknown_players_a3fa7c[i]->Address == unknown_address_a3f80c) {
                    delete unknown_players_a3fa7c[i];
                    unknown_players_a3fa7c.Delete(unknown_players_a3fa7c[i]);
                    player_removed = true;
                    if (unknown_join_state_a71e94 >= 2) {
                        Voc_Play(Rules->PlayerLeft, 1.0f, 0x2000, 0);
                    }
                }
            }
            for (i = 1; i < unknown_chat_a3fa4c.Count(); i++) {
                if (unknown_chat_a3fa4c[i]->Address == unknown_address_a3f80c) {
                    delete unknown_chat_a3fa4c[i];
                    unknown_chat_a3fa4c.Delete(unknown_chat_a3fa4c[i]);
                }
            }
            if (player_removed) {
                Unknown_Enable_Start_005c9700();
                HWND dialog = Find_Dialog_00735940(0xBD);
                Unknown_005cd030(dialog, true);
                if (Current_Dialog_Id_00735b20() == 0x6B) {
                    HWND window = Unknown_00735B10();
                    int index = SendDlgItemMessageA(window, 0x6EB, 0x188, 0, 0);
                    if (index != -1) {
                        MultiplayerGameMode *row = (MultiplayerGameMode *)SendDlgItemMessageA(window, 0x6EB, 0x199, index, 0);
                        row->unknown_slot30();
                    }
                } else {
                    unknown_session_a3d298.Mode->unknown_slot30();
                }
            }
            display_users = true;
        } else if (unknown_gpacket_a3f640.Command == 0xB || unknown_gpacket_a3f640.Command == 0xE) {
            // NET_GO, NET_LOADGAME
            if (unknown_join_state_a71e94 == 2) {
                unknown_max_ahead_a3d560 = unknown_gpacket_a3f640.Progress.Percent;
                unknown_address_a3db2c = unknown_address_a3f80c;
                unknown_session_a3d55c = unknown_players_a3fa7c.Count();
                unknown_lobby_result_a71e8c = 1;
                if (unknown_gpacket_a3f640.Command == 0xB) {
                    unknown_join_state_a71e94 = 3;
                } else if (unknown_gpacket_a3f640.Command == 0xE) {
                    unknown_join_state_a71e94 = 4;
                }
            }
        } else if (unknown_gpacket_a3f640.Command == 4) {
            // NET_CHAT_ANNOUNCE
            if (unknown_gpacket_a3f640.Chat.ID == unknown_session_a3d298.UniqueID) {
                continue;
            }
            found = 0;
            for (i = 0; i < unknown_chat_a3fa4c.Count(); i++) {
                if (unknown_chat_a3fa4c[i]->Address == unknown_address_a3f80c) {
                    wcscpy(unknown_chat_a3fa4c[i]->Name, Unknown_006FA180(unknown_gpacket_a3f640.Name));
                    unknown_chat_a3fa4c[i]->Chat.LastTime = TickCount.Time();
                    unknown_chat_a3fa4c[i]->Chat.LastChance = 0;
                    unknown_chat_a3fa4c[i]->Chat.Color = unknown_gpacket_a3f640.Chat.Color;
                    found = 1;
                    if (unknown_game_index_a71e90 == 0) {
                        display_users = true;
                    }
                    break;
                }
            }
            if (!found) {
                who = new NodeNameType;
                wcscpy(who->Name, Unknown_006FA180(unknown_gpacket_a3f640.Name));
                who->Address = unknown_address_a3f80c;
                who->Chat.LastTime = TickCount.Time();
                who->Chat.LastChance = 0;
                who->Chat.Color = unknown_gpacket_a3f640.Chat.Color;
                unknown_session_a3d298.NodeList_27b4.Add(who);
                if (unknown_game_index_a71e90 == 0) {
                    display_users = true;
                }
            }
        } else if (unknown_gpacket_a3f640.Command == 5) {
            // NET_CHAT_REQUEST
            if (unknown_join_state_a71e94 != 1 && unknown_join_state_a71e94 != 2) {
                UnknownGlobalPacket packet;
                memset(&packet, 0, sizeof(packet));
                packet.Command = 4;
                strcpy(packet.Name, unknown_name_a3d3a0);
                packet.Chat.ID = unknown_session_a3d298.UniqueID;
                packet.Chat.Color = unknown_a3d3b4;
                unknown_ipx_manager_a40978.Send_Global_Message(&packet, sizeof(packet), 1, &unknown_address_a3f80c, 0, 0);
                Service_Game_IO_00481fb0();
            }
        } else if (unknown_gpacket_a3f640.Command == 12) {
            // NET_MESSAGE
            int color = unknown_gpacket_a3f640.Message.unknown_110;
            if (unknown_join_state_a71e94 == 2) {
                if (unknown_gpacket_a3f640.Message.unknown_114 == (int)Compute_Name_CRC(unknown_host_name_a3f618)) {
                    Unknown_005C2C80(color, L"[%s] %s", Unknown_006FA180(unknown_gpacket_a3f640.Name), unknown_gpacket_a3f640.Message.Buf);
                    Voc_Play(Rules->IncomingMessage, 1.0f, 0x2000, 0);
                }
            } else {
                Unknown_005C2C80(color, L"[%s] %s", Unknown_006FA180(unknown_gpacket_a3f640.Name), unknown_gpacket_a3f640.Message.Buf);
                Voc_Play(Rules->IncomingMessage, 1.0f, 0x2000, 0);
            }
        } else if (unknown_gpacket_a3f640.Command == 6) {
            // NET_QUERY_JOIN
            UnknownGlobalPacket packet;
            if (!unknown_players_a3fa7c.Count()) {
                memset(&packet, 0, sizeof(packet));
                packet.Command = 8;
                packet.Reject.Why = 5;
                unknown_ipx_manager_a40978.Send_Global_Message(&packet, sizeof(packet), 1, &unknown_address_a3f80c, 0, 0);
            } else {
            found = 0;
            int resend = 0;
            for (i = 1; i < unknown_players_a3fa7c.Count(); i++) {
                if (!_stricmp(Unknown_006FA120(unknown_players_a3fa7c[i]->Name), unknown_gpacket_a3f640.Name)) {
                    if (unknown_players_a3fa7c[i]->Address != unknown_address_a3f80c) {
                        found = 1;
                    } else {
                        resend = 1;
                    }
                    break;
                }
            }
            if (!_stricmp(Unknown_006FA120(unknown_players_a3fa7c[0]->Name), unknown_gpacket_a3f640.Name)) {
                found = 1;
            }
            if (found) {
                memset(&packet, 0, sizeof(packet));
                packet.Command = 8;
                packet.Reject.Why = 0;
                unknown_ipx_manager_a40978.Send_Global_Message(&packet, sizeof(packet), 1, &unknown_address_a3f80c, 0, 0);
                continue;
            }
            if (!resend) {
                if (unknown_gpacket_a3f640.Join.unknown_57 != 1 && Slots_Filled_005c9440()) {
                    memset(&packet, 0, sizeof(packet));
                    packet.Command = 8;
                    packet.Reject.Why = 1;
                    unknown_ipx_manager_a40978.Send_Global_Message(&packet, sizeof(packet), 1, &unknown_address_a3f80c, 0, 0);
                    continue;
                }
                if (unknown_gpacket_a3f640.Join.unknown_57 == 1 && No_Observer_Slot_005c9490()) {
                    memset(&packet, 0, sizeof(packet));
                    packet.Command = 8;
                    packet.Reject.Why = 1;
                    unknown_ipx_manager_a40978.Send_Global_Message(&packet, sizeof(packet), 1, &unknown_address_a3f80c, 0, 0);
                    continue;
                }
            }
            bool match = true;
            if (!resend) {
                if (unknown_gpacket_a3f640.Join.unknown_43 != unknown_a71e9c) {
                    match = false;
                }
                if (unknown_gpacket_a3f640.Join.unknown_47 != unknown_ini_8397a0_unique_id()) {
                    match = false;
                }
                if (unknown_gpacket_a3f640.Join.unknown_4b != unknown_a71ea0) {
                    match = false;
                }
                if (unknown_gpacket_a3f640.Join.unknown_4f != Unknown_00737af0()) {
                    match = false;
                }
            }
            int dups = 0;
            for (i = 0; i < unknown_players_a3fa7c.Count(); i++) {
                if (!strcmp(unknown_players_a3fa7c[i]->unknown_34, unknown_gpacket_a3f640.unknown_18)) {
                    dups++;
                }
            }
            if (!match) {
                memset(&packet, 0, sizeof(packet));
                packet.Command = 8;
                packet.Reject.Why = 6;
                unknown_ipx_manager_a40978.Send_Global_Message(&packet, sizeof(packet), 1, &unknown_address_a3f80c, 0, 0);
                continue;
            }
            if (!resend) {
                unsigned long version = version_object_00a40c88.Clip_Version_00713170(unknown_gpacket_a3f640.Join.unknown_3b, unknown_gpacket_a3f640.Join.unknown_3f);
                unknown_version_a3d8d4 = version;
                if (version == 0) {
                    memset(&packet, 0, sizeof(packet));
                    packet.Command = 8;
                    packet.Reject.Why = 2;
                    unknown_ipx_manager_a40978.Send_Global_Message(&packet, sizeof(packet), 1, &unknown_address_a3f80c, 0, 0);
                    continue;
                }
                if (version == 0xFFFFFFFF) {
                    memset(&packet, 0, sizeof(packet));
                    packet.Command = 8;
                    packet.Reject.Why = 3;
                    unknown_ipx_manager_a40978.Send_Global_Message(&packet, sizeof(packet), 1, &unknown_address_a3f80c, 0, 0);
                    continue;
                }
                unknown_session_a3d2ac = version_object_00a40c88.Version_Protocol_00713130(version);
                who = new NodeNameType;
                memset(who, 0, sizeof(*who));
                wcscpy(who->Name, Unknown_006FA180(unknown_gpacket_a3f640.Name));
                who->Address = unknown_address_a3f80c;
                if (unknown_session_a3d298.Mode) {
                    who->unknown_66e2d0(!unknown_session_a3d298.Mode->unknown_slot7(unknown_gpacket_a3f640.Join.unknown_2f) ? unknown_session_a3d298.Mode->unknown_slot10() : unknown_gpacket_a3f640.Join.unknown_2f);
                }
                strcpy(who->unknown_34, unknown_gpacket_a3f640.unknown_18);
                int color = unknown_gpacket_a3f640.Join.unknown_33;
                if (Unknown_Is_Color_Taken_005c95d0(color)) {
                    color = -2;
                }
                if (unknown_gpacket_a3f640.Join.unknown_57 == 1) {
                    color = -2;
                    who->unknown_66e2d0(-3);
                    who->Team = -1;
                } else {
                    who->Team = 0;
                    if (unknown_gpacket_a3f640.Join.unknown_2f == -3) {
                        if (unknown_session_a3d298.Mode) {
                            who->unknown_66e2d0(unknown_session_a3d298.Mode->unknown_slot10());
                        } else {
                            who->unknown_66e2d0(-2);
                        }
                    }
                }
                who->unknown_66e300(color);
                unknown_session_a3d298.Players.Add(who);
                int slot = Assign_Slot_005c9170(who);
                Unknown_Enable_Start_005c9700();
                memset(&packet, 0, sizeof(packet));
                packet.Command = 7;
                strcpy(packet.Name, unknown_name_a3d3a0);
                display_users = true;
                packet.PlayerInfo.unknown_2f = who->unknown_66e290();
                packet.PlayerInfo.unknown_33 = who->Get_Color_0066e2a0();
                packet.PlayerInfo.Observer = unknown_lobby_flag_7e6d90;
                packet.PlayerInfo.Slot = slot;
                unknown_ipx_manager_a40978.Send_Global_Message(&packet, sizeof(packet), 1, &unknown_address_a3f80c, 0, 0);
                Voc_Play(Rules->PlayerJoined, 1.0f, 0x2000, 0);
                if (unknown_session_a3d298.Mode) {
                    int rows = unknown_session_a3d298.Mode->unknown_slot32();
                    if (rows != -1) {
                        unknown_int_a3db1c = rows;
                    }
                }
                Unknown_005c3810(true, false);
                UnknownGlobalPacket slots;
                memset(&slots, 0, sizeof(slots));
                slots.Command = 0x16;
                strcpy(slots.Name, unknown_name_a3d3a0);
                Unknown_Slot_Names_005c8cf0(slots.Slots.Names);
                int count = unknown_players_a3fa7c.Count();
                for (i = 1; i < count; i++) {
                    unknown_ipx_manager_a40978.Send_Global_Message(&slots, sizeof(slots), 1, &unknown_players_a3fa7c[i]->Address, 0, 0);
                    Service_Game_IO_00481fb0();
                }
                Unknown_005c34f0();
            }
            }
        }
    }
    if (display_users) {
        Unknown_005bbdd0(false);
    }
    if (display_games) {
        Refresh_Game_List_005bc790();
    }
}
