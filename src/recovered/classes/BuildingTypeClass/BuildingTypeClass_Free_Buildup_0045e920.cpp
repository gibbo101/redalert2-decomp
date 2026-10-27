// void BuildingTypeClass::Free_Buildup() (0x0045E920)
// Frees the image when FreeBuildup is set.
#include "shared/building_type.hpp"
// @ref ??3@YAXPAX@Z=00781d3b

void BuildingTypeClass::Free_Buildup()
{
    if (FreeBuildup && BuildupData) {
        operator delete(BuildupData);
        BuildupData = 0;
        BuildupDataAllocated = false;
    }
}
