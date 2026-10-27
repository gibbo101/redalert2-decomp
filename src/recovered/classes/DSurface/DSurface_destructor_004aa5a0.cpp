// DSurface::~DSurface() (0x004AA5A0)
// Releases the primary surface's clipper (primary only), the description
// and the DirectDraw surface.
#include "shared/dsurface.hpp"
// @ref ?unknown_clipper_852fb4@@3PAUIDirectDrawClipper@@A=00852fb4

DSurface::~DSurface()
{
    if (IsPrimary && VideoSurfacePtr != 0 && unknown_clipper_852fb4 != 0) {
        VideoSurfacePtr->SetClipper(0);
        unknown_clipper_852fb4->Release();
        unknown_clipper_852fb4 = 0;
    }
    delete VideoSurfaceDescription;
    VideoSurfaceDescription = 0;
    if (VideoSurfacePtr != 0) {
        VideoSurfacePtr->Release();
    }
    VideoSurfacePtr = 0;
}
