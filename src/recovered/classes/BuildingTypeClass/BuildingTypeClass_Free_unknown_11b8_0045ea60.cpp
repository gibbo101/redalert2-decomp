// void BuildingTypeClass::Free_unknown_11b8() (0x0045EA60)
// Frees the image when unknown_11bc is set.
#include "shared/building_type.hpp"
// @ref ??3@YAXPAX@Z=00781d3b

void BuildingTypeClass::Free_unknown_11b8()
{
    if (unknown_11bc && unknown_11b8) {
        operator delete(unknown_11b8);
        unknown_11b8 = 0;
        unknown_11bc = false;
    }
}
