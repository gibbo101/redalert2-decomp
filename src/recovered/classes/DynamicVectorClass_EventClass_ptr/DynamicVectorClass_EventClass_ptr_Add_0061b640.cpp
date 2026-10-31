// DynamicVectorClass<EventClass *>::Add (0x0061B640).
// Layout and behaviour: shared/vector_class.hpp. The out-of-line copy of the planning unit
// (0x00614A6A appends to PlanningLists::unknown_list_00a76648).
#define VECTOR_IMPLEMENT_DYNAMIC_ADD
#define VECTOR_IMPLEMENT_VECTOR_ACCESSORS
#include "shared/vector_class.hpp"

class EventClass;

template class DynamicVectorClass<EventClass *>;
