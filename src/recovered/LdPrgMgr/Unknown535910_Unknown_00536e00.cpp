// void Unknown535910::Unknown_00536E00(Surface *surface) -- 0x00536E00
// Copies the surface at +0x5C (when made) onto another surface.
#include "shared/unknown_globals.hpp"
#include "shared/surface.hpp"

void Unknown535910::Unknown_00536E00(Surface *surface)
{
    if (unknown_5c != 0) {
        surface->Copy_From(*unknown_5c, false, true);
    }
}
