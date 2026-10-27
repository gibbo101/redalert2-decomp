// int ConnectionClass::Send_Packet(void *buf, int buflen, int ack_req, unsigned char target) (0x00480F00, slot 2)
// Wraps the data in a header (sequenced when an ACK is wanted) and queues
// it for sending.
#include "shared/connection.hpp"
// @ref ?Debug_Printf@@YAXPBDZZ=004068f0
// @ref ?Queue_Send@CommBufferClass@@QAEHPAXH0HG@Z=004803f0
// @ref ?unknown_game_mode_a3d298@@3HA=00a3d298
// @ref ?unknown_flag_a3fba8@@3_NA=00a3fba8
// @ref ??_C@_0N@CJME@buflen?5?$DN?5?$CFd?6?$AA@=007d3120
// @ref ??_C@_0BD@CCED@MaxPacketLen?5?$DN?5?$CFd?6?$AA@=007d3130
// @ref ??_C@_0BB@GHDM@NumSendAck?5?$DN?5?$CFd?6?$AA@=007d3144

int ConnectionClass::Send_Packet(void *buf, int buflen, int ack_req, unsigned char target)
{
    ((CommHeaderType *)PacketBuf)->MagicNumber = MagicNum;
    if (ack_req) {
        ((CommHeaderType *)PacketBuf)->Code = PACKET_DATA_ACK;
        ((CommHeaderType *)PacketBuf)->PacketID = NumSendAck;
        Debug_Printf("NumSendAck = %d\n", NumSendAck);
    } else {
        ((CommHeaderType *)PacketBuf)->Code = PACKET_DATA_NOACK;
        ((CommHeaderType *)PacketBuf)->PacketID = NumSendNoAck;
    }
    if (unknown_game_mode_a3d298 == 4 && unknown_flag_a3fba8) {
        ((CommHeaderType *)PacketBuf)->unknown_03 = target;
    }
    if (MaxPacketLen < buflen) {
        Debug_Printf("MaxPacketLen = %d\n", MaxPacketLen);
        Debug_Printf("buflen = %d\n", buflen);
        return 0;
    }
    memcpy(PacketBuf + sizeof(CommHeaderType), buf, buflen);
    if (Queue->Queue_Send(PacketBuf, buflen + sizeof(CommHeaderType), 0, 0, 0)) {
        if (ack_req) {
            NumSendAck++;
        } else {
            NumSendNoAck++;
        }
        return 1;
    }
    return 0;
}
