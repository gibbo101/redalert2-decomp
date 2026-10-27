// bool XSurface::Unknown_Slot14(int, int, int, int, int, int, int) (0x00773ED0, slot 14)
// Not implemented by the generic surface: returns false.
// Unresolved: purpose and argument types (only the 7 stack arguments are
// evidenced, by ret 0x1c); DSurface overrides some of these slots.
#include "shared/surface.hpp"

bool XSurface::Unknown_Slot14(int, int, int, int, int, int, int)
{
    return false;
}
