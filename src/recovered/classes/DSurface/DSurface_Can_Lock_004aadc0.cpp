// bool DSurface::Can_Lock(int x, int y) (0x004AADC0, slot 25)
// When not locked, tries a DirectDraw lock and releases it at once; false
// when the lock fails. x and y are ignored.
#include "shared/crt_memory.hpp"
#include "shared/dsurface.hpp"

bool DSurface::Can_Lock(int x, int y)
{
    if (LockLevel == 0) {
        DDSURFACEDESC desc;
        memset(&desc, 0, sizeof(desc));
        desc.dwSize = sizeof(desc);
        if (VideoSurfacePtr->Lock(0, &desc, 0, 0) != DD_OK) {
            return false;
        }
        VideoSurfacePtr->Unlock(desc.lpSurface);
    }
    return true;
}
