// DynamicVectorClass<TEventClass *>::Resize (0x006E70A0; DynamicVectorClass<TEventClass *> vtable 0x007ad694 slot 2).
// Layout and behaviour: shared/vector_class.hpp.
#define VECTOR_IMPLEMENT_DYNAMIC_RESIZE
#include "shared/vector_class.hpp"

class TEventClass;

template class DynamicVectorClass<TEventClass *>;
