// DynamicVectorClass<EgoClass *>::ID_pointer (0x004B4360; DynamicVectorClass<EgoClass *> vtable 0x007a0cec slot 5).
// Layout and behaviour: shared/vector_class.hpp.
#define VECTOR_IMPLEMENT_DYNAMIC_ID_POINTER
#include "shared/vector_class.hpp"

class EgoClass;

template class DynamicVectorClass<EgoClass *>;
