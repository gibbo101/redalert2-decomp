// DynamicVectorClass<TemporalClass *>::Clear (0x006E2AB0; DynamicVectorClass<TemporalClass *> vtable 0x007ad2b4 slot 3).
// Layout and behaviour: shared/vector_class.hpp.
#define VECTOR_IMPLEMENT_DYNAMIC_CLEAR
#include "shared/vector_class.hpp"

class TemporalClass;

template class DynamicVectorClass<TemporalClass *>;
