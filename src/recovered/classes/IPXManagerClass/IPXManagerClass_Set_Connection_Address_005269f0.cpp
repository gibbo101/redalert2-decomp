// void IPXManagerClass::Set_Connection_Address(int id, IPXAddressClass *address) (0x005269F0)
#include "shared/ipx_manager.hpp"

void IPXManagerClass::Set_Connection_Address(int id, IPXAddressClass *address)
{
    int index = Connection_Index(id);
    if (index != -1 && index < NumConnections) {
        Connection[index]->Address = *address;
    }
}
