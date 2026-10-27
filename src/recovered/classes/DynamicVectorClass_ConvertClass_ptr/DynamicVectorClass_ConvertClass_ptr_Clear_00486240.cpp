// DynamicVectorClass<ConvertClass *>::Clear (0x00486240; DynamicVectorClass<ConvertClass *> vtable 0x0079df30 slot 3).
// Layout and behaviour: shared/vector_class.hpp.
#define VECTOR_IMPLEMENT_DYNAMIC_CLEAR
#include "shared/vector_class.hpp"

class ConvertClass;

template class DynamicVectorClass<ConvertClass *>;
