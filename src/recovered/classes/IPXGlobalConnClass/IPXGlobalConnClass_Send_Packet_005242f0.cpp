// int IPXGlobalConnClass::Send_Packet(void *buf, int buflen, IPXAddressClass *address, int ack_req, unsigned short id, unsigned long packet_id) (0x005242F0, slot 11)
// Wraps the data in a global header (sequenced only with an ACK and an
// address; numbered by the send total unless a number is given) and queues
// it with the destination address as extra data.
#include "shared/ipx_global_conn.hpp"
// @ref ??0IPXAddressClass@@QAE@XZ=00523410
// @ref ?Queue_Send@CommBufferClass@@QAEHPAXH0HG@Z=004803f0

int IPXGlobalConnClass::Send_Packet(void *buf, int buflen, IPXAddressClass *address, int ack_req, unsigned short id, unsigned long packet_id)
{
    IPXAddressClass dest_addr;

    ((GlobalHeaderType *)PacketBuf)->unknown_08 = 0;
    ((GlobalHeaderType *)PacketBuf)->unknown_0c = 0;
    ((GlobalHeaderType *)PacketBuf)->MagicNumber = MagicNum;
    if (ack_req && address) {
        ((GlobalHeaderType *)PacketBuf)->Code = PACKET_DATA_ACK;
    } else {
        ((GlobalHeaderType *)PacketBuf)->Code = PACKET_DATA_NOACK;
    }
    ((GlobalHeaderType *)PacketBuf)->PacketID = Queue->SendTotal;
    if (packet_id) {
        ((GlobalHeaderType *)PacketBuf)->PacketID = packet_id;
    }
    ((GlobalHeaderType *)PacketBuf)->ProductID = ProductID;
    ((GlobalHeaderType *)PacketBuf)->unknown_03 = 0;
    if (address) {
        dest_addr = *address;
    }
    memcpy(PacketBuf + sizeof(GlobalHeaderType), buf, buflen);
    return Queue->Queue_Send(PacketBuf, buflen + sizeof(GlobalHeaderType), &dest_addr, sizeof(IPXAddressClass), id);
}
