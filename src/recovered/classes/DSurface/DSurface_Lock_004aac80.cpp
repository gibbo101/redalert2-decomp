// void *DSurface::Lock(Point2D point) (0x004AAC80, slot 23)
// Locks the DirectDraw surface on the first nested lock (refreshing the
// description, pixel size and memory pointer) and returns the address of
// pixel point; null when restoration fails or is disabled, or for a negative coordinate.
#include "shared/crt_memory.hpp"
#include "shared/dsurface.hpp"
// @ref ?unknown_flag_851cb0@@3_NA=00851cb0
// @ref ?unknown_flag_a40d28@@3_NA=00a40d28

// Restores a lost DirectDraw surface and re-establishes an outstanding lock:
// the body of Restore_Check (0x004AAF00), which Lock, Unlock and Fill_Rect
// expand inline while Restore_Check itself is an ordinary function.
inline bool DSurface::Restore_Lost_Surface()
{
    if (unknown_flag_851cb0 || unknown_flag_a40d28) {
        if (VideoSurfacePtr != 0 && VideoSurfacePtr->IsLost() == DDERR_SURFACELOST) {
            if (VideoSurfacePtr->Restore() != DD_OK || VideoSurfacePtr->IsLost() != DD_OK) {
                return false;
            }
            if (LockLevel > 0) {
                int oldlocklevel = LockLevel;
                LockLevel = 0;
                Lock();
                LockLevel++;
                Unlock();
                LockLevel = oldlocklevel;
            }
        }
        return true;
    }
    return false;
}

void *DSurface::Lock(Point2D point)
{
    if (!Restore_Lost_Surface()) {
        return 0;
    }
    if (point.X < 0 || point.Y < 0) {
        return 0;
    }
    if (LockLevel == 0) {
        DDSURFACEDESC desc;
        memset(&desc, 0, sizeof(desc));
        desc.dwSize = sizeof(desc);
        if (VideoSurfacePtr->Lock(0, &desc, DDLOCK_WAIT, 0) != DD_OK) {
            return 0;
        }
        *VideoSurfaceDescription = desc;
        BytesPerPixel = (VideoSurfaceDescription->ddpfPixelFormat.dwRGBBitCount + 7) / 8;
        IsVideoRam = (VideoSurfaceDescription->ddsCaps.dwCaps & DDSCAPS_VIDEOMEMORY) != 0;
        BufferPtr = VideoSurfaceDescription->lpSurface;
    }
    XSurface::Lock();
    return (char *)BufferPtr + point.Y * Stride() + point.X * Bytes_Per_Pixel();
}
