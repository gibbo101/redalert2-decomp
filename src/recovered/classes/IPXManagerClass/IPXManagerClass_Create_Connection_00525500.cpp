// int IPXManagerClass::Create_Connection(int id, wchar_t const *name, IPXAddressClass *address) (0x00525500)
// Adds a private connection with the current timing.
#include "shared/ipx_manager.hpp"
// @ref ??0IPXConnClass@@QAE@HHHGPAVIPXAddressClass@@HPBGH@Z=00523b70
// @ref ??2@YAPAXI@Z=00782017

int IPXManagerClass::Create_Connection(int id, wchar_t const *name, IPXAddressClass *address)
{
    if (!IPXStatus) {
        return 0;
    }
    if (NumConnections == CONNECT_MAX) {
        return 0;
    }
    Connection[NumConnections] = new IPXConnClass(Pvt_NumPackets, Pvt_NumPackets, Pvt_MaxPacketLen, ProductID, address, id, name);
    if (Connection[NumConnections] == 0) {
        return 0;
    }
    Connection[NumConnections]->Init();
    Connection[NumConnections]->RetryDelta = RetryDelta;
    Connection[NumConnections]->MaxRetries = MaxRetries;
    Connection[NumConnections]->Timeout = Timeout;
    NumConnections++;
    return 1;
}
