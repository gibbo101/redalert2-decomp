// IPXManagerClass::~IPXManagerClass() (0x00525130)
// Stops listening and deletes the channels and every connection.
#include "shared/ipx_manager.hpp"
// @ref ?Stop_Listening@IPXConnClass@@SAHXZ=00523cf0
// @ref ??_7ConnManClass@@6B@=007a474c

IPXManagerClass::~IPXManagerClass()
{
    if (Listening) {
        IPXConnClass::Stop_Listening();
        Listening = false;
    }
    if (GlobalChannel) {
        delete GlobalChannel;
        GlobalChannel = 0;
    }
    if (unknown_4c) {
        delete unknown_4c;
        unknown_4c = 0;
    }
    if (unknown_50) {
        delete unknown_50;
        unknown_50 = 0;
    }
    for (int i = 0; i < NumConnections; i++) {
        delete Connection[i];
        Connection[i] = 0;
    }
    NumConnections = 0;
}
