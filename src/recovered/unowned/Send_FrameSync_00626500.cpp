// void __fastcall Send_FrameSync(ConnManClass *net, int cmd_count) (0x00626500): a FRAMESYNC packet to every player.
#include "shared/queue.hpp"
// @ref ?Frame@@3HA=00a40d2c
// @ref ?unknown_crc_a40770@@3KA=00a40770
// @ref ?unknown_frame_syncs_ab62e4@@3HA=00ab62e4
// @ref ?unknown_frame_send_rate_a3d564@@3IA=00a3d564
// @ref ??_C@_0BM@KFED@Sent?5FrameSync?5only?5packet?6?$AA@=007ec8d0

void __fastcall Send_FrameSync(ConnManClass *net, int cmd_count)
{
    EventClass packet;

    memset(&packet, 0, sizeof(EventClass));
    packet.Type = 0x19;
    if (unknown_session_a3d2ac == 2) {
        packet.Frame = ((::Frame + unknown_max_ahead_a3d560 + (unknown_frame_send_rate_a3d564 - 1)) / unknown_frame_send_rate_a3d564) * unknown_frame_send_rate_a3d564;
    } else {
        packet.Frame = ::Frame + unknown_max_ahead_a3d560;
    }
    packet.House = unknown_player_a35db4->ArrayIndex;
    packet.LongAt(0x07) = unknown_crc_a40770;
    packet.ShortAt(0x0b) = cmd_count;
    packet.ByteAt(0x0d) = unknown_max_ahead_a3d560;
    net->Send_Private_Message(&packet, 0x0E, 0, -1);
    Debug_Printf("Sent FrameSync only packet\n");
    unknown_frame_syncs_ab62e4++;
}
