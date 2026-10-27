// DynamicVectorClass<EgoClass *>::Clear (0x004B4330; DynamicVectorClass<EgoClass *> vtable 0x007a0cec slot 3).
// Layout and behaviour: shared/vector_class.hpp.
#define VECTOR_IMPLEMENT_DYNAMIC_CLEAR
#include "shared/vector_class.hpp"

class EgoClass;

template class DynamicVectorClass<EgoClass *>;
