// TiberiumClass::Detach (0x006E9420)
#include "shared/tiberium.hpp"

void TiberiumClass::Detach(AbstractClass *target, bool all)
{
    for (int index = Debris.Count() - 1; index >= 0; index--) {
        if (Debris[index] == (AnimTypeClass *)target) {
            Debris.Delete(index);
        }
    }
    if (Image == (OverlayTypeClass *)target) {
        Image = 0;
    }
}
