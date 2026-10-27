// VectorClass<EventClass *>::ID_pointer (0x0061B570; VectorClass<EventClass *> vtable 0x007a81fc slot 5).
// Layout and behaviour: shared/vector_class.hpp.
#define VECTOR_IMPLEMENT_VECTOR_ID_POINTER
#include "shared/vector_class.hpp"

class EventClass;

template class VectorClass<EventClass *>;
