// DynamicVectorClass<PlanningNodeClass *>::Delete(PlanningNodeClass * const &object) (0x0061B390).
// Expands Delete(int); this unit's own copy of Delete(int) is the one at 0x0061B350.
// Layout and behaviour: shared/vector_class.hpp.
// @ref ?Delete@?$DynamicVectorClass@PAVPlanningNodeClass@@@@QAE_NH@Z=0061b350
#define VECTOR_IMPLEMENT_DYNAMIC_DELETE_OBJECT
#define VECTOR_IMPLEMENT_DYNAMIC_DELETE_INDEX
#include "shared/vector_class.hpp"

class PlanningNodeClass;

template class DynamicVectorClass<PlanningNodeClass *>;
