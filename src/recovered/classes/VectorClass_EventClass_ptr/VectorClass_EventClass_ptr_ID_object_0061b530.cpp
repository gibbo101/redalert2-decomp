// VectorClass<EventClass *>::ID_object (0x0061B530; VectorClass<EventClass *> vtable 0x007a81fc slot 4).
// Layout and behaviour: shared/vector_class.hpp.
#define VECTOR_IMPLEMENT_VECTOR_ID_OBJECT
#include "shared/vector_class.hpp"

class EventClass;

template class VectorClass<EventClass *>;
