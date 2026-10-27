// int DSurface::Release_DC(HDC dc) (0x004AAC30)
// Gives a device context from Get_DC back and drops its lock.
#include "shared/dsurface.hpp"

int DSurface::Release_DC(HDC dc)
{
    if (VideoSurfacePtr->ReleaseDC(dc) == DD_OK && LockLevel > 0) {
        LockLevel--;
    }
    return 1;
}
