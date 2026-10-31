// DynamicVectorClass<PlanningMemberClass *>::Delete(PlanningMemberClass * const &) (0x0061AD90).
// Layout and behaviour: shared/vector_class.hpp. The planning unit's out-of-line copy
// (a node's Members list; called from 0x00612D20, 0x00613330 and 0x00615480), with the
// unit's Delete(int) 0x0061BD30 (the next row; called after Members.ID at 0x00612F78 and three more).
#define VECTOR_IMPLEMENT_DYNAMIC_DELETE_OBJECT
#define VECTOR_IMPLEMENT_DYNAMIC_DELETE_INDEX
#include "shared/vector_class.hpp"

class PlanningMemberClass;

template class DynamicVectorClass<PlanningMemberClass *>;
