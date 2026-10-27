// DynamicVectorClass<AnimClass *>::ID_pointer (0x004D50A0; DynamicVectorClass<AnimClass *> vtable 0x007a2464 slot 5).
// Layout and behaviour: shared/vector_class.hpp.
#define VECTOR_IMPLEMENT_DYNAMIC_ID_POINTER
#include "shared/vector_class.hpp"

class AnimClass;

template class DynamicVectorClass<AnimClass *>;
