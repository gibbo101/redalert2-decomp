// DynamicVectorClass<DiscreteDistributionClass<BuildingTypeClass>::DistributionObject<BuildingTypeClass *>>::Add (0x004F83F0).
// Layout and behaviour: shared/vector_class.hpp, shared/discrete_distribution.hpp.
#define VECTOR_IMPLEMENT_DYNAMIC_ADD
#define VECTOR_IMPLEMENT_VECTOR_ACCESSORS
#include "shared/discrete_distribution.hpp"

class BuildingTypeClass;

template class DynamicVectorClass<DiscreteDistributionClass<BuildingTypeClass>::DistributionObject<BuildingTypeClass *> >;
