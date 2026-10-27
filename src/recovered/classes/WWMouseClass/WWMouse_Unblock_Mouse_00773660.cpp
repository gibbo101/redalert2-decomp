// void Unblock_Mouse() (0x00773660)
// Releases the mouse mutex (always expanded inline; this copy is never called).
#include "shared/wwmouse.hpp"
// @ref ?MouseMutex@@3PAXA=00b2af60

void Unblock_Mouse()
{
    ReleaseMutex(MouseMutex);
}
