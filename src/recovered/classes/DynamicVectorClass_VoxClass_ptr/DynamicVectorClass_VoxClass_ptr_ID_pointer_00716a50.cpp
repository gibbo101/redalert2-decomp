// DynamicVectorClass<VoxClass *>::ID_pointer (0x00716A50; DynamicVectorClass<VoxClass *> vtable 0x007ae9e4 slot 5).
// Layout and behaviour: shared/vector_class.hpp.
#define VECTOR_IMPLEMENT_DYNAMIC_ID_POINTER
#include "shared/vector_class.hpp"

class VoxClass;

template class DynamicVectorClass<VoxClass *>;
