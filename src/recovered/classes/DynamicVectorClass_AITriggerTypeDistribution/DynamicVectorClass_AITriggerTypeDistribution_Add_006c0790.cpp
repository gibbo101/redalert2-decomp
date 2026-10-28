// DynamicVectorClass<DiscreteDistributionClass<AITriggerTypeClass>::DistributionObject<AITriggerTypeClass *>>::Add (0x006C0790).
// Layout and behaviour: shared/vector_class.hpp, shared/discrete_distribution.hpp.
// Called at 0x006BEF51 while the AI trigger choices are weighted.
#define VECTOR_IMPLEMENT_DYNAMIC_ADD
#define VECTOR_IMPLEMENT_VECTOR_ACCESSORS
#include "shared/discrete_distribution.hpp"

class AITriggerTypeClass;

template class DynamicVectorClass<DiscreteDistributionClass<AITriggerTypeClass>::DistributionObject<AITriggerTypeClass *> >;
