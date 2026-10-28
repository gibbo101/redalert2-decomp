// bool DynamicVectorClass<TechnoClass *>::Delete(TechnoClass * const &object) (0x0061B6C0).
// Instantiated from shared/vector_class.hpp; called by the planning code (0x00612E46 and three more) for the PlanningLists TechnoClass list (0x00A76700).
// Expands Delete(int); this unit's own copy of Delete(int) is the one at 0x0061BDC0.
// @ref ?Delete@?$DynamicVectorClass@PAVTechnoClass@@@@QAE_NH@Z=0061bdc0
#define VECTOR_IMPLEMENT_DYNAMIC_DELETE_OBJECT
#define VECTOR_IMPLEMENT_DYNAMIC_DELETE_INDEX
#include "shared/vector_class.hpp"

class TechnoClass;

template class DynamicVectorClass<TechnoClass *>;
