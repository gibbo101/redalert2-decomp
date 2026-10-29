// void __fastcall Wait_For_End_Game() (0x00624850; name hypothesis from its traces).
#include "shared/queue.hpp"
#include "shared/display.hpp"
#include "shared/map_view.hpp"
#include "shared/tactical.hpp"
#include "shared/serial_progress.hpp"
#include "shared/cd_timer.hpp"
// @ref ?Frame@@3HA=00a40d2c
// @ref ??_C@_0BB@FKCM@Dolist?5is?5full?$CB?6?$AA@=007ec640
// @ref ??_C@_0BE@ILKF@Entering?5wait?5loop?6?$AA@=007ec6b4
// @ref ??_C@_0BF@GBGE@Resending?5framesync?6?$AA@=007ec69c
// @ref ??_C@_0BG@JCLB@Waiting?5to?5exit?5game?6?$AA@=007ec6c8
// @ref ??_C@_0BJ@OBEE@their_oldest_frame?5?$DN?5?$CFd?6?$AA@=007ec624
// @ref ??_C@_0CB@HNJP@Timed?5out?5waiting?5for?5end?5game?$CB?6@=007ec654
// @ref ??_C@_0CD@COBP@Waiting?5for?5player?5?$CFd?5on?5frame?5?$CF@=007ec678
// @ref ??_C@_0DO@EIEJ@All?5players?5have?5finished?5?9?5read@=007ec5e4
// @ref ?Get_Input@GScreenClass@@UAEXAAH00@Z=004e09d0
// @ref ?Keyboard_Process@@YIXAAH@Z=005406e0
// @ref ?Process_Receive_Packet@@YI?AW4RetcodeType@@PAVConnManClass@@PADHHPAUUnknownFrameTiming@@PAUUnknownElapsedTimer@@@Z=006265c0
// @ref ?Process_Serial_Packet@@YI?AW4RetcodeType@@PADH@Z=00626b30
// @ref ?Send_Packets@@YIHPAVConnManClass@@PADHHH@Z=006261a0
// @ref ?unknown_meta_packet_a3f81a@@3PADA=00a3f81a
// @ref ?unknown_meta_size_a3fa48@@3HA=00a3fa48
// @ref ?unknown_my_sent_aabe78@@3GA=00aabe78
// @ref ?unknown_their_timing_aabdd0@@3PAUUnknownFrameTiming@@A=00aabdd0

// Defined in this unit: the compiler then reads it with a 32-bit load and a mask.
unsigned short unknown_my_sent_aabe78;

void __fastcall Wait_For_End_Game()
{
    ConnManClass *net;
    char *multi_packet_buf;
    int multi_packet_max;
    int packetlen;
    int id;
    int input;
    int x;
    int y;
    int i;

    Debug_Printf("Waiting to exit game\n");
    if (unknown_session_a3d298.Type >= 3 && unknown_session_a3d298.Type <= 4) {
        multi_packet_buf = unknown_meta_packet_a3f81a;
        net = &unknown_ipx_manager_a40978;
        multi_packet_max = unknown_meta_size_a3fa48;
    } else {
        multi_packet_buf = serial_manager_00a40a28.BuildBuf;
        net = &serial_manager_00a40a28;
        multi_packet_max = serial_manager_00a40a28.MaxLen - 0x0E;
    }
    unknown_my_sent_aabe78 += Send_Packets(net, multi_packet_buf, multi_packet_max, unknown_max_ahead_a3d560, unknown_my_sent_aabe78);

    CDTimerClass<SystemTimerClass> framesync_timer = 15;
    CDTimerClass<SystemTimerClass> timeout_timer = 600;
    UnknownElapsedTimer elapsed;

    Debug_Printf("Entering wait loop\n");
    while (true) {
        WWKeyboard->Check();
        if (framesync_timer.Value() == 0) {
            framesync_timer = 15;
            Debug_Printf("Resending framesync\n");
            Send_FrameSync(net, unknown_my_sent_aabe78);
        }
        net->Service();
        if (timeout_timer.Value() == 0) {
            Debug_Printf("Timed out waiting for end game!\n");
            return;
        }
        int count = 1;
        while (true) {
            if (!net->Get_Private_Message(multi_packet_buf, &packetlen, &id)) {
                break;
            }
            WWKeyboard->Check();
            if (unknown_session_a3d298.Type == 1 || unknown_session_a3d298.Type == 2) {
                switch (Process_Serial_Packet(multi_packet_buf, 0)) {
                case RC_NORMAL:
                    break;
                case RC_PLAYER_READY:
                case RC_SCENARIO_MISMATCH:
                case RC_DOLIST_FULL:
                    return;
                case RC_SERIAL_PROCESSED:
                    net->Service();
                    framesync_timer = 15;
                    timeout_timer = 600;
                    break;
                case RC_PLAYER_LEFT:
                case RC_HUNG_UP:
                    return;
                default:
                    return;
                }
            } else {
                if (Process_Receive_Packet(net, multi_packet_buf, id, packetlen, unknown_their_timing_aabdd0, &elapsed) == RC_DOLIST_FULL) {
                    Debug_Printf("Dolist is full!\n");
                    return;
                }
            }
            net->Service();
            if (count++ >= 64) {
                break;
            }
        }
        unknown_481fb0();
        if (!unknown_int_a40d48) {
            Map.Get_Input(input, x, y);
            Keyboard_Process(input);
            unknown_tactical_83996c->AI();
            Map.Render();
        }

        int their_oldest_frame = ::Frame + 1000;
        int oldest_index = -1;
        for (i = 0; i < net->Num_Connections(); i++) {
            if (unknown_their_timing_aabdd0[i].Frame < their_oldest_frame) {
                their_oldest_frame = unknown_their_timing_aabdd0[i].Frame;
                oldest_index = i;
            }
        }
        if (their_oldest_frame + (int)unknown_frame_send_rate_a3d564 >= ::Frame) {
            Debug_Printf("their_oldest_frame = %d\n", their_oldest_frame);
            Debug_Printf("All players have finished - ready to proceed to score screen\n");
            Send_FrameSync(net, unknown_my_sent_aabe78);
            Send_FrameSync(net, unknown_my_sent_aabe78);
            Send_FrameSync(net, unknown_my_sent_aabe78);
            Send_FrameSync(net, unknown_my_sent_aabe78);
            return;
        }
        Debug_Printf("Waiting for player %d on frame %d\n", oldest_index, unknown_their_timing_aabdd0[oldest_index].Frame);
    }
}
