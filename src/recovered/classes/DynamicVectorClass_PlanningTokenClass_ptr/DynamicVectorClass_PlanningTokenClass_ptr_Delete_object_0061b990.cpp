// bool DynamicVectorClass<PlanningTokenClass *>::Delete(PlanningTokenClass * const &object) (0x0061B990).
// Instantiated from shared/vector_class.hpp; called at 0x00613EA5 for the PlanningTokenClass list (0x00A76738).
// Expands Delete(int); this unit's own copy of Delete(int) is the one at 0x0061BE00.
// @ref ?Delete@?$DynamicVectorClass@PAVPlanningTokenClass@@@@QAE_NH@Z=0061be00
#define VECTOR_IMPLEMENT_DYNAMIC_DELETE_OBJECT
#define VECTOR_IMPLEMENT_DYNAMIC_DELETE_INDEX
#include "shared/vector_class.hpp"

class PlanningTokenClass;

template class DynamicVectorClass<PlanningTokenClass *>;
