// IPXManagerClass::IPXManagerClass(int glb_maxlen, int pvt_maxlen, int glb_num_packets, int pvt_num_packets, unsigned short socket, unsigned short product_id) (0x00525030)
// Probes for a transport (creating and dropping an IPX interface), then
// keeps the channel sizes, the byte-swapped socket and default timing.
#include "shared/ipx_manager.hpp"
// @ref ??_7IPXManagerClass@@6B@=007a46e4
// @ref ??2@YAPAXI@Z=00782017
// @ref ??0IPXInterfaceClass@@QAE@XZ=0076a070
// @ref ?Init@WinsockInterfaceClass@@QAE_NXZ=0076b0a0
// @ref ?PacketTransport@@3PAVWinsockInterfaceClass@@A=00839c50

IPXManagerClass::IPXManagerClass(int glb_maxlen, int pvt_maxlen, int glb_num_packets, int pvt_num_packets,
    unsigned short socket, unsigned short product_id)
{
    if (PacketTransport) {
        delete PacketTransport;
        PacketTransport = 0;
    }
    PacketTransport = new IPXInterfaceClass;
    if (PacketTransport->Init()) {
        IPXStatus = true;
    } else {
        IPXStatus = false;
    }
    if (PacketTransport) {
        delete PacketTransport;
    }
    PacketTransport = 0;

    Listening = false;
    Glb_MaxPacketLen = glb_maxlen;
    Glb_NumPackets = glb_num_packets;
    Pvt_MaxPacketLen = pvt_maxlen;
    Pvt_NumPackets = pvt_num_packets;
    unknown_18 = glb_maxlen;
    unknown_1c = pvt_num_packets;
    ProductID = product_id;
    Socket = ((socket & 0x00FF) << 8) | ((socket & 0xFF00) >> 8);
    ConnectionNum = 0;
    NumConnections = 0;
    CurConnection = 0;
    for (int i = 0; i < CONNECT_MAX; i++) {
        Connection[i] = 0;
    }
    GlobalChannel = 0;
    unknown_a8 = -1;
    MaxRetries = 0xFFFFFFFF;
    unknown_4c = 0;
    unknown_50 = 0;
    SendOverflows = 0;
    unknown_a4 = 0;
    RetryDelta = 2;
    Timeout = 60;
}
