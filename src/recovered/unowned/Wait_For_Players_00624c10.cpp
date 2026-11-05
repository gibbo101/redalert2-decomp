// int Wait_For_Players (0x00624C10; Red Alert's Wait_For_Players): waits for the other players, with the
// reconnect dialog, the kick votes and the frame-sync stall bars.
// The exit path reads Session through its raw names (game mode, the debug flags at +0x62C and +0x62D): VC6's
// reload order at the loop head and the pixel channel order depend on how many static locations the body names.
#include "shared/queue.hpp"
#include "shared/display.hpp"
#include "shared/map_view.hpp"
#include "shared/tactical.hpp"
#include "shared/serial_progress.hpp"
#include "shared/cd_timer.hpp"
#include "shared/session_state.hpp"
#include "shared/string_table.hpp"
#include "shared/unknown_player_entry.hpp"
#include "shared/wol_sink.hpp"
#include "shared/lobby.hpp"
#include "shared/dsurface.hpp"
#include "shared/hicolor.hpp"
#include "shared/ipx_conn.hpp"
#include "shared/crt_string.hpp"
#include "shared/gscreen.hpp"
#include "shared/id_source.hpp"

extern int unknown_reconnect_result_ab5ed0;     // 0x00AB5ED0
extern bool unknown_flag_ab5ed8;                // 0x00AB5ED8
extern bool unknown_flag_ab62fc;                // 0x00AB62FC
extern HWND unknown_reconnect_dialog_a780d4;    // 0x00A780D4
extern int unknown_seconds_ab6300;              // 0x00AB6300
extern long unknown_elapsed_aabe90;             // 0x00AABE90
extern unsigned short const unknown_blank_839d4c[]; // 0x00839D4C
extern unsigned short const unknown_crlf_7d64f4[];  // 0x007D64F4
extern void *unknown_instance_b26180;           // 0x00B26180
extern HWND unknown_parent_b263d8;              // 0x00B263D8
extern bool unknown_flag_a3d8c5;                // 0x00A3D8C5
extern int unknown_stall_counts_a3d5d8[][26];   // 0x00A3D5D8 (per connection: frame stalls, command stalls)
int __fastcall Wait_For_Players(int first_time, ConnManClass *net, int resend_delta, int dialog_time, int timeout,
    char *multi_packet_buf, int my_sent, UnknownFrameTiming *their);

enum {
    MAX_EVENTS = 64,
};

#define QTEXT(label, line) StringTable::Load_String(label, 0, "D:\\Ra2\\Queue.CPP", line)

static inline void Close_Reconnect_Dialog()
{
    void *dialog = Unknown_00735940(0xEA);
    if (dialog) {
        if (unknown_flag_ab5ed8) {
            WWMouse->Capture_Mouse();
        }
        Unknown_007357E0(dialog, 0);
        unknown_flag_a40380 = unknown_flag_ab62fc;
        Map.Flag_To_Redraw(2);
        if (unknown_flag_a40380) {
            Map.Render();
        }
    }
}

