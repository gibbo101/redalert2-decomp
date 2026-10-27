// DynamicVectorClass<AnimClass *>::Clear (0x004D5070; DynamicVectorClass<AnimClass *> vtable 0x007a2464 slot 3).
// Layout and behaviour: shared/vector_class.hpp.
#define VECTOR_IMPLEMENT_DYNAMIC_CLEAR
#include "shared/vector_class.hpp"

class AnimClass;

template class DynamicVectorClass<AnimClass *>;
