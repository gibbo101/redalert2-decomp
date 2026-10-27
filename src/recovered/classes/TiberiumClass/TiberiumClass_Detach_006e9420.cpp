// TiberiumClass::Detach (0x006E9420)
#include "shared/tiberium.hpp"

void TiberiumClass::Detach(AbstractClass *target, bool all)
{
    for (int index = unknown_c4.Count() - 1; index >= 0; index--) {
        if (unknown_c4[index] == (AnimTypeClass *)target) {
            unknown_c4.Delete(index);
        }
    }
    if (Image == (OverlayTypeClass *)target) {
        Image = 0;
    }
}
