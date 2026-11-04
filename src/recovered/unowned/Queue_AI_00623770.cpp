#include "shared/queue.hpp"
#include "shared/main_loop.hpp"
#include "shared/house_type.hpp"
// Queue.CPP normal/playback dispatch, target 00623770. Owner authored draft, fresh canonical context.
// @ref ?Frame@@3HA=00a40d2c
// @ref ?Read@CCFileClass@@UAEJPAXJ@Z=00469060
// @ref ?unknown_record_file_a3f59c@@3VCCFileClass@@A=00a3f59c
// @ref ?Queue_AI_Multiplayer@@YIXXZ=00623b00
// @ref ?Compute_Game_CRC@@YIXXZ=00629fa0
// @ref ?Print_CRCs@@YIXPAVEventClass@@@Z=0062a360
// @ref ?Unknown_0062DBA0@@YIXHH@Z=0062dba0
// @ref ?Unknown_00691320@@YAXXZ=00691320
// @ref ?unknown_trap_print_crc_a40314@@3HA=00a40314
// @ref ?unknown_flag_ab62e8@@3_NA=00ab62e8
// @ref ?unknown_max_players_a3d558@@3HA=00a3d558
// @ref ?unknown_mouse_x_a76b70@@3HA=00a76b70
// @ref ?unknown_mouse_y_a76c78@@3HA=00a76c78
// @ref ?Clean_DoList@@YIXPAVConnManClass@@@Z=00629e80
// @ref ?Queue_Record@@YIXXZ=00629ed0
// @ref ?DoList@@3V?$QueueClass@VEventClass@@$0EAAA@@@A=00866270
// @ref ?Unknown_0069A160@@YAXXZ=0069a160
// @ref ?Unknown_00698D00@@YIX_N@Z=00698d00
// @ref ?Unknown_0059DA00@@YAXXZ=0059da00
// @ref ?Mono_Window_Show@@YAXXZ=0059d9c0
// @ref ?Mono_Page_0059da50@@YIPAVMonoClass@@H@Z=0059da50
// @ref ?unknown_a3d8c8@@3HA=00a3d8c8
// @ref ?unknown_a3d8cc@@3HA=00a3d8cc
// @ref ?unknown_ab62dc@@3HA=00ab62dc
// @ref ?unknown_flag_a3d8d1@@3_NA=00a3d8d1
// @ref ?unknown_flag_a3d8d2@@3_NA=00a3d8d2
// @ref ?unknown_flag_abd500@@3_NA=00abd500
// @ref ?Process@WWMessageBox@@QAEHPBG000_N@Z=005b46b0
// @ref ??_C@_13ECNF@?$AA?5?$AA?$AA@=007d64f4
// @ref ??_C@_0BB@FEBL@D?3?2Ra2?2Queue?4CPP?$AA@=007ec598
// @ref ??_C@_0P@CAII@TXT_QUEUE_FULL?$AA@=007ec56c
// @ref ??_C@_06DN@TXT_OK?$AA@=007db8f4
// @ref ?unknown_frame_send_rate_a3d564@@3IA=00a3d564
// @ref ?GameCRC@@3KA=00a76c74
// @ref ?CRC@@3PAKA=00ab5edc
// @ref ?unknown_crc_a40770@@3KA=00a40770
// @ref ?unknown_frame_syncs_ab62e4@@3HA=00ab62e4
// @ref ?unknown_a3fb84@@3PAHA=00a3fb84
// @ref ?unknown_precalc_max_ahead_a3d57c@@3IA=00a3d57c
// @ref ?unknown_sync_counts_a76b74@@3PAY07HA=00a76b74
// @ref ?unknown_queue_timings_7ec438@@3QBUUnknownQueueTimings@@B=007ec438
// @ref ??_C@_0BE@HIML@Response?5time?5?$DN?5?$CFd?6?$AA@=007ec5d0
// @ref ??_C@_0BI@JHAI@Frame?5?$CFd?0?5my?5sent?5?$DN?5?$CFd?6?$AA@=007ec4f0
// @ref ??_C@_0BK@OPPK@Failure?5executing?5DoList?6?$AA@=007ec4b4
// @ref ??_C@_0BM@NNNI@Generate_Real_Timing_Event?6?$AA@=007ec53c
// @ref ??_C@_0BO@NLNF@Wait_For_Players?5returned?5?$CFd?6?$AA@=007ec4d0
// @ref ??_C@_0CD@IHEO@Processing?5Ticks?3?$CF03d?5Frames?3?$CF03@=007ec5ac
// @ref ??_C@_0DD@HMFE@Sending?5precalculated?5network?5ti@=007ec508
// @ref ?Wait_For_Players@@YI?AW4RetcodeType@@HPAVConnManClass@@HHHPADHPAUUnknownFrameTiming@@@Z=00624c10
// @ref _?skip_crc@?4??Queue_AI_Multiplayer@@YAXXZ@4V?$CDTimerClass@VFrameTimerClass@@@@A=00aabeb8
// @ref ?Next@?$QueueClass@VEventClass@@$0IA@@@QAEHXZ=0062e9e0
// @ref ?Queue_AI_Multiplayer@@YAXXZ=00623b00
// @ref ??_C@_0BB@KACD@TXT_DISCON_ABORT?$AA@=007ec558
// @ref ??_C@_0BL@BADN@TXT_SCENARIOS_DO_NOT_MATCH?$AA@=007ec57c
// @ref ?unknown_megamission_counts_aabdb0@@3PAHA=00aabdb0
// @ref ?unknown_megamission_frames_aabe94@@3PAHA=00aabe94
// @ref _?$S78@?4??Queue_AI_Multiplayer@@YAXXZ@4EA=00a780d0


