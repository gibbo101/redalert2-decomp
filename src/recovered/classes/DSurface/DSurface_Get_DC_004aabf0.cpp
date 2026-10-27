// HDC DSurface::Get_DC() (0x004AABF0)
// Device context of the DirectDraw surface; holding it counts as a lock.
// Null when the surface is already locked or GetDC fails.
#include "shared/dsurface.hpp"

HDC DSurface::Get_DC()
{
    HDC dc = 0;
    if (!Is_Locked()) {
        if (VideoSurfacePtr->GetDC(&dc) == DD_OK) {
            LockLevel++;
        } else {
            return 0;
        }
    }
    return dc;
}
