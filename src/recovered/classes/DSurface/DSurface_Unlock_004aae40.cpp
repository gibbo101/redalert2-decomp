// bool DSurface::Unlock() (0x004AAE40, slot 24)
// Drops one lock; the last one unlocks the DirectDraw surface. Restoration
// is attempted first but its result is ignored.
#include "shared/dsurface.hpp"

bool DSurface::Unlock()
{
    Restore_Lost_Surface();
    if (LockLevel > 0) {
        LockLevel--;
        if (LockLevel == 0) {
            VideoSurfacePtr->Unlock(BufferPtr);
            BufferPtr = 0;
        }
        return true;
    }
    return false;
}
