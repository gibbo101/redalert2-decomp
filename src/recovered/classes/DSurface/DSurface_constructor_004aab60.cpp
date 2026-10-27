// DSurface::DSurface(IDirectDrawSurface *surface) (0x004AAB60)
// Wraps an existing DirectDraw surface and takes its size, pixel size and
// memory placement from its description.
#include "shared/crt_memory.hpp"
#include "shared/dsurface.hpp"

DSurface::DSurface(IDirectDrawSurface *surface)
    : BytesPerPixel(0),
      BufferPtr(0),
      IsPrimary(false),
      IsVideoRam(false),
      VideoSurfacePtr(surface),
      VideoSurfaceDescription(0)
{
    if (surface != 0) {
        VideoSurfaceDescription = new DDSURFACEDESC;
        memset(VideoSurfaceDescription, 0, sizeof(DDSURFACEDESC));
        VideoSurfaceDescription->dwSize = sizeof(DDSURFACEDESC);
        if (VideoSurfacePtr->GetSurfaceDesc(VideoSurfaceDescription) == DD_OK) {
            BytesPerPixel = (VideoSurfaceDescription->ddpfPixelFormat.dwRGBBitCount + 7) / 8;
            IsVideoRam = (VideoSurfaceDescription->ddsCaps.dwCaps & DDSCAPS_VIDEOMEMORY) != 0;
            Width = VideoSurfaceDescription->dwWidth;
            Height = VideoSurfaceDescription->dwHeight;
        }
    }
}
