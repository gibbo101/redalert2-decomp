// DynamicVectorClass<EgoClass *>::ID_object (0x004B45C0; DynamicVectorClass<EgoClass *> vtable 0x007a0cec slot 4).
// Layout and behaviour: shared/vector_class.hpp.
#define VECTOR_IMPLEMENT_DYNAMIC_ID_OBJECT
#include "shared/vector_class.hpp"

class EgoClass;

template class DynamicVectorClass<EgoClass *>;
