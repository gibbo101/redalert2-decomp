// DynamicVectorClass<EventClass *>::Resize (0x0061B590; DynamicVectorClass<EventClass *> vtable 0x007a81dc slot 2).
// Layout and behaviour: shared/vector_class.hpp.
#define VECTOR_IMPLEMENT_DYNAMIC_RESIZE
#include "shared/vector_class.hpp"

class EventClass;

template class DynamicVectorClass<EventClass *>;
