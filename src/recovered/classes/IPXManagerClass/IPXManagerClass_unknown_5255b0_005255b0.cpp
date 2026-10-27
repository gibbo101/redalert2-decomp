// int IPXManagerClass::unknown_5255b0() (0x005255B0)
// Creates the multicast connection to the first node's address.
#include "shared/ipx_manager.hpp"
// @ref ??0IPXConnClass@@QAE@HHHGPAVIPXAddressClass@@HPBGH@Z=00523b70
// @ref ??2@YAPAXI@Z=00782017
// @ref ?unknown_nodes_a3fa7c@@3V?$DynamicVectorClass@PAUUnknownNodeName@@@@A=00a3fa7c
// @ref ?Unknown_006FA180@@YIPAGPBD@Z=006fa180
// @ref ??_C@_09LEIE@Multicast?$AA@=007ddfa0

int IPXManagerClass::unknown_5255b0()
{
    if (!IPXStatus) {
        return 0;
    }
    unknown_50 = new IPXConnClass(Pvt_NumPackets, Pvt_NumPackets, Pvt_MaxPacketLen, ProductID,
        &unknown_nodes_a3fa7c[0]->Address, -1, Unknown_006FA180("Multicast"));
    if (!unknown_50) {
        return 0;
    }
    unknown_50->Init();
    unknown_50->RetryDelta = RetryDelta;
    unknown_50->MaxRetries = MaxRetries;
    unknown_50->Timeout = Timeout;
    return 1;
}
