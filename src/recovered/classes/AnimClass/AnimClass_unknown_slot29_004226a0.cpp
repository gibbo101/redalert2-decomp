// int AnimClass::unknown_slot29() const (0x004226A0)
// The layer: 2 when attached to an object, else the type's Layer (3 without
// a type).
#include "shared/anim.hpp"

int AnimClass::unknown_slot29() const
{
    if (unknown_b4 != 0) {
        return 2;
    }
    if (Class != 0) {
        return Class->Layer;
    }
    return 3;
}
