// bool DSurface::Restore_Check() (0x004AAF00)
// Restores a lost DirectDraw surface and, when a lock is outstanding, locks
// it again to refresh the memory pointer. False when restoration is
// disabled (both flags clear) or Restore fails. The body is the inline
// Restore_Lost_Surface (defined with Lock), which Lock, Unlock and
// Fill_Rect expand. Unresolved: the meaning of the two enabling flags.
#include "shared/dsurface.hpp"

bool DSurface::Restore_Check()
{
    return Restore_Lost_Surface();
}
