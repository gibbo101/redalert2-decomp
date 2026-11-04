#include "shared/queue.hpp"
#include "shared/main_loop.hpp"
#include "shared/session_state.hpp"
#include "shared/null_modem.hpp"
#include "shared/mono_class.hpp"
#include "shared/string_table.hpp"
#include "shared/ww_message_box.hpp"
extern "C" void *__cdecl memset(void *, int, unsigned int);

struct QueueTimeouts { int Resend, Dialog, Sync, Load; };
extern QueueTimeouts unknown_queue_timeouts_7ec438[6];
extern int unknown_sync_counts_a76b74[8][8];
extern bool unknown_flag_a3d8d1, unknown_flag_abd500;

extern NullModemClass unknown_null_modem_a40a28;
extern unsigned short const unknown_caption_7d64f4[];
MonoClass *__fastcall Mono_Page_0059da50(int page);
void Mono_Window_Show_0059d9c0();
int __fastcall Wait_For_Players(int first_time, ConnManClass *net, int resend, int dialog,
    int timeout, char *buffer, int sent, UnknownFrameTiming *their);

#define WestwoodMAX(a,b) (((a)>(b))?(a):(b))
#define WestwoodMIN(a,b) (((a)<(b))?(a):(b))

static void __fastcall Generate_Process_Time_Event_00623b00(ConnManClass *net)
{
    EventClass packet;

        unsigned long response=net->Response_Time();
        switch(unknown_a3fba4) {
        case 0: break;
        case 1: response+=response>>1; break;
        case 2: response*=2; break;
        case 3: response*=3; break;
        default: goto latency_done;
        }
        Debug_Printf("Response time = %d\n",response);
latency_done:
        unsigned long timeout=response*8+15;
        if (timeout<120) timeout=120;
        net->Set_Timing(response+10,-1,timeout,false);
        if (unknown_ab62dc) {
            Mono_Window_Show_0059d9c0();
            MonoClass *page=Mono_Page_0059da50(4);
            page->Set_Cursor(0,23);
            page->Printf("Processing Ticks:%03d Frames:%03d\n",unknown_process_ticks_a3d570,unknown_process_frames_a3d574);
            Unknown_0059DA00();
        }
        packet.Type=0x21;
        packet.Data.ProcessTime.AverageTicks=unknown_process_ticks_a3d570/unknown_process_frames_a3d574;
        packet.Frame=Frame;
        packet.House=unknown_player_a35db4->ArrayIndex;
        OutList.Add(packet);
        unknown_process_ticks_a3d570=0;
        unknown_process_frames_a3d574=0;
        if (unknown_game_mode_a3d298==4 && (Frame&2047)==0) net->Reset_Response_Time(false);
}

static void __fastcall Generate_Real_Timing_Event_00623b00(ConnManClass *net, int my_sent)
{
    EventClass packet;
    int i;
        Debug_Printf("Generate_Real_Timing_Event\n");
        if(unknown_session_a3d298.unknown_2e4!=0 || unknown_session_a3d298.unknown_2e8!=0) {
            Debug_Printf("Sending precalculated network timings on frame %d\n");
            packet.Type=0x20;
            packet.Data.Timing.DesiredFrameRate=unknown_a3d580;
            packet.Data.Timing.MaxAhead=unknown_session_a3d298.unknown_2e4;
            packet.Data.Timing.FrameSendRate=(unsigned int)unknown_session_a3d298.unknown_2e8>30U?10:5;
            packet.Frame=Frame;
            packet.House=unknown_player_a35db4->ArrayIndex;
            OutList.Add(packet);
            unknown_session_a3d298.unknown_2e4=0;unknown_session_a3d298.unknown_2e8=0;
        
            return;
        }
        if(my_sent<5)return;

                int worst=0;
                for (i=0;i<unknown_session_a3d298.Players.Count();i++) {
                    int ticks=unknown_session_a3d298.Players[i]->unknown_63;
                    if (ticks==-1) return;
                    if (ticks>worst) worst=ticks;
                }
                int desired;
                if (worst==0) desired=60;
                else desired=WestwoodMAX(1,1000/worst);
                int cap;
                switch(unknown_a40b18) {
                case 0:cap=60;break;
                case 1:cap=45;break;
                default:cap=60/unknown_a40b18;break;
                }
                desired=WestwoodMIN(desired,cap);
                unsigned long response;
                if(unknown_game_mode_a3d298==4 && unknown_session_a3d298.ViaPacketRouter) {
                    response=((IPXManagerClass*)net)->unknown_526c70();
                    unsigned long worst_response=0;
                    for(i=0;i<net->Num_Connections();i++) {
                        worst_response=WestwoodMAX(worst_response,(unsigned long)unknown_their_timing_aabdd0[i].unknown_10);
                    }
                    response+=worst_response;
                } else response=net->Response_Time();
                int connection_response=net->Response_Time();
                unsigned char send_rate=(unsigned char)unknown_frame_send_rate_a3d564;
                if(unknown_game_mode_a3d298==4)send_rate=desired>30?10:5;
                int base=0;
                if(response!=0) {
                    switch(unknown_a3fba4) {
                    case 0:break;
                    case 1:response+=response>>1;base=10;connection_response+=connection_response/2;break;
                    case 2:response*=2;connection_response*=2;base=20;break;
                    case 3:response*=3;connection_response*=3;base=30;break;
                    default:goto timing_latency_done;
                    }
                    Debug_Printf("Response time = %d\n",response);
                }
timing_latency_done:
                int ahead=(response*desired)/120+base;
                if(ahead>unknown_max_ahead_a3d560) ahead=WestwoodMIN(ahead,unknown_max_ahead_a3d560+send_rate);
                ahead=((ahead-1+send_rate)/send_rate)*send_rate;
                ahead=WestwoodMAX(ahead,(int)send_rate*3);
                int max_ahead=((send_rate+249)/send_rate)*send_rate;
                ahead=WestwoodMIN(ahead,max_ahead);
                packet.Type=0x20;
                packet.Data.Timing.DesiredFrameRate=desired;
                packet.Frame=Frame;
                packet.House=unknown_player_a35db4->ArrayIndex;
                packet.Data.Timing.MaxAhead=ahead+(unknown_id_source_a3d290->Special().FogOfWar?10:0);
                packet.Data.Timing.FrameSendRate=send_rate;
                OutList.Add(packet);
                int timeout=connection_response*8+15;
                if(timeout<120)timeout=120;
                net->Set_Timing(connection_response+10,-1,timeout,false);
            
}

