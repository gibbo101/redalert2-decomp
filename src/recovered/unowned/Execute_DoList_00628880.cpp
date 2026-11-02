// int __fastcall Execute_DoList(int max_houses, int base_house, ConnManClass *net,
//     CDTimerClass<FrameTimerClass> *skip_crc, UnknownFrameTiming *their) (0x00628880; Red Alert's Execute_DoList)
#include "shared/queue.hpp"
#include "shared/session_state.hpp"
#include "shared/main_loop.hpp"
#include "shared/rules.hpp"
#include "shared/string_table.hpp"
#include "shared/ww_message_box.hpp"
#include "shared/crt_string.hpp"
#include "shared/crt_memory.hpp"
#include "shared/gadget.hpp"
// @ref ?Load_String@StringTable@@SIPBGPBDPAD0H@Z=006f9ec0
// @ref ?Process@WWMessageBox@@QAEHPBG000_N@Z=005b46b0
// @ref ??_C@_09NMOI@Frame?$DN?$CFd?6?$AA@=007ecfa0
// @ref ??_C@_0BA@BEEC@ID?3?5?5?5?5?5?5?5?5?5?$CFd?6?$AA@=007ecfbc
// @ref ??_C@_0BA@GMF@Frame?3?5?5?5?5?5?5?$CFd?6?$AA@=007ecfcc
// @ref ??_C@_0BA@DPIM@Type?3?5?5?5?5?5?5?5?$CFs?6?$AA@=007ecfdc
// @ref ??_C@_0BC@MGGJ@FrameSendRate?$DN?$CFd?6?$AA@=007ecf8c
// @ref ??_C@_0N@HMPP@MaxAhead?$DN?$CFd?6?$AA@=007ecfac
// @ref ??_C@_0BJ@EOLI@Removing?5a?5player?5?$CFs?3?$CFd?6?$AA@=007ecef8
// @ref ??_C@_0BL@LOHI@Packet?5received?5too?5late?$CB?6?$AA@=007ed018
// @ref ??_C@_0CL@ILFN@?9?9?9?9?9?9?9?9?9?5Event?5data?3?5?9?9?9?9?9?9?9?9?9?9@=007ecfec
// @ref ??_C@_0DA@LGEE@DoList?3?5Moving?5event?5from?5frame?5@=007ed06c
// @ref ??_C@_0DF@HGNM@DoList?3?5Moving?5EXIT?5event?5from?5f@=007ed034
// @ref ??_C@_0DH@MLHK@Exit?5Event?3?5ID?3?$CFd?5?$CI?$CFs?$CJ?0?5?5Event?5F@=007ecf14
// @ref ??_C@_0DP@IEKC@Sending?5game?5results?5because?5I?5q@=007ecf4c
// @ref ??_C@_08GPOP@TXT_STOP?$AA@=007eceec
// @ref ??_C@_0N@LAJB@TXT_COMPUTER?$AA@=007d1634
// @ref ??_C@_08CJPC@Computer?$AA@=007daa28
// @ref ??_C@_0CD@EFPN@Processing?5EXIT?5event?5on?5frame?5?$CF@=007d6aac
// @ref ??_C@_0BB@FEBL@D?3?2Ra2?2Queue?4CPP?$AA@=007ec598
// @ref ??_C@_0BA@FFPI@TXT_OUT_OF_SYNC?$AA@=007ecedc
// @ref ?Print_CRCs@@YIXPAVEventClass@@@Z=0062a360
// @ref ?Unknown_00629290@@YIXHH@Z=00629290
// @ref ?unknown_debug_print_events_a40d1c@@3_NA=00a40d1c
// @ref ?unknown_exit_frame1_a402e0@@3HA=00a402e0
// @ref ?unknown_exit_frame2_a402e4@@3HA=00a402e4
// @ref ?unknown_exit_house_a402e8@@3HA=00a402e8
// @ref ?unknown_max_ahead_frame1_a3d258@@3HA=00a3d258
// @ref ?unknown_max_ahead_frame2_a3d23c@@3HA=00a3d23c
extern int unknown_max_ahead_frame2_a3d23c;     // 0x00A3D23C (Red Alert's NewMaxAheadFrame2)
extern int unknown_max_ahead_frame1_a3d258;     // 0x00A3D258 (Red Alert's NewMaxAheadFrame1)
extern int unknown_exit_frame1_a402e0;          // 0x00A402E0
extern int unknown_exit_frame2_a402e4;          // 0x00A402E4
extern int unknown_exit_house_a402e8;           // 0x00A402E8 (-1: none)
extern bool unknown_debug_print_events_a40d1c;  // 0x00A40D1C
// Executes the events of a run of identical megamission events of the queue 0x00A35F30 (0x00629290).
void __fastcall Unknown_00629290(int start, int count);

