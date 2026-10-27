// void BuildingTypeClass::Free_unknown_11a8() (0x0045E9E0)
// Frees the image when unknown_11ac is set.
#include "shared/building_type.hpp"
// @ref ??3@YAXPAX@Z=00781d3b

void BuildingTypeClass::Free_unknown_11a8()
{
    if (unknown_11ac && unknown_11a8) {
        operator delete(unknown_11a8);
        unknown_11a8 = 0;
        unknown_11ac = false;
    }
}