static void __fastcall Stop_Game_00623b00(bool cancelled)
{
    unknown_a3d8c8=0;
    unknown_a3d8cc=0;
    unknown_flag_a40958=false;
    if(unknown_ab62dc)Unknown_0059DA00();
    if(unknown_game_mode_a3d298==4) {
        unknown_flag_abd500=true;
        if(!cancelled)unknown_flag_a3d8d1=true;
        unknown_flag_a3d8d2=true;
        Unknown_0069A160();
        Unknown_00698D00(false);
    }
}

static int __fastcall Process_Send_Period_00623b00(ConnManClass *net)
{
    if(Frame!=(int)(((Frame+(unknown_frame_send_rate_a3d564-1))/unknown_frame_send_rate_a3d564)*unknown_frame_send_rate_a3d564)) {
        net->Service();
        if(unknown_ab62dc)Unknown_0059DA00();
        return 0;
    }
    return 1;
}

void __fastcall Queue_AI_Multiplayer()
{
    if (unknown_game_mode_a3d298 == 5) return;
    ConnManClass *net;
    char *buffer;
    int maximum;
    bool is_error;
    static CDTimerClass<FrameTimerClass> skip_crc;
    int i;
    int rc;
    if (unknown_game_mode_a3d298 >= 3 && unknown_game_mode_a3d298 <= 4) {
        buffer = unknown_meta_packet_a3f81a;
        maximum = unknown_meta_size_a3fa48;
        net = &unknown_ipx_manager_a40978;
    } else {
        buffer = unknown_null_modem_a40a28.BuildBuf;
        maximum = unknown_null_modem_a40a28.MaxLen - 14;
        net = &unknown_null_modem_a40a28;
    }
    Compute_Game_CRC();
    CRC[Frame & 255] = GameCRC;
    if (Frame == 0 || unknown_a3d8c8) {
        for (i = 0; i < 7; i++) {
            unknown_their_timing_aabdd0[i].Frame = -1;
            unknown_their_timing_aabdd0[i].unknown_04 = 0;
            unknown_their_timing_aabdd0[i].unknown_08 = 0;
            unknown_their_timing_aabdd0[i].unknown_0c = 0;
            unknown_their_timing_aabdd0[i].unknown_14 = 0;
            unknown_their_timing_aabdd0[i].unknown_10 = 20;
        }
        unknown_my_sent_aabe78 = 0;
        skip_crc = Frame + sizeof(CRC)/sizeof(CRC[0]);
        memset(CRC,0,sizeof(CRC));
        memset(unknown_megamission_frames_aabe94,0,sizeof(unknown_megamission_frames_aabe94));
        unknown_ab62ec=0; unknown_ab62f0=0; unknown_ab62f4=false;
        unknown_ab62f5=false; unknown_ab62e0=false;
        memset(unknown_megamission_counts_aabdb0,0,sizeof(unknown_megamission_counts_aabdb0));
        for(i=0;i<32;i+=4) for(int j=0;j<8;j++) *(int *)((char *)&unknown_sync_counts_a76b74[j][0]+i)=0;
        if (unknown_a3d8c8) unknown_crc_a40770=unknown_a3d8cc ? 0 : GameCRC;
        unknown_frame_syncs_ab62e4=0;
        unknown_timer_a780c0=UnknownElapsedTimer();
        Send_FrameSync(net,unknown_my_sent_aabe78);
        rc=Wait_For_Players(1,net,unknown_queue_timeouts_7ec438[unknown_game_mode_a3d298].Resend,
            unknown_queue_timeouts_7ec438[unknown_game_mode_a3d298].Dialog,
            unknown_queue_timeouts_7ec438[unknown_game_mode_a3d298].Load,buffer,unknown_my_sent_aabe78,unknown_their_timing_aabdd0);
        if (rc!=0) {
            if (unknown_game_mode_a3d298==4) Unknown_0069A160();
            is_error=true;
            unknown_counter_a3fabc++;
            if (rc==7) WWMessageBox(unknown_caption_7d64f4).Process(
                StringTable::Load_String("TXT_SYSTEM_NOT_RESPONDING",0,"D:\\Ra2\\Queue.CPP",0x40d),
                StringTable::Load_String("TXT_OK",0,"D:\\Ra2\\Queue.CPP",0x40d),0,0,false);
            else if (rc==2) WWMessageBox(unknown_caption_7d64f4).Process(
                StringTable::Load_String("TXT_SCENARIOS_DO_NOT_MATCH",0,"D:\\Ra2\\Queue.CPP",0x410),
                StringTable::Load_String("TXT_OK",0,"D:\\Ra2\\Queue.CPP",0x410),0,0,false);
            else if (rc==3) WWMessageBox(unknown_caption_7d64f4).Process(
                StringTable::Load_String("TXT_QUEUE_FULL",0,"D:\\Ra2\\Queue.CPP",0x413),
                StringTable::Load_String("TXT_OK",0,"D:\\Ra2\\Queue.CPP",0x413),0,0,false);
            else if (rc==8) is_error=false;
            else if (rc==9) {
                WWMessageBox(unknown_caption_7d64f4).Process(
                    StringTable::Load_String("TXT_DISCON_ABORT",0,"D:\\Ra2\\Queue.CPP",0x419),
                    StringTable::Load_String("TXT_OK",0,"D:\\Ra2\\Queue.CPP",0x419),0,0,false);
                is_error=false;
            }
            unknown_counter_a3fabc--;
            Stop_Game_00623b00(!is_error);
            return;
        }
        UnknownFrameTiming *timing=unknown_their_timing_aabdd0;
        for(i=0;i<7;i++)unknown_a3fb84[i]=0;
        for(;(int)timing<(int)(unknown_their_timing_aabdd0+7);timing++)timing->Frame=0;
        net->Reset_Response_Time(true);
        if(unknown_session_a3d2ac==2)Process_Send_Period_00623b00(net);
        if (unknown_a3d8c8) { unknown_a3d8cc=0; unknown_a3d8c8=0; }
    } else if ((Frame & 127)==0) {
        Generate_Process_Time_Event_00623b00(net);
    }
    if (unknown_session_a3d298.Am_I_Master(0) &&
        (unknown_session_a3d298.unknown_2e4!=0 || unknown_session_a3d298.unknown_2e8!=0 || !(char)Frame)) {
        Generate_Real_Timing_Event_00623b00(net,unknown_my_sent_aabe78);
    }
    if(unknown_session_a3d2ac==2) {
        if(!Process_Send_Period_00623b00(net)) {
            if(unknown_ab62dc)Unknown_0059DA00();
            return;
        }
    }
    {
        int sent=(unsigned short)Send_Packets(net,buffer,maximum,unknown_max_ahead_a3d560,unknown_my_sent_aabe78);
        unknown_my_sent_aabe78+=sent;
        if(sent)Debug_Printf("Frame %d, my sent = %d\n",Frame,unknown_my_sent_aabe78);
    }
    if(Frame==0) {if(unknown_ab62dc)Unknown_0059DA00();return;}
    rc=Wait_For_Players(0,net,180,
        ((int)net->Response_Time()*3 > unknown_queue_timeouts_7ec438[unknown_game_mode_a3d298].Sync)
            ? (int)net->Response_Time()*3 : unknown_queue_timeouts_7ec438[unknown_game_mode_a3d298].Sync,
        unknown_queue_timeouts_7ec438[unknown_game_mode_a3d298].Load,buffer,unknown_my_sent_aabe78,unknown_their_timing_aabdd0);
    if(rc!=0) {
        Debug_Printf("Wait_For_Players returned %d\n",rc);
        if(unknown_game_mode_a3d298==4)Unknown_0069A160();
        is_error=true;unknown_counter_a3fabc++;
        if(rc==7)WWMessageBox(unknown_caption_7d64f4).Process(StringTable::Load_String("TXT_SYSTEM_NOT_RESPONDING",0,"D:\\Ra2\\Queue.CPP",0x4ab),StringTable::Load_String("TXT_OK",0,"D:\\Ra2\\Queue.CPP",0x4ab),0,0,false);
        else if(rc==2)WWMessageBox(unknown_caption_7d64f4).Process(StringTable::Load_String("TXT_SCENARIOS_DO_NOT_MATCH",0,"D:\\Ra2\\Queue.CPP",0x4af),StringTable::Load_String("TXT_OK",0,"D:\\Ra2\\Queue.CPP",0x4af),0,0,false);
        else if(rc==3)WWMessageBox(unknown_caption_7d64f4).Process(StringTable::Load_String("TXT_QUEUE_FULL",0,"D:\\Ra2\\Queue.CPP",0x4b3),StringTable::Load_String("TXT_OK",0,"D:\\Ra2\\Queue.CPP",0x4b3),0,0,false);
        else if(rc==8)is_error=false;
        else if(rc==9){WWMessageBox(unknown_caption_7d64f4).Process(StringTable::Load_String("TXT_DISCON_ABORT",0,"D:\\Ra2\\Queue.CPP",0x4bb),StringTable::Load_String("TXT_OK",0,"D:\\Ra2\\Queue.CPP",0x4bb),0,0,false);is_error=false;}
        unknown_counter_a3fabc--;
        Stop_Game_00623b00(!is_error);
        return;
    }
    if(unknown_session_a3d298.Record)Queue_Record();
    if(!Execute_DoList(unknown_max_players_a3d558,0,net,&skip_crc,unknown_their_timing_aabdd0)) {
        Debug_Printf("Failure executing DoList\n");
        if(unknown_game_mode_a3d298==4)Unknown_0069A160();
        Stop_Game_00623b00(false);
        return;
    }
    Clean_DoList(net);
    if(unknown_ab62dc)Unknown_0059DA00();
    return;

}