int __fastcall Execute_DoList(int max_houses, int base_house, ConnManClass *net,
    CDTimerClass<FrameTimerClass> *skip_crc, UnknownFrameTiming *their)
{
    int count = DoList.Count;
    int house_count = Houses.Count();
    int i, j, k;
    int index;
    int check_crc;
    HouseClass *hptr;

    for (j = 0; j < count; j++) {
        if (DoList[j].Type != 0x1C && DoList[j].Frame > unknown_max_ahead_frame1_a3d258 &&
                DoList[j].Frame < unknown_max_ahead_frame2_a3d23c) {
            Debug_Printf("DoList: Moving event from frame %d to frame %d\n", DoList[j].Frame, unknown_max_ahead_frame2_a3d23c);
            DoList[j].Frame = unknown_max_ahead_frame2_a3d23c;
        }
    }

    if (unknown_exit_frame1_a402e0 && unknown_exit_frame2_a402e4 && unknown_exit_house_a402e8 != -1) {
        for (j = 0; j < count; j++) {
            if (DoList[j].Type == 0x13 && DoList[j].House == unknown_exit_house_a402e8 &&
                    DoList[j].Frame > unknown_exit_frame1_a402e0 && DoList[j].Frame < unknown_exit_frame2_a402e4) {
                Debug_Printf("DoList: Moving EXIT event from frame %d to frame %d\n", DoList[j].Frame, unknown_exit_frame2_a402e4);
                DoList[j].Frame = unknown_exit_frame2_a402e4;
            }
        }
        if (::Frame > unknown_exit_frame2_a402e4) {
            unknown_exit_frame1_a402e0 = 0;
            unknown_exit_frame2_a402e4 = 0;
            unknown_exit_house_a402e8 = -1;
        }
    }

    for (i = 0; i < house_count; i++) {
        hptr = Houses[i];
        if (!hptr) {
            continue;
        }
        if (!hptr->unknown_134 && !hptr->unknown_135) {
            continue;
        }

        for (j = 0; j < count; j++) {
            if (DoList[j].House == hptr->ArrayIndex && ::Frame >= DoList[j].Frame && !DoList[j].IsExecuted) {
                if (::Frame > DoList[j].Frame && DoList[j].Type != 0x1C &&
                        unknown_game_mode_a3d298 != 0 && unknown_game_mode_a3d298 != 5) {
                    EventClass *event = &DoList[j];
                    Debug_Printf("Packet received too late!\n");
                    Debug_Printf("--------- Event data: -------------------\n");
                    Debug_Printf("Type:       %s\n", EventNames[event->Type]);
                    Debug_Printf("Frame:      %d\n", event->Frame);
                    Debug_Printf("ID:         %d\n", event->House);
                    Debug_Printf("MaxAhead=%d\n", unknown_max_ahead_a3d560);
                    Debug_Printf("Frame=%d\n", ::Frame);
                    Debug_Printf("FrameSendRate=%d\n", unknown_frame_send_rate_a3d564);
                    net->Num_Connections();
                    continue;
                }

                if (DoList[j].Type == 0x13 || DoList[j].Type == 0x0C || DoList[j].Type == 0x22) {
                    if (DoList[j].Type == 0x13) {
                        HouseClass *quithptr = 0;
                        for (int player = 0; player < house_count; player++) {
                            quithptr = Houses[player];
                            if (!quithptr) {
                                continue;
                            }
                            if (quithptr->ArrayIndex == DoList[j].House) {
                                quithptr->unknown_18f = true;
                                break;
                            }
                        }
                        if (Unknown_005C3150(quithptr) == 1 && unknown_game_mode_a3d298 == 4 && !unknown_flag_a417c8) {
                            unknown_flag_a3d8d1 = true;
                            Unknown_0069A160();
                            Unknown_00698D00(false);
                        }
                        if (unknown_game_mode_a3d298 == 4 && !unknown_flag_a417c8 && unknown_player_a35db4 != 0 &&
                                unknown_player_a35db4 == quithptr) {
                            Debug_Printf("Sending game results because I quit, but didn't see completion");
                            Unknown_00698D00(false);
                        }
                    }
                    if (unknown_debug_print_events_a40d1c) {
                        if (DoList[j].Type == 0x13) {
                            Debug_Printf("Exit Event: ID:%d (%s),  Event Frame:%d,  My Frame:%d\n",
                                DoList[j].House, (char const *)Houses[DoList[j].House]->IniName, DoList[j].Frame, ::Frame);
                        }
                    }
                    if (DoList[j].House == unknown_player_a35db4->ArrayIndex) {
                        int stamp = DoList.Timings[(DoList.Head + j) & 0x3FFF];
                        unknown_time_7ec498 = timeGetTime() - stamp;
                        DoList[j].Execute();
                    } else if (DoList[j].Type == 0x13) {
                        Debug_Printf("Processing EXIT event on frame %d\n", ::Frame);
                        if (unknown_game_mode_a3d298 == 1 || unknown_game_mode_a3d298 == 2) {
                            Destroy_Null_Connection(i, 0);
                        } else if ((unknown_game_mode_a3d298 == 3 || unknown_game_mode_a3d298 == 4) && net) {
                            index = net->Connection_Index(i);
                            if (index != -1) {
                                for (k = index; k < net->Num_Connections() - 1; k++) {
                                    their[k] = their[k + 1];
                                }
                                Destroy_Connection_005bb5d0(i, 0);
                            }
                        }
                        if ((unknown_flags_a3f600 & 2) && DoList[j].Type == 0x13) {
                            hptr->unknown_134 = false;
                            hptr->unknown_194 = Rules->MaxIQ;
                            HouseClass::unknown_func_4ec5e0();
                            hptr->IniName = FixedString<21>("Computer");
                            wcsncpy(hptr->UIName, StringTable::Load_String("TXT_COMPUTER", 0, "D:\\Ra2\\Queue.CPP", 0x1623), 0x15);
                            hptr->UIName[20] = 0;
                            Debug_Printf("Removing a player %s:%d\n", "D:\\Ra2\\Queue.CPP", 0x1625);
                            unknown_session_a3d55c--;
                        }
                    }
                } else if (DoList[j].Type == 0x1C) {
                    if (!skip_crc || *skip_crc == 0) {
                        check_crc = 1;
                    } else {
                        check_crc = 0;
                    }
                    if (check_crc && DoList[j].Frame == ::Frame && DoList[j].ByteAt(0x0D) < 256) {
                        index = (DoList[j].Frame - DoList[j].ByteAt(0x0D)) & 0xFF;
                        if (CRC[index] != (unsigned long)DoList[j].LongAt(0x07)) {
                            if (unknown_flag_ab62e8) {
                                // The CRC log of every sync slot (k is reduced to a slot
                                // number before each call; the loop count is separate).
                                k = 0;
                                for (int n = 256; n; n--) {
                                    k &= 0xFF;
                                    Unknown_0062DBA0(k, &DoList[j]);
                                    k++;
                                }
                            } else {
                                Print_CRCs(&DoList[j]);
                            }
                            unknown_a3fabc++;
                            if (WWMessageBox(L" ").Process(StringTable::Load_String("TXT_OUT_OF_SYNC", 0, "D:\\Ra2\\Queue.CPP", 0x1655),
                                    StringTable::Load_String("TXT_STOP", 0, "D:\\Ra2\\Queue.CPP", 0x1656), 0, 0, 0) == 0) {
                                unknown_a3fabc--;
                                return 0;
                            }
                            unknown_a3fabc--;
                            return 0;
                        }
                    }
                } else {
                    int stamp = DoList.Timings[(DoList.Head + j) & 0x3FFF];
                    unknown_time_7ec498 = timeGetTime() - stamp;
                    if (DoList[j].Type == 4) {
                        unknown_event_queue_a35f30.Add(DoList[j]);
                    } else {
                        DoList[j].Execute();
                    }
                }
                DoList[j].IsExecuted = 1;
            }
        }

        int mission = -1;
        TargetClass target;
        TargetClass destination;
        target.Kind = 0;
        destination.Kind = 0;
        int start = 0;
        for (k = 0; k < unknown_event_queue_a35f30.Count; k++) {
            bool differ = false;
            if (mission != -1) {
                EventClass &event = unknown_event_queue_a35f30[k];
                if ((char)event.ByteAt(0x0C) != (char)mission) {
                    differ = true;
                }
                if (event.TargetAt(0x0E).Kind != target.Kind || event.TargetAt(0x0E).ID != target.ID ||
                        event.TargetAt(0x13).Kind != destination.Kind || event.TargetAt(0x13).ID != destination.ID) {
                    differ = true;
                }
            }
            mission = (char)unknown_event_queue_a35f30[k].ByteAt(0x0C);
            target = unknown_event_queue_a35f30[k].TargetAt(0x0E);
            destination = unknown_event_queue_a35f30[k].TargetAt(0x13);
            if (differ) {
                if (k - start > 1) {
                    Unknown_00629290(start, k - start);
                }
                start = k;
            } else if (k == unknown_event_queue_a35f30.Count - 1 && k - start + 1 > 1) {
                Unknown_00629290(start, k - start + 1);
            }
        }
        while (unknown_event_queue_a35f30.Count) {
            unknown_event_queue_a35f30.First().Execute();
            unknown_event_queue_a35f30.Next();
        }
    }
    return 1;
}
