// DynamicVectorClass<DiscreteDistributionClass<BuildingTypeClass>::DistributionObject<BuildingTypeClass *>>::Resize (0x004F82C0;
// vtable 0x007A2FCC slot 2, named by its RTTI).
// Layout and behaviour: shared/vector_class.hpp, shared/discrete_distribution.hpp.
// @ref ??_I@YGXPAXIHP6EX0@Z@Z=0040af00
// @ref ??1?$DistributionObject@PAVBuildingTypeClass@@@?$DiscreteDistributionClass@VBuildingTypeClass@@@@QAE@XZ=004f83e0
// @ref ??_E?$DistributionObject@PAVBuildingTypeClass@@@?$DiscreteDistributionClass@VBuildingTypeClass@@@@QAEPAXI@Z=004f8860
#define VECTOR_IMPLEMENT_DYNAMIC_RESIZE
#include "shared/discrete_distribution.hpp"

class BuildingTypeClass;

template class DynamicVectorClass<DiscreteDistributionClass<BuildingTypeClass>::DistributionObject<BuildingTypeClass *> >;
