// DynamicVectorClass<VoxClass *>::Clear (0x00716A20; DynamicVectorClass<VoxClass *> vtable 0x007ae9e4 slot 3).
// Layout and behaviour: shared/vector_class.hpp.
#define VECTOR_IMPLEMENT_DYNAMIC_CLEAR
#include "shared/vector_class.hpp"

class VoxClass;

template class DynamicVectorClass<VoxClass *>;
