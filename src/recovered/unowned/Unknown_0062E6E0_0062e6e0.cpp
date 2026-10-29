// void __fastcall Unknown_0062E6E0(EventClass *event) (0x0062E6E0): a local event at the head of DoList.
#include "shared/queue.hpp"
#include "shared/wol_sink.hpp"
#include "shared/ww_message_box.hpp"
#include "shared/string_table.hpp"
// @ref ?Frame@@3HA=00a40d2c
// @ref ?unknown_frame_send_rate_a3d564@@3IA=00a3d564
// @ref ?Unknown_0069A160@@YAXXZ=0069a160
// @ref ?Unknown_00698D00@@YIX_N@Z=00698d00
// @ref ?Unknown_0059DA00@@YAXXZ=0059da00
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
// @ref ?DoList@@3V?$QueueClass@VEventClass@@$0EAAA@@@A=00866270

void __fastcall Unknown_0062E6E0(EventClass *event)
{
    long frame = ::Frame + 1;
    if (unknown_session_a3d2ac == 2) {
        frame = ((::Frame + 1 + (unknown_frame_send_rate_a3d564 - 1)) / unknown_frame_send_rate_a3d564) * unknown_frame_send_rate_a3d564;
    }
    event->Frame = frame;
    if (DoList.Count < 0x4000) {
        if (DoList.Head == 0) {
            DoList.Head = 0x3FFF;
        } else {
            DoList.Head--;
        }
        DoList.Array[DoList.Head] = *event;
        DoList.Timings[DoList.Head] = timeGetTime();
        DoList.Count++;
        return;
    }
    if (unknown_game_mode_a3d298 != 0 && unknown_game_mode_a3d298 != 5) {
        if (unknown_game_mode_a3d298 == 4) {
            Unknown_0069A160();
        }
        unknown_counter_a3fabc++;
        WWMessageBox(L" ").Process(StringTable::Load_String("TXT_QUEUE_FULL", 0, "D:\\Ra2\\Queue.CPP", 8826),
                                   StringTable::Load_String("TXT_OK", 0, "D:\\Ra2\\Queue.CPP", 8826), 0, 0, false);
        unknown_counter_a3fabc--;
        unknown_a3d8c8 = 0;
        unknown_a3d8cc = 0;
        unknown_flag_a40958 = false;
        if (unknown_ab62dc) {
            Unknown_0059DA00();
        }
        if (unknown_game_mode_a3d298 == 4) {
            unknown_flag_abd500 = true;
            unknown_flag_a3d8d1 = true;
            unknown_flag_a3d8d2 = true;
            Unknown_0069A160();
            Unknown_00698D00(false);
        }
    }
}
