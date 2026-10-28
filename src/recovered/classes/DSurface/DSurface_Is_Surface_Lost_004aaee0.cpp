// bool DSurface::Is_Surface_Lost() (0x004AAEE0)
// The DirectDraw surface exists and reports DDERR_SURFACELOST.
#include "shared/dsurface.hpp"

bool DSurface::Is_Surface_Lost()
{
    return VideoSurfacePtr != 0 && VideoSurfacePtr->IsLost() == DDERR_SURFACELOST;
}
