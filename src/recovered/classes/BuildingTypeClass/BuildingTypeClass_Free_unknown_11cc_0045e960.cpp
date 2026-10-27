// void BuildingTypeClass::Free_unknown_11cc() (0x0045E960)
// Frees the image when unknown_11d0 is set.
#include "shared/building_type.hpp"
// @ref ??3@YAXPAX@Z=00781d3b

void BuildingTypeClass::Free_unknown_11cc()
{
    if (unknown_11d0 && unknown_11cc) {
        operator delete(unknown_11cc);
        unknown_11cc = 0;
        unknown_11d0 = false;
    }
}
