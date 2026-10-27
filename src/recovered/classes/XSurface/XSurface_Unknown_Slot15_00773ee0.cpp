// bool XSurface::Unknown_Slot15(int, int, int, int, int, int, int, int, int, int, int) (0x00773EE0, slot 15)
// Not implemented by the generic surface: returns false.
// Unresolved: purpose and argument types (only the 11 stack arguments are
// evidenced, by ret 0x2c); DSurface overrides some of these slots.
#include "shared/surface.hpp"

bool XSurface::Unknown_Slot15(int, int, int, int, int, int, int, int, int, int, int)
{
    return false;
}
