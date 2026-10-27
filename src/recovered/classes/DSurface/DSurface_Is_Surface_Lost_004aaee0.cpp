// int DSurface::Is_Surface_Lost() (0x004AAEE0)
// The DirectDraw surface exists and reports DDERR_SURFACELOST.
#include "shared/dsurface.hpp"

int DSurface::Is_Surface_Lost()
{
    if (VideoSurfacePtr != 0 && VideoSurfacePtr->IsLost() == DDERR_SURFACELOST) {
        return 1;
    }
    return 0;
}
