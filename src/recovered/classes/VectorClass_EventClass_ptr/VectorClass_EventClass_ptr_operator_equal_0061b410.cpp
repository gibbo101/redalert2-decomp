// VectorClass<EventClass *>::operator equal (0x0061B410; VectorClass<EventClass *> vtable 0x007a81fc slot 1).
// Layout and behaviour: shared/vector_class.hpp.
#define VECTOR_IMPLEMENT_VECTOR_EQUAL
#include "shared/vector_class.hpp"

class EventClass;

template class VectorClass<EventClass *>;