static inline int Process_Reconnect_Dialog(ConnManClass *net, CDTimerClass<SystemTimerClass> *timeout_timer, UnknownFrameTiming *their,
    int num_conn, int reconn, int fresh, UnknownElapsedTimer *timer)
{
    int new_time;
    int oldest_index;
    int i;
    wchar_t buf[512];

    unknown_elapsed_aabe90 = timer->Timer - timer->Started;
    for (i = 0; i < num_conn; i++) {
        unknown_timing_aabcf0[i] = their[i];
    }
    if (fresh) {
        unknown_flag_ab62fc = unknown_flag_a40380;
        unknown_flag_a40380 = false;
        unknown_reconnect_result_ab5ed0 = -1;
        unknown_reconnect_dialog_a780d4 = (HWND)unknown_create_dialog_735700(unknown_instance_b26180, 0xEA, unknown_parent_b263d8,
            (UnknownDialogProc)Unknown_00627350, 0);
        if (unknown_reconnect_dialog_a780d4) {
            SetWindowLongA(unknown_reconnect_dialog_a780d4, 8, (long)&unknown_reconnect_result_ab5ed0);
            unknown_show_dialog_5ff7e0(unknown_reconnect_dialog_a780d4, 0xEA);
            ShowWindow(unknown_reconnect_dialog_a780d4, 1);
            SendMessageA(unknown_reconnect_dialog_a780d4, 0x4A9, 0, 1);
            unknown_flag_ab5ed8 = WWMouse->Is_Captured();
            if (unknown_flag_ab5ed8) {
                WWMouse->Release_Mouse();
            }
            WWMouse->Show_Mouse();
        }
    }
    if (unknown_reconnect_result_ab5ed0 == 2) {
        return 1;
    }
    new_time = timeout_timer->Value() / 60;
    if (fresh || new_time != unknown_seconds_ab6300) {
        unknown_seconds_ab6300 = new_time;
        HWND item = GetDlgItem(unknown_reconnect_dialog_a780d4, 0x650);
        if (item) {
            swprintf(buf, QTEXT("TXT_TIME_ALLOWED", 3856), unknown_seconds_ab6300);
            SendMessageA(item, 0x4B2, 0, (LPARAM)buf);
        }
        if (!(unknown_seconds_ab6300 & 1)) {
            PostMessageA(unknown_reconnect_dialog_a780d4, 0xF, 0, 0);
        }
        if (fresh) {
            while (unknown_session_a3d298.GlobalPackets_8a0.Count()) {
                delete unknown_session_a3d298.GlobalPackets_8a0[0];
                unknown_session_a3d298.GlobalPackets_8a0.Delete(0);
            }
            memset(unknown_session_a3d298.KickVotes, 0, sizeof(unknown_session_a3d298.KickVotes));
            memset(unknown_session_a3d298.KickVoters, 0xFF, sizeof(unknown_session_a3d298.KickVoters));
            HWND list = GetDlgItem(unknown_reconnect_dialog_a780d4, 0x651);
            if (list) {
                if (reconn) {
                    int oldest = 0x7FFFFFFF;
                    oldest_index = 0;
                    for (i = 0; i < num_conn; i++) {
                        if (their[i].Frame < oldest) {
                            oldest = their[i].Frame;
                            oldest_index = i;
                        }
                    }
                    if (unknown_session_a3d298.Type == 3 || unknown_session_a3d298.Type == 4) {
                        swprintf(buf, QTEXT("TXT_RECONNECTING_TO", 3911),
                            unknown_ipx_manager_a40978.Connection_Name(unknown_ipx_manager_a40978.Connection_ID(oldest_index)));
                    } else {
                        swprintf(buf, QTEXT("TXT_RECONNECTING_TO", 3917), unknown_session_a3d298.Players[1]->Name);
                    }
                    Unknown_005C2DA0(-1, (unsigned short const *)buf, list);
                    Unknown_005C2DA0(-1, unknown_blank_839d4c, list);
                    if (unknown_session_a3d298.Type == 4) {
                        wcscpy(buf, QTEXT("TXT_RECONNECT_HELP3", 3931));
                        wcscat(buf, (wchar_t const *)unknown_crlf_7d64f4);
                        wcscat(buf, QTEXT("TXT_RECONNECT_HELP3B", 3933));
                        wcscat(buf, (wchar_t const *)unknown_crlf_7d64f4);
                        wcscat(buf, QTEXT("TXT_RECONNECT_HELP3C", 3935));
                        Unknown_005C2DA0(-1, (unsigned short const *)buf, list);
                        Unknown_005C2DA0(-1, unknown_blank_839d4c, list);
                    }
                    if (unknown_session_a3d298.Type == 4 || unknown_session_a3d298.Type == 3) {
                        wcscpy(buf, QTEXT("TXT_RECONNECT_HELP2", 3942));
                        wcscat(buf, (wchar_t const *)unknown_crlf_7d64f4);
                        if (unknown_session_a3d298.Type == 4) {
                            wcscat(buf, QTEXT("TXT_RECONNECT_HELP2B", 3946));
                        } else if (unknown_session_a3d298.Type == 3) {
                            wcscat(buf, QTEXT("TXT_RECONNECT_HELP4", 3948));
                        }
                        Unknown_005C2DA0(-1, (unsigned short const *)buf, list);
                        Unknown_005C2DA0(-1, unknown_blank_839d4c, list);
                    }
                    Unknown_005C2DA0(-1, unknown_blank_839d4c, list);
                    Unknown_005C2DA0(-1, (unsigned short const *)QTEXT("TXT_RECONNECT_HELP5", 3958), list);
                    Unknown_005C2DA0(-1, (unsigned short const *)QTEXT("TXT_RECONNECT_HELP1", 3963), list);
                    Unknown_005C2DA0(-1, unknown_blank_839d4c, list);
                } else {
                    swprintf(buf, QTEXT("TXT_WAITING_FOR_CONNECTIONS", 3966));
                    Unknown_005C2DA0(-1, (unsigned short const *)buf, list);
                }
            }
        }
    }
    if (unknown_session_a3d298.GlobalPackets_8a0.Count() > 0) {
        Unknown_00627210(unknown_session_a3d298.GlobalPackets_8a0[0]->PlayerInfo.unknown_33, unknown_session_a3d298.GlobalPackets_8a0[0]->PlayerInfo.unknown_2f);
        delete unknown_session_a3d298.GlobalPackets_8a0[0];
        unknown_session_a3d298.GlobalPackets_8a0.Delete(0);
    }
    for (i = 0; i < unknown_session_a3d298.Players.Count(); i++) {
        int votes = unknown_session_a3d298.KickVotes[unknown_session_a3d298.Players[i]->ID];
        if (votes >= unknown_session_a3d298.Players.Count() - 1) {
            Debug_Printf("Kicking player %s from the game due to %d votes\n", unknown_session_a3d298.Players[i], votes);
            if (i == 0) {
                Debug_Printf("Outvoted player is me!\n");
                for (i = 1; i < unknown_session_a3d298.Players.Count(); i++) {
                    Kick_Player_Now(net, net->Connection_Index(unknown_session_a3d298.Players[i]->ID), their, 0);
                }
                break;
            }
            Kick_Player_Now(net, net->Connection_Index(unknown_session_a3d298.Players[i]->ID), their, 1);
        }
    }
    return 0;
}

