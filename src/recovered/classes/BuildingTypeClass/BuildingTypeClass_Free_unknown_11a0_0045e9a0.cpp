// void BuildingTypeClass::Free_unknown_11a0() (0x0045E9A0)
// Frees the image when unknown_11a4 is set.
#include "shared/building_type.hpp"
// @ref ??3@YAXPAX@Z=00781d3b

void BuildingTypeClass::Free_unknown_11a0()
{
    if (unknown_11a4 && unknown_11a0) {
        operator delete(unknown_11a0);
        unknown_11a0 = 0;
        unknown_11a4 = false;
    }
}
