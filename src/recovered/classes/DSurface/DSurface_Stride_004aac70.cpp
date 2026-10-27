// int DSurface::Stride() (0x004AAC70, slot 29)
// Row pitch reported by DirectDraw.
#include "shared/dsurface.hpp"

int DSurface::Stride()
{
    return VideoSurfaceDescription->lPitch;
}
