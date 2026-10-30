// @ref ??_7?$VectorClass@V?$DistributionObject@PAVBuildingTypeClass@@@?$DiscreteDistributionClass@VBuildingTypeClass@@@@@@6B@=007a2fac
// @ref ??_E?$VectorClass@V?$DistributionObject@PAVBuildingTypeClass@@@?$DiscreteDistributionClass@VBuildingTypeClass@@@@@@UAEPAXI@Z=004f8800
// @ref ??8?$VectorClass@V?$DistributionObject@PAVBuildingTypeClass@@@?$DiscreteDistributionClass@VBuildingTypeClass@@@@@@UBE_NABV0@@Z=004f80a0
// @ref ?Resize@?$VectorClass@V?$DistributionObject@PAVBuildingTypeClass@@@?$DiscreteDistributionClass@VBuildingTypeClass@@@@@@UAE_NHPBV?$DistributionObject@PAVBuildingTypeClass@@@?$DiscreteDistributionClass@VBuildingTypeClass@@@@@Z=004f8100
// @ref ?Clear@?$VectorClass@V?$DistributionObject@PAVBuildingTypeClass@@@?$DiscreteDistributionClass@VBuildingTypeClass@@@@@@UAEXXZ=004f8210
// @ref ?ID@?$VectorClass@V?$DistributionObject@PAVBuildingTypeClass@@@?$DiscreteDistributionClass@VBuildingTypeClass@@@@@@UAEHABV?$DistributionObject@PAVBuildingTypeClass@@@?$DiscreteDistributionClass@VBuildingTypeClass@@@@@Z=004f8250
// @ref ?ID@?$VectorClass@V?$DistributionObject@PAVBuildingTypeClass@@@?$DiscreteDistributionClass@VBuildingTypeClass@@@@@@UAEHPBV?$DistributionObject@PAVBuildingTypeClass@@@?$DiscreteDistributionClass@VBuildingTypeClass@@@@@Z=004f82a0
// @ref ?Fetch@?$VectorClass@V?$DistributionObject@PAVBuildingTypeClass@@@?$DiscreteDistributionClass@VBuildingTypeClass@@@@@@UBE?AV?$DistributionObject@PAVBuildingTypeClass@@@?$DiscreteDistributionClass@VBuildingTypeClass@@@@H@Z=004f6ec0
// Weighted-building candidate storage; original004F8D70, RTTI007A2FAC.
#define VECTOR_IMPLEMENT_VECTOR_DESTRUCTOR
#include "shared/discrete_distribution.hpp"
class BuildingTypeClass;
typedef DiscreteDistributionClass<BuildingTypeClass>::DistributionObject<BuildingTypeClass *> HouseBuildingDistributionElement;
template <> VectorClass<HouseBuildingDistributionElement>::VectorClass(unsigned size,HouseBuildingDistributionElement const *array)
    : Vector(0),VectorMax(size),IsValid(true),IsAllocated(false)
{
    if (size) {
        if (array) Vector=new ((void *)array) HouseBuildingDistributionElement[size];
        else {
            Vector=new HouseBuildingDistributionElement[size];
            IsAllocated=true;
        }
    }
}
