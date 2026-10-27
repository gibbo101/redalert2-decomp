// DynamicVectorClass<EventClass *>::ID_pointer (0x0061AA70; DynamicVectorClass<EventClass *> vtable 0x007a81dc slot 5).
// Layout and behaviour: shared/vector_class.hpp.
#define VECTOR_IMPLEMENT_DYNAMIC_ID_POINTER
#include "shared/vector_class.hpp"

class EventClass;

template class DynamicVectorClass<EventClass *>;
