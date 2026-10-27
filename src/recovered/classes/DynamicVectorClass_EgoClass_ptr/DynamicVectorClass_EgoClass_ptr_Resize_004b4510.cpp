// DynamicVectorClass<EgoClass *>::Resize (0x004B4510; DynamicVectorClass<EgoClass *> vtable 0x007a0cec slot 2).
// Layout and behaviour: shared/vector_class.hpp.
#define VECTOR_IMPLEMENT_DYNAMIC_RESIZE
#include "shared/vector_class.hpp"

class EgoClass;

template class DynamicVectorClass<EgoClass *>;
