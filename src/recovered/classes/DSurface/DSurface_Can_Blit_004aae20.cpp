// bool DSurface::Can_Blit() (0x004AAE20, slot 37)
// Whether DirectDraw can accept a blit now (GetBltStatus(DDGBS_CANBLT)).
#include "shared/dsurface.hpp"

bool DSurface::Can_Blit()
{
    return VideoSurfacePtr->GetBltStatus(DDGBS_CANBLT) == DD_OK;
}
