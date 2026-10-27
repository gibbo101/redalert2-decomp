// void BuildingTypeClass::Free_unknown_11b0() (0x0045EA20)
// Frees the image when unknown_11b4 is set.
#include "shared/building_type.hpp"
// @ref ??3@YAXPAX@Z=00781d3b

void BuildingTypeClass::Free_unknown_11b0()
{
    if (unknown_11b4 && unknown_11b0) {
        operator delete(unknown_11b0);
        unknown_11b0 = 0;
        unknown_11b4 = false;
    }
}
