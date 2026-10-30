// @ref ??_G?$VectorClass@PBVBuildingTypeClass@@@@UAEPAXI@Z=004f8490
// @ref ??_E?$VectorClass@PBVBuildingTypeClass@@@@UAEPAXI@Z=004f8490
// @ref ??8?$VectorClass@PBVBuildingTypeClass@@@@UBE_NABV0@@Z=004f7010
// @ref ?Resize@?$VectorClass@PBVBuildingTypeClass@@@@UAE_NHPBQBVBuildingTypeClass@@@Z=004f7050
// @ref ?Clear@?$VectorClass@PBVBuildingTypeClass@@@@UAEXXZ=004f7100
// @ref ?ID@?$VectorClass@PBVBuildingTypeClass@@@@UAEHABQBVBuildingTypeClass@@@Z=004f7130
// @ref ?ID@?$VectorClass@PBVBuildingTypeClass@@@@UAEHPBQBVBuildingTypeClass@@@Z=004f7170
// @ref ?Fetch@?$VectorClass@PBVBuildingTypeClass@@@@UBEPBVBuildingTypeClass@@H@Z=004f6c50
// Real original RTTI: VectorClass<BuildingTypeClass const *> at007A2F08.
// @ref ??_7?$VectorClass@PBVBuildingTypeClass@@@@6B@=007a2f08
class BuildingTypeClass;
#define VECTOR_IMPLEMENT_VECTOR_DESTRUCTOR
#include "shared/vector_class.hpp"
template <> VectorClass<BuildingTypeClass const *>::VectorClass(unsigned size, BuildingTypeClass const * const *array)
    : Vector(0), VectorMax(size), IsValid(true), IsAllocated(false)
{
    if (size) {
        if (array) Vector = new ((void *)array) BuildingTypeClass const *[size];
        else {
            Vector = new BuildingTypeClass const *[size];
            IsAllocated = true;
        }
    }
}
