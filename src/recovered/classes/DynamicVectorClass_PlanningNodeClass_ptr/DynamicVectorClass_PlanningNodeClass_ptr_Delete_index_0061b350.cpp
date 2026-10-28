// DynamicVectorClass<PlanningNodeClass *>::Delete(int index) (0x0061B350).
// Instantiated for the planning code (0x00616xxx calls it out of line).
// Layout and behaviour: shared/vector_class.hpp.
#define VECTOR_IMPLEMENT_DYNAMIC_DELETE_INDEX
#include "shared/vector_class.hpp"

class PlanningNodeClass;

template class DynamicVectorClass<PlanningNodeClass *>;
