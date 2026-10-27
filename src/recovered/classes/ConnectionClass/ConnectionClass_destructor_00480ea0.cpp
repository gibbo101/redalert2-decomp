// ConnectionClass::~ConnectionClass() (0x00480EA0)
#include "shared/connection.hpp"
// @ref ??3@YAXPAX@Z=00781d3b

ConnectionClass::~ConnectionClass()
{
    delete[] PacketBuf;
    if (Queue) {
        delete Queue;
    }
}
