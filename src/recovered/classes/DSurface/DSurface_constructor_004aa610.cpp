// DSurface::DSurface() (0x004AA610)
// An empty surface with a cleared description (no DirectDraw surface yet).
// Unresolved: the allocation is used without a null check (as the original).
#include "shared/crt_memory.hpp"
#include "shared/dsurface.hpp"

DSurface::DSurface()
    : BytesPerPixel(0),
      BufferPtr(0),
      IsPrimary(false),
      IsVideoRam(false),
      VideoSurfacePtr(0)
{
    VideoSurfaceDescription = new DDSURFACEDESC;
    memset(VideoSurfaceDescription, 0, sizeof(DDSURFACEDESC));
    VideoSurfaceDescription->dwSize = sizeof(DDSURFACEDESC);
}
