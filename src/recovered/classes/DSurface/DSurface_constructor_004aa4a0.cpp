// DSurface::DSurface(int width, int height, bool system_memory) (0x004AA4A0)
// Creates an offscreen DirectDraw surface of the given size (system memory
// when asked; a plain offscreen 3D-device surface when unknown_flag_852fd7
// is set) and reads back its
// description, pixel size and memory placement.
// Unresolved: the meaning of the global flag; CreateSurface's result is not
// checked (only the returned pointer).
#include "shared/crt_memory.hpp"
#include "shared/dsurface.hpp"
// @ref ?DirectDrawObject@@3PAUIDirectDraw@@A=008523cc
// @ref ?unknown_flag_852fd7@@3_NA=00852fd7

DSurface::DSurface(int width, int height, bool system_memory)
    : XSurface(width, height),
      BytesPerPixel(0),
      BufferPtr(0),
      IsPrimary(false),
      IsVideoRam(false),
      VideoSurfacePtr(0),
      VideoSurfaceDescription(0)
{
    VideoSurfaceDescription = new DDSURFACEDESC;
    if (VideoSurfaceDescription != 0) {
        memset(VideoSurfaceDescription, 0, sizeof(DDSURFACEDESC));
        VideoSurfaceDescription->dwSize = sizeof(DDSURFACEDESC);
        VideoSurfaceDescription->dwFlags = DDSD_CAPS | DDSD_HEIGHT | DDSD_WIDTH;
        VideoSurfaceDescription->dwWidth = width;
        VideoSurfaceDescription->dwHeight = height;
        if (system_memory == true) {
            VideoSurfaceDescription->ddsCaps.dwCaps |= DDSCAPS_SYSTEMMEMORY;
        }
        if (unknown_flag_852fd7) {
            VideoSurfaceDescription->ddsCaps.dwCaps = DDSCAPS_3DDEVICE | DDSCAPS_OFFSCREENPLAIN;
        }
        DirectDrawObject->CreateSurface(VideoSurfaceDescription, &VideoSurfacePtr, 0);
        if (VideoSurfacePtr != 0) {
            memset(VideoSurfaceDescription, 0, sizeof(DDSURFACEDESC));
            VideoSurfaceDescription->dwSize = sizeof(DDSURFACEDESC);
            VideoSurfacePtr->GetSurfaceDesc(VideoSurfaceDescription);
            BytesPerPixel = (VideoSurfaceDescription->ddpfPixelFormat.dwRGBBitCount + 7) / 8;
            IsVideoRam = (VideoSurfaceDescription->ddsCaps.dwCaps & DDSCAPS_VIDEOMEMORY) != 0;
        }
    }
}
