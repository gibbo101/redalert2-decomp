// VectorClass<EventClass *>::Fetch (0x0061AA90; VectorClass<EventClass *> vtable 0x007a81fc slot 6).
// Layout and behaviour: shared/vector_class.hpp.
#define VECTOR_IMPLEMENT_VECTOR_FETCH
#include "shared/vector_class.hpp"

class EventClass;

template class VectorClass<EventClass *>;
