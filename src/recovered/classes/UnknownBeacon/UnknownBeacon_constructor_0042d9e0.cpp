// UnknownBeacon::UnknownBeacon (0x0042D9E0): the default position (the unit's unknown_geometry_l),
// placed and blinking flags clear, an empty text. Out of line here; 0x0042E370 expands it.
#include "shared/beacon.hpp"
#include "shared/unknown_geometry.hpp"

UnknownBeacon::UnknownBeacon()
{
    unknown_coord = unknown_geometry_l;
    unknown_flags &= 0xfc;
    for (int index = 0; index < 128; index++) {
        unknown_text.chars[index] = 0;
    }
}
