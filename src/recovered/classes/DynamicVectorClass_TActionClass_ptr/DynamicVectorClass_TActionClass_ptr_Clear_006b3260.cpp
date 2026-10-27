// DynamicVectorClass<TActionClass *>::Clear (0x006B3260; DynamicVectorClass<TActionClass *> vtable 0x007ac5f0 slot 3).
// Layout and behaviour: shared/vector_class.hpp.
#define VECTOR_IMPLEMENT_DYNAMIC_CLEAR
#include "shared/vector_class.hpp"

class TActionClass;

template class DynamicVectorClass<TActionClass *>;
