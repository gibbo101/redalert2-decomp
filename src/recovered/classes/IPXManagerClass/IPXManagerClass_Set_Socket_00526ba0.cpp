// void IPXManagerClass::Set_Socket(unsigned short socket) (0x00526BA0)
#include "shared/ipx_manager.hpp"

void IPXManagerClass::Set_Socket(unsigned short socket)
{
    Socket = ((socket & 0x00FF) << 8) | ((socket & 0xFF00) >> 8);
}
