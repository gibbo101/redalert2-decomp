// bool XSurface::Unknown_Slot7(int, int, int) (0x007746B0, slot 7)
// Not implemented by the generic surface: returns false.
// Unresolved: purpose and argument types (3 stack arguments, ret 0xc);
// DSurface overrides it (0x004AB730).
#include "shared/surface.hpp"

bool XSurface::Unknown_Slot7(int, int, int)
{
    return false;
}
