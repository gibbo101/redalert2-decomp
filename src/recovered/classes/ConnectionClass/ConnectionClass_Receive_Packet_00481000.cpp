#include "shared/connection.hpp"
extern char const received_ack_format_007d32e8[];
extern char const no_ack_queue_full_007d32a0[];
extern char const queue_failed_007d325c[];
extern char const connect_source_007d328c[];
extern char const invalid_packet_code_007d3158[];
extern char const ack_queue_full_007d3218[];
extern char const queue_receive_error_007d31d4[];
extern char const sending_ack_format_007d31a0[];
// @ref ?received_ack_format_007d32e8@@=007d32e8
// @ref ?no_ack_queue_full_007d32a0@@=007d32a0
// @ref ?queue_failed_007d325c@@=007d325c
// @ref ?connect_source_007d328c@@=007d328c
// @ref ?invalid_packet_code_007d3158@@=007d3158
// @ref ?ack_queue_full_007d3218@@=007d3218
// @ref ?queue_receive_error_007d31d4@@=007d31d4
// @ref ?sending_ack_format_007d31a0@@=007d31a0
int ConnectionClass::Receive_Packet(void *buf, int buflen)
{
    CommHeaderType *packet = (CommHeaderType *)buf;
    if (packet->MagicNumber != MagicNum) { ++unknown_18; return 0; }
    if (packet->Code == PACKET_ACK) {
        Debug_Printf(received_ack_format_007d32e8, packet->PacketID);
        for (int index = 0; index < Queue->SendCount; ++index) {
            SendQueueType *entry = Queue->Get_Send(index);
            if (entry && packet->PacketID == ((CommHeaderType *)entry->Buffer)->PacketID
                && ((CommHeaderType *)entry->Buffer)->Code == PACKET_DATA_ACK) {
                entry->IsACK = 1;
                break;
            }
        }
        return 1;
    }
    if (packet->Code == PACKET_DATA_NOACK) {
        if (Queue->MaxReceive - Queue->ReceiveCount <= 1) {
            ++unknown_14;
            Debug_Printf(no_ack_queue_full_007d32a0);
            return 0;
        }
        if (!Queue->Queue_Receive(buf, buflen, 0, 0)) {
            Debug_Printf(queue_failed_007d325c, connect_source_007d328c, 0x14c);
            ++unknown_14;
            return 0;
        }
        ++NumRecNoAck;
        unknown_0c = packet->PacketID - NumRecNoAck + 1;
        if (packet->PacketID != 0)
            unknown_10 = 100 - NumRecNoAck * 100 / (packet->PacketID + 1);
        return 1;
    }
    if (packet->Code == PACKET_DATA_ACK) {
        if (packet->PacketID > LastSeqID || LastSeqID == 0xffffffff) {
            for (int index = 0; index < Queue->ReceiveCount; ++index) {
                ReceiveQueueType *entry = Queue->Get_Receive(index);
                if (entry && ((CommHeaderType *)entry->Buffer)->Code == PACKET_DATA_ACK
                    && ((CommHeaderType *)entry->Buffer)->PacketID == packet->PacketID)
                    goto send_ack;
            }
            if (Queue->MaxReceive - Queue->ReceiveCount <= 1 && packet->PacketID != LastSeqID + 1) {
                Debug_Printf(ack_queue_full_007d3218);
                return 0;
            }
            if (!Queue->Queue_Receive(buf, buflen, 0, 0)) {
                Debug_Printf(queue_receive_error_007d31d4);
                return 0;
            }
            ++NumRecAck;
            unsigned long next = packet->PacketID;
            if (next == LastSeqID + 1) {
                while (true) {
                    LastSeqID = next;
                    int index = 0;
                    if (Queue->ReceiveCount <= 0) break;
                    CommHeaderType *queued;
                    do {
                        ReceiveQueueType *entry = Queue->Get_Receive(index);
                        if (entry) {
                            queued = (CommHeaderType *)entry->Buffer;
                            if (queued->Code == PACKET_DATA_ACK && queued->PacketID == LastSeqID + 1) break;
                        }
                        ++index;
                        if (index >= Queue->ReceiveCount) goto send_ack;
                    } while (true);
                    next = queued->PacketID;
                }
            }
        }
send_ack:
        unsigned long receivedID = packet->PacketID;
        CommHeaderType ack;
        ack.MagicNumber = MagicNum;
        ack.Code = PACKET_ACK;
        ack.PacketID = receivedID;
        if (unknown_flag_a3fba8) ack.unknown_03 = packet->unknown_03;
        else ack.unknown_03 = 0;
        Debug_Printf(sending_ack_format_007d31a0, receivedID, ack.unknown_03);
        Send((char *)&ack, sizeof(ack), 0, 0, this == unknown_connection_a409c4, 0);
        return 1;
    }
    Debug_Printf(invalid_packet_code_007d3158);
    return 0;
}