static inline int Can_Advance(ConnManClass *net, int max_ahead, UnknownFrameTiming *their, int *frame_stall, int *count_stall)
{
    int their_oldest_frame;
    int count_ok;
    int i;

    *frame_stall = -1;
    if (unknown_session_a3d55c == 1) {
        return 1;
    }
    their_oldest_frame = Frame + 1000;
    for (i = 0; i < net->Num_Connections(); i++) {
        if (their[i].Frame < their_oldest_frame) {
            their_oldest_frame = their[i].Frame;
            *frame_stall = i;
        }
    }
    count_ok = 1;
    for (i = 0; i < net->Num_Connections(); i++) {
        if ((unsigned)their[i].unknown_08 < (unsigned)their[i].unknown_04) {
            count_ok = 0;
            break;
        }
    }
    if (count_ok) {
        if (Frame < their_oldest_frame + max_ahead) {
            return 1;
        }
        i = -1;
    }
    if (Frame < their_oldest_frame + max_ahead) {
        *frame_stall = -1;
    }
    *count_stall = i;
    return 0;
}

int __fastcall Wait_For_Players(int first_time, ConnManClass *net, int resend_delta, int dialog_time, int timeout,
    char *multi_packet_buf, int my_sent, UnknownFrameTiming *their)
{
    int packetlen;
    int id;
    int num_ready;
    int loop_count;
    int messages_this_loop;
    int input;
    int x, y;
    int i;
    RetcodeType rc;
    bool stall_drawn = false;
    Surface *surface = unknown_surface_839950;
    CDTimerClass<SystemTimerClass> retry_timer;
    CDTimerClass<SystemTimerClass> dialog_timer;
    CDTimerClass<SystemTimerClass> timeout_timer;
    UnknownElapsedTimer timer;
    CDTimerClass<SystemTimerClass> progress_timer;
    int reconnect_dlg = 0;
    CDTimerClass<SystemTimerClass> unused_a = dialog_time * 2;
    CDTimerClass<SystemTimerClass> unused_b = dialog_time / 2;

    num_ready = 0;
    retry_timer = resend_delta;
    dialog_timer = dialog_time;
    timeout_timer = timeout;
    timer = UnknownElapsedTimer();
    progress_timer = 180;
    CDTimerClass<SystemTimerClass> keepalive_timer = 300;
    loop_count = 0;
    unsigned long now = timeGetTime();
    for (i = 0; i < net->Num_Connections(); i++) {
        their[i].unknown_14 = now;
    }

    while (true) {
        WWKeyboard->Check();
        if (retry_timer.Value() == 0) {
            retry_timer = resend_delta;
            Send_FrameSync(net, my_sent);
            if (unknown_session_a3d298.Type == 4 && unknown_flag_a3fba8) {
                unknown_ipx_manager_a40978.unknown_5277f0();
                Debug_Printf("Time to send IM_STILL_HERE packets\n");
                UnknownGlobalPacket packet;
                packet.Command = 0x27;
                strncpy(packet.Name, Unknown_006FA120((unsigned short const *)unknown_session_a3d298.Players[0]->Name), 20);
                *(int *)&packet.unknown_2f[0] = unknown_player_a35db4->ArrayIndex;
                IPXAddressClass address = unknown_forward_address_a3fbac;
                address.unknown_523960(unknown_forward_port_a3fbc4);
                *(IPXAddressClass *)&packet.unknown_2f[4] = address;
                for (i = 1; i < unknown_session_a3d298.Players.Count(); i++) {
                    int id2 = unknown_session_a3d298.Players[i]->ID;
                    if (id2 != unknown_player_a35db4->ArrayIndex) {
                        unknown_ipx_manager_a40978.Send_Global_Message(&packet, 0x5B, 0,
                            &unknown_session_a3d298.Players[i]->Address, unknown_node_ids_a402ba[i], 0);
                    }
                }
                unknown_481fb0();
            }
        }
        if (keepalive_timer.Value() == 0 && !first_time) {
            keepalive_timer = 300;
        } else if (first_time) {
            if (progress_timer.Value() == 0) {
                if (unknown_session_a3d298.Type == 1 || unknown_session_a3d298.Type == 2 || unknown_flag_a3fba8) {
                    Debug_Printf("Resending progress message\n");
                    if (unknown_session_a3d298.Type == 4) {
                        unknown_ipx_manager_a40978.unknown_5277f0();
                    }
                    unknown_session_a3d298.Loading_Progress_00672160(unknown_id_source_a3d290->unknown_223b ? 200 : 100);
                    progress_timer = 180;
                }
            }
        }
        net->Service();

        if (dialog_timer.Value() == 0) {
            if (unknown_session_a3d298.Type == 4) {
                unknown_ipx_manager_a40978.unknown_5277f0();
            }
            int fresh = reconnect_dlg == 0;
            int reconn = first_time == 0;
            if (Process_Reconnect_Dialog(net, &timeout_timer, their, net->Num_Connections(), reconn, fresh, &timer)) {
                Unknown_007357E0(unknown_reconnect_dialog_a780d4, 0);
                if (unknown_flag_ab5ed8) {
                    WWMouse->Capture_Mouse();
                }
                unknown_flag_a40380 = unknown_flag_ab62fc;
                Map.Flag_To_Redraw(2);
                if (reconnect_dlg) {
                    Close_Reconnect_Dialog();
                }
                if (unknown_session_a3d298.Type == 4) {
                    unknown_ipx_manager_a40978.unknown_527800();
                }
                if (!unknown_ab62e0) {
                    Send_Port_Unreachable();
                    return RC_CANCEL;
                }
                Send_Port_Unreachable();
                return RC_CANCEL + 1;
            }
            reconnect_dlg = 1;
        }

        if (timeout_timer.Value() == 0) {
            if (first_time) {
                if (reconnect_dlg) {
                    Close_Reconnect_Dialog();
                }
                Send_Port_Unreachable();
                if (unknown_session_a3d298.Type == 4) {
                    unknown_ipx_manager_a40978.unknown_527800();
                }
                return RC_NOT_RESPONDING;
            }
            if (Handle_Timeout(net, their)) {
                Map.Flag_To_Redraw(2);
                Map.Render();
                retry_timer = resend_delta;
                dialog_timer = dialog_time;
                timeout_timer = timeout;
            } else {
                if (reconnect_dlg) {
                    Close_Reconnect_Dialog();
                }
                if (unknown_session_a3d298.Type == 4) {
                    unknown_ipx_manager_a40978.unknown_527800();
                }
                return RC_NOT_RESPONDING;
            }
        }

        messages_this_loop = 0;
        while (messages_this_loop++ < MAX_EVENTS && net->Get_Private_Message(multi_packet_buf, &packetlen, &id)) {
            WWKeyboard->Check();
            if (unknown_session_a3d298.Type == 1 || unknown_session_a3d298.Type == 2) {
                rc = Process_Serial_Packet(multi_packet_buf, first_time);
                if (rc == RC_SERIAL_PROCESSED) {
                    net->Service();
                    retry_timer = resend_delta;
                    dialog_timer = dialog_time;
                    timeout_timer = timeout;
                    continue;
                } else if (rc == RC_PLAYER_LEFT) {
                    if (first_time) {
                        num_ready++;
                    }
                    break;
                } else if (rc == RC_HUNG_UP) {
                    if (Handle_Timeout(net, their)) {
                        Map.Flag_To_Redraw(2);
                        Map.Render();
                        retry_timer = resend_delta;
                        dialog_timer = dialog_time;
                        timeout_timer = timeout;
                    } else {
                        if (reconnect_dlg) {
                            Close_Reconnect_Dialog();
                        }
                        if (unknown_session_a3d298.Type == 4) {
                            unknown_ipx_manager_a40978.unknown_527800();
                        }
                        Send_Port_Unreachable();
                        return RC_NOT_RESPONDING;
                    }
                } else if (rc != RC_NORMAL) {
                    break;
                }
            }
            rc = Process_Receive_Packet(net, multi_packet_buf, id, packetlen, their, &timer);
            if (rc == RC_PLAYER_READY) {
                num_ready++;
            } else if (rc == RC_SCENARIO_MISMATCH) {
                if (reconnect_dlg) {
                    Close_Reconnect_Dialog();
                }
                if (unknown_session_a3d298.Type == 4) {
                    unknown_ipx_manager_a40978.unknown_527800();
                }
                return RC_SCENARIO_MISMATCH;
            } else if (rc == RC_DOLIST_FULL) {
                if (reconnect_dlg) {
                    Close_Reconnect_Dialog();
                }
                if (unknown_session_a3d298.Type == 4) {
                    unknown_ipx_manager_a40978.unknown_527800();
                }
                Send_Port_Unreachable();
                return RC_DOLIST_FULL;
            }
            net->Service();
        }

        if (reconnect_dlg) {
            net->Num_Connections();
        }
        if (first_time) {
            if (num_ready >= net->Num_Connections()) {
                break;
            }
        } else {
            int frame_stall;
            int count_stall;
            if (Can_Advance(net, unknown_max_ahead_a3d560, their, &frame_stall, &count_stall)) {
                break;
            }
            if (unknown_flag_a3d8c4 && unknown_flag_a3d8c5 && loop_count > 0 && (!stall_drawn || frame_stall != -1 || count_stall != -1)) {
                Unknown_005419E0(true);
            } else if (stall_drawn) {
                goto service;
            }
            if (frame_stall != -1) {
                if (unknown_flag_a3d8c4 && unknown_flag_a3d8c5) {
                    surface->Fill_Rect(Rect((frame_stall * 5 + 5) * 20, 400, 35, 3), Build_Hicolor_Pixel(255, 255, 40));
                }
                unknown_stall_counts_a3d5d8[frame_stall][0]++;
            }
            if (count_stall != -1) {
                if (unknown_flag_a3d8c4 && unknown_flag_a3d8c5) {
                    surface->Fill_Rect(Rect(count_stall * 100 + 140, 400, 40, 3), Build_Hicolor_Pixel(255, 40, 40));
                }
                unknown_stall_counts_a3d5d8[frame_stall][1]++;
            }
            stall_drawn = true;
        }
service:
        unknown_481fb0();
        if (!first_time && !unknown_int_a40d48 && !reconnect_dlg) {
            Map.Get_Input(input, x, y);
            Keyboard_Process(input);
            unknown_tactical_83996c->AI();
            Map.Render();
        }
        loop_count++;
    }
    if (reconnect_dlg) {
        Close_Reconnect_Dialog();
        if (net->Num_Connections() > 0) {
            unknown_b2a630 = 0;
            unknown_b2aaf8 = 0;
        }
    }
    if (stall_drawn && unknown_session_a3d298.unknown_2ec[0x340] && unknown_session_a3d298.unknown_2ec[0x341]) {
        Rect rect(100, 400, 540, 4);
        surface->Fill_Rect(rect, 0);
    }
    if (unknown_game_mode_a3d298 == 4) {
        unknown_ipx_manager_a40978.unknown_527800();
    }
    return RC_NORMAL;
}
// @ref ??_C@_0BB@CCIN@TXT_TIME_ALLOWED?$AA@=007ec808
// @ref ??_C@_0BE@CFPE@TXT_RECONNECT_HELP5?$AA@=007ec75c
// @ref ??_C@_0BE@FKHA@TXT_RECONNECTING_TO?$AA@=007ec7f4
// @ref ??_C@_0BE@HABB@TXT_RECONNECT_HELP2?$AA@=007ec79c
// @ref ??_C@_0BE@IPGD@TXT_RECONNECT_HELP4?$AA@=007ec770
// @ref ??_C@_0BE@IPKI@TXT_RECONNECT_HELP1?$AA@=007ec748
// @ref ??_C@_0BE@NKIG@TXT_RECONNECT_HELP3?$AA@=007ec7e0
// @ref ??_C@_0BF@CIJO@TXT_RECONNECT_HELP2B?$AA@=007ec784
// @ref ??_C@_0BF@DODE@TXT_RECONNECT_HELP3B?$AA@=007ec7c8
// @ref ??_C@_0BF@JEKD@TXT_RECONNECT_HELP3C?$AA@=007ec7b0
// @ref ??_C@_0BI@DCKO@Outvoted?5player?5is?5me?$CB?6?$AA@=007ec6e0
// @ref ??_C@_0BM@DLII@Resending?5progress?5message?6?$AA@=007ec81c
// @ref ??_C@_0BM@KBEO@TXT_WAITING_FOR_CONNECTIONS?$AA@=007ec72c
// @ref ??_C@_0CE@IOJA@Time?5to?5send?5IM_STILL_HERE?5packe@=007ec838
// @ref ??_C@_0DB@MLLE@Kicking?5player?5?$CFs?5from?5the?5game?5@=007ec6f8
// @ref ?Delete@?$DynamicVectorClass@PAUUnknownGlobalPacket@@@@QAE_NH@Z=0062ea00
// @ref __imp__PostMessageA@16=0079a470
// @ref ?unknown_blank_839d4c@@3QBGB=00839d4c
// @ref ?unknown_crlf_7d64f4@@3QBGB=007d64f4
// @ref ?unknown_elapsed_aabe90@@3JA=00aabe90
// @ref ?unknown_flag_a3d8c5@@3_NA=00a3d8c5
// @ref ?unknown_flag_ab5ed8@@3_NA=00ab5ed8
// @ref ?unknown_flag_ab62fc@@3_NA=00ab62fc
// @ref ?unknown_instance_b26180@@3PAXA=00b26180
// @ref ?unknown_parent_b263d8@@3PAUHWND__@@A=00b263d8
// @ref ?unknown_reconnect_dialog_a780d4@@3PAUHWND__@@A=00a780d4
// @ref ?unknown_reconnect_result_ab5ed0@@3HA=00ab5ed0
// @ref ?unknown_seconds_ab6300@@3HA=00ab6300
// @ref ?unknown_stall_counts_a3d5d8@@3PAY0BK@HA=00a3d5d8