static void Queue_AI_Normal()
{
    while (OutList.Count) {
        OutList.First().IsExecuted = false;
        if (!DoList.Add(OutList.First())) {
            ;
        }
        OutList.Next();
    }
    if (unknown_flags_a3f600 & 1) {
        Queue_Record();
    }
    if (!Execute_DoList(1, unknown_player_a35db4->Type->House, 0, 0, 0)) {
        unknown_flag_a40958 = false;
        return;
    }
    Clean_DoList(0);
}

static void Queue_Playback()
{
    int numevents;
    EventClass event;
    int i;
    int ok;
    int max_houses;
    int base_house;
    int key;

    if (WWKeyboard->Check()) {
        key = WWKeyboard->Get();
        if (key == 0x1B || (unknown_flags_a3f600 & 4)) {
            unknown_flag_a40958 = false;
            return;
        }
    }
    if ((unknown_flags_a3f600 & 4) && ::Frame > 0 && (unknown_mouse_x_a76b70 != WWMouse->Get_Mouse_X() || unknown_mouse_y_a76c78 != WWMouse->Get_Mouse_Y())) {
        unknown_flag_a40958 = false;
        return;
    }
    unknown_mouse_x_a76b70 = WWMouse->Get_Mouse_X();
    unknown_mouse_y_a76c78 = WWMouse->Get_Mouse_Y();

    Compute_Game_CRC();
    CRC[::Frame & 0xFF] = GameCRC;

    if (::Frame >= unknown_trap_print_crc_a40314) {
        if (unknown_flag_ab62e8) {
            Unknown_0062DBA0(::Frame % 256, 0);
        } else {
            Print_CRCs(0);
        }
        Unknown_00691320();
        Emergency_Exit(0);
    }

    if (::Frame == 0 && unknown_game_mode_a3d298 != 0) {
        return;
    }

    if ((unknown_game_mode_a3d298 != 0 && unknown_game_mode_a3d298 != 5) && unknown_session_a3d2ac == 2) {
        if (::Frame != (((::Frame + (unknown_frame_send_rate_a3d564 - 1)) / unknown_frame_send_rate_a3d564) * unknown_frame_send_rate_a3d564)) {
            return;
        }
    }

    ok = 1;
    if (unknown_record_file_a3f59c.Read(&numevents, sizeof(numevents)) == sizeof(numevents)) {
        for (i = 0; i < numevents; i++) {
            if (unknown_record_file_a3f59c.Read(&event, sizeof(EventClass)) == sizeof(EventClass)) {
                event.IsExecuted = 0;
                DoList.Add(event);
            } else {
                ok = 0;
                break;
            }
        }
    } else {
        ok = 0;
    }
    if (!ok) {
        unknown_flag_a40958 = false;
        return;
    }

    if (unknown_game_mode_a3d298 == 0) {
        max_houses = 1;
        base_house = unknown_player_a35db4->Type->House;
    } else {
        max_houses = unknown_max_players_a3d558;
        base_house = 0;
    }
    if (!Execute_DoList(max_houses, base_house, 0, 0, 0)) {
        unknown_flag_a40958 = false;
        return;
    }
    Clean_DoList(0);
}

void __fastcall Queue_AI()
{
    if (unknown_flags_a3f600 & 2) {
        Queue_Playback();
    } else {
        switch (unknown_game_mode_a3d298) {
        case 0:
        case 5:
            Queue_AI_Normal();
            break;
        case 1:
        case 2:
        case 3:
        case 4:
            Queue_AI_Multiplayer();
            break;
        }
    }
}

