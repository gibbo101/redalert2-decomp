// DynamicVectorClass<DiscreteDistributionClass<CellClass>::DistributionObject<CellClass *>>::Add (0x004ce950; vtable 0x007a17fc).
// Layout and behaviour: shared/vector_class.hpp, shared/discrete_distribution.hpp.
#define VECTOR_IMPLEMENT_DYNAMIC_ADD
#define VECTOR_IMPLEMENT_VECTOR_ACCESSORS
#include "shared/discrete_distribution.hpp"

class CellClass;

template class DynamicVectorClass<DiscreteDistributionClass<CellClass>::DistributionObject<CellClass *> >;
