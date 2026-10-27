// void IsometricTileTypeClass::Detach(AbstractClass *target, bool all) (0x0052E310, slot 10)
// Forgets unknown_28c and the animation type (unknown_298) when they are the target.
// Only the list accessors expand here: the colour table constructor stays a call.
#define VECTOR_IMPLEMENT_VECTOR_ACCESSORS
#define VECTOR_IMPLEMENT_DYNAMIC_ACCESSORS
#include "shared/vector_class.hpp"
#include "shared/isometric_tile_type.hpp"
#include "shared/anim_type.hpp"
// @ref ?AnimTypes@@3V?$TypeList@PAVAnimTypeClass@@@@A=008661e0

void IsometricTileTypeClass::Detach(AbstractClass *target, bool all)
{
    if (unknown_28c == target) {
        unknown_28c = 0;
    }
    if (unknown_298 != -1 && AnimTypes[unknown_298] == target) {
        unknown_298 = -1;
    }
}
