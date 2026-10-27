// DynamicVectorClass<TEventClass *>::ID_pointer (0x006E6EF0; DynamicVectorClass<TEventClass *> vtable 0x007ad694 slot 5).
// Layout and behaviour: shared/vector_class.hpp.
#define VECTOR_IMPLEMENT_DYNAMIC_ID_POINTER
#include "shared/vector_class.hpp"

class TEventClass;

template class DynamicVectorClass<TEventClass *>;
