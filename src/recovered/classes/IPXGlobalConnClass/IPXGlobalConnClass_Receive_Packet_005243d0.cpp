// @ref ??_C@_0BN@BINA@Failed?5to?5ack?5global?5packet?6?$AA@=007ddd34
// @ref ??_C@_0CG@PEFH@Sending?5global?5ack?5packet?5to?5por@=007ddd54
// @ref ??_C@_0CP@EHAN@Failed?5to?5queue?5incoming?5packet?4@=007ddd04
// @ref ??_C@_0CM@PKLM@Queueing?5new?5global?5PACKET_DATA_@=007ddd7c
// @ref ??_C@_0CO@GPJM@Queueing?5new?5global?5PACKET_DATA_@=007ddda8
// @ref ??_C@_0CD@JPDG@Received?5global?5ack?5for?5packet?5?$CF@=007dddd8
// @ref ??_C@_0CH@ONKI@Queueing?5new?5global?5PACKET_ACK?5p@=007dddfc
// Receive global IPX/UDP packets, reject duplicates, and acknowledge reliable data (0x005243D0).
#include "shared/ipx_global_conn.hpp"

int IPXGlobalConnClass::Receive_Packet(void *buf, int buflen, IPXAddressClass *address, unsigned short port)
{
    GlobalHeaderType *packet = (GlobalHeaderType *)buf;
    if (packet->MagicNumber != MagicNum) return 0;
    switch (packet->Code) {
    case PACKET_DATA_ACK: {
        IPXAddressClass received = *address;
        if (port != 0) received.unknown_523960(port);
        int resend = 0;
        for (int index = 0; index < unknown_d4; index++) {
            if ((unsigned int)index >= Queue->ReceiveTotal) break;
            if (received == unknown_cc[index] && packet->PacketID == (unsigned long)unknown_d0[index]) {
                resend = 1;
                break;
            }
        }
        Debug_Printf("Queueing new global PACKET_DATA_ACK packet\n");
        if (!resend) {
            if (Queue->Queue_Receive(buf, buflen, &received, sizeof(received))) {
                unknown_cc[unknown_d8] = received;
                unknown_d0[unknown_d8] = packet->PacketID;
                unknown_d8++;
                if (unknown_d8 >= unknown_d4) unknown_d8 = 0;
            } else {
                Debug_Printf("Failed to queue incoming packet. Ack not sent\n");
                break;
            }
        }
        GlobalHeaderType acknowledgement;
        acknowledgement.MagicNumber = MagicNum;
        acknowledgement.Code = PACKET_ACK;
        acknowledgement.PacketID = packet->PacketID;
        acknowledgement.ProductID = ProductID;
        acknowledgement.unknown_03 = 0;
        Debug_Printf("Sending global ack packet to port %d\n", port);
        ConnectionClass *global_channel = unknown_connection_a409c4;
        if (!Send((char *)&acknowledgement, sizeof(acknowledgement), address, sizeof(IPXAddressClass), this == global_channel, port)) {
            Debug_Printf("Failed to ack global packet\n");
        }
        break;
    }
    case PACKET_DATA_NOACK: {
        Debug_Printf("Queueing new global PACKET_DATA_NOACK packet\n");
        IPXAddressClass received = *address;
        if (port != 0) received.unknown_523960(port);
        Queue->Queue_Receive(buf, buflen, &received, sizeof(received));
        break;
    }
    case PACKET_ACK: {
        Debug_Printf("Queueing new global PACKET_ACK packet\n");
        for (int index = 0; index < Queue->SendCount; index++) {
            SendQueueType *entry = Queue->Get_Send(index);
            GlobalHeaderType *sent = (GlobalHeaderType *)entry->Buffer;
            if (packet->PacketID == sent->PacketID && sent->Code == PACKET_DATA_ACK) {
                entry->IsACK = 1;
                Debug_Printf("Received global ack for packet %d\n", packet->PacketID);
                break;
            }
        }
        break;
    }
    default:
        break;
    }
    return 1;
}
