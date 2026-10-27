// VectorClass<EventClass *>::Clear (0x0061B500; VectorClass<EventClass *> vtable 0x007a81fc slot 3).
// Layout and behaviour: shared/vector_class.hpp.
#define VECTOR_IMPLEMENT_VECTOR_CLEAR
#include "shared/vector_class.hpp"

class EventClass;

template class VectorClass<EventClass *>;
