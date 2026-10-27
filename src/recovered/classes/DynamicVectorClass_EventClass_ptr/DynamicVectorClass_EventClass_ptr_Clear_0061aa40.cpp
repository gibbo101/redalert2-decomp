// DynamicVectorClass<EventClass *>::Clear (0x0061AA40; DynamicVectorClass<EventClass *> vtable 0x007a81dc slot 3).
// Layout and behaviour: shared/vector_class.hpp.
#define VECTOR_IMPLEMENT_DYNAMIC_CLEAR
#include "shared/vector_class.hpp"

class EventClass;

template class DynamicVectorClass<EventClass *>;
