// int __fastcall Send_Packets(ConnManClass *net, char *multi_packet_buf, int multi_packet_max, int max_ahead,
// int my_sent) (0x006261A0; Red Alert's Send_Packets with Build_Send_Packet and Add_Uncompressed_Events inline).
#include "shared/queue.hpp"
#include "shared/crt_memory.hpp"
// @ref ?GameCRC@@3KA=00a76c74
// @ref ?Frame@@3HA=00a40d2c
// @ref ?Add_Compressed_Events@@YIHPAXHHHHPAH@Z=00627b60
// @ref ??_C@_0DM@KBMB@Send_Packets?5?9?5created?5packet?5wi@=007ec894
// @ref ??_C@_0DH@MFB@Send_Packets?5?9?5added?5total?5of?5?$CFd@=007ec85c

static int Build_Send_Packet(void *buf, int bufsize, int frame_delay, int num_cmds, int cap, int *added);
static int Add_Uncompressed_Events(void *buf, int bufsize, int frame_delay, int size, int cap);

int __fastcall Send_Packets(ConnManClass *net, char *multi_packet_buf, int multi_packet_max, int max_ahead, int my_sent)
{
    int cap;
    int ack_req;
    int packetlen;
    int added;
    int total = 0;

    cap = OutList.Count;
    if (cap > 0x2000 - DoList.Count) {
        cap = 0x2000 - DoList.Count;
    }
    int count = OutList.Count;

    while (true) {
        if (cap == 0 || OutList.Count == 0 || unknown_session_a3d55c == 1) {
            ack_req = 0;
        } else {
            ack_req = 1;
        }
        packetlen = Build_Send_Packet(multi_packet_buf, multi_packet_max, max_ahead, my_sent, cap, &added);
        cap -= added;
        total += added;
        if (added) {
            Debug_Printf("Send_Packets - created packet with %d commands on frame %d\n", added, ::Frame);
            ack_req = 1;
        }
        net->Send_Private_Message(multi_packet_buf, packetlen, ack_req, -1);
        unknown_frame_syncs_ab62e4++;
        net->Service();
        if (OutList.Count == 0 || OutList.Count > count || cap == 0) {
            break;
        }
    }
    if (total) {
        Debug_Printf("Send_Packets - added total of %d commands on frame %d\n", total, ::Frame);
    }
    return total;
}

static int Build_Send_Packet(void *buf, int bufsize, int frame_delay, int num_cmds, int cap, int *added)
{
    int size = 0;
    EventClass *finfo = (EventClass *)buf;

    finfo->Type = 0x1C;
    *added = 0;
    if (unknown_session_a3d2ac == 2) {
        finfo->Frame = ((::Frame + frame_delay + (unknown_frame_send_rate_a3d564 - 1)) / unknown_frame_send_rate_a3d564)
            * unknown_frame_send_rate_a3d564;
    } else {
        finfo->Frame = ::Frame + frame_delay;
    }
    finfo->House = unknown_player_a35db4->ArrayIndex;
    finfo->LongAt(0x07) = GameCRC;
    finfo->ShortAt(0x0B) = num_cmds;
    finfo->ByteAt(0x0D) = frame_delay;
    if (unknown_session_a3d2ac == 0) {
        size += sizeof(EventClass);
    } else {
        size += 0x0E;
    }
    switch (unknown_session_a3d2ac) {
    case 0:
        size = Add_Uncompressed_Events(buf, bufsize, frame_delay, size, cap);
        break;
    case 1:
    case 2:
        size = Add_Compressed_Events(buf, bufsize, frame_delay, size, cap, added);
        break;
    default:
        size = 0;
        break;
    }
    return size;
}

static int Add_Uncompressed_Events(void *buf, int bufsize, int frame_delay, int size, int cap)
{
    int num = 0;
    int ev_size;

    while (OutList.Count && num < cap) {
        if (OutList.First().Type == 0x1F) {
            ev_size = sizeof(EventClass) + OutList.First().LongAt(0x0B);
        } else {
            ev_size = sizeof(EventClass);
        }
        if (size + ev_size > bufsize) {
            return size;
        }
        OutList.First().Frame = ::Frame + frame_delay;
        OutList.First().House = unknown_player_a35db4->ArrayIndex;
        OutList.First().IsExecuted = 0;
        if (!DoList.Add(OutList.First())) {
            return size;
        }
        if (OutList.First().Type == 0x1F) {
            memcpy((char *)buf + size, &OutList.First(), sizeof(EventClass));
            size += sizeof(EventClass);
            memcpy((char *)buf + size, (void *)OutList.First().LongAt(0x07), OutList.First().LongAt(0x0B));
            size += OutList.First().LongAt(0x0B);
        } else {
            memcpy((char *)buf + size, &OutList.First(), sizeof(EventClass));
            size += sizeof(EventClass);
        }
        num++;
        OutList.Next();
    }
    return size;
}