// References verified on the required target; timer thunk full16-byte proof is in timer-thunk-proof.json.
// @ref ??_C@_06DN@TXT_OK?$AA@=007db8f4
// @ref ??_C@_0BB@FEBL@D?3?2Ra2?2Queue?4CPP?$AA@=007ec598
// @ref ??_C@_0BB@KACD@TXT_DISCON_ABORT?$AA@=007ec558
// @ref ??_C@_0BE@HIML@Response?5time?5?$DN?5?$CFd?6?$AA@=007ec5d0
// @ref ??_C@_0BI@JHAI@Frame?5?$CFd?0?5my?5sent?5?$DN?5?$CFd?6?$AA@=007ec4f0
// @ref ??_C@_0BK@GPBE@TXT_SYSTEM_NOT_RESPONDING?$AA@=007e222c
// @ref ??_C@_0BK@OPPK@Failure?5executing?5DoList?6?$AA@=007ec4b4
// @ref ??_C@_0BL@BADN@TXT_SCENARIOS_DO_NOT_MATCH?$AA@=007ec57c
// @ref ??_C@_0BM@NNNI@Generate_Real_Timing_Event?6?$AA@=007ec53c
// @ref ??_C@_0BO@NLNF@Wait_For_Players?5returned?5?$CFd?6?$AA@=007ec4d0
// @ref ??_C@_0CD@IHEO@Processing?5Ticks?3?$CF03d?5Frames?3?$CF03@=007ec5ac
// @ref ??_C@_0DD@HMFE@Sending?5precalculated?5network?5ti@=007ec508
// @ref ??_C@_0P@CAII@TXT_QUEUE_FULL?$AA@=007ec56c
// @ref ?Mono_Window_Show_0059d9c0@@YAXXZ=0059d9c0
// @ref ?Unknown_00698D00@@YIX_N@Z=00698d00
// @ref ?Wait_For_Players@@YIHHPAVConnManClass@@HHHPADHPAUUnknownFrameTiming@@@Z=00624c10
// @ref ?unknown_caption_7d64f4@@3QBGB=007d64f4
// @ref ?unknown_megamission_counts_aabdb0@@3PAHA=00aabdb0
// @ref ?unknown_megamission_frames_aabe94@@3PAHA=00aabe94
// @ref ?unknown_null_modem_a40a28@@3VNullModemClass@@A=00a40a28
// @ref ?unknown_queue_timeouts_7ec438@@3PAUQueueTimeouts@@A=007ec438
// @ref ?unknown_sync_counts_a76b74@@3PAY07HA=00a76b74
// @ref _$E79=00624840
// @ref _?$S78@?3??Queue_AI_Multiplayer@@YIXXZ@4EA=00a780d0
// @ref _?skip_crc@?3??Queue_AI_Multiplayer@@YIXXZ@4V?$CDTimerClass@VFrameTimerClass@@@@A=00aabeb8

