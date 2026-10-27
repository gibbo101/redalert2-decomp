// DynamicVectorClass<TEventClass *>::Clear (0x006E6EC0; DynamicVectorClass<TEventClass *> vtable 0x007ad694 slot 3).
// Layout and behaviour: shared/vector_class.hpp.
#define VECTOR_IMPLEMENT_DYNAMIC_CLEAR
#include "shared/vector_class.hpp"

class TEventClass;

template class DynamicVectorClass<TEventClass *>;
