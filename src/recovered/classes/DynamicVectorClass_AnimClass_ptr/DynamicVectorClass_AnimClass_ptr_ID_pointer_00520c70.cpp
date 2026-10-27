// DynamicVectorClass<AnimClass *>::ID_pointer (0x00520C70; DynamicVectorClass<AnimClass *> vtable 0x007a4554 slot 5).
// Layout and behaviour: shared/vector_class.hpp.
#define VECTOR_IMPLEMENT_DYNAMIC_ID_POINTER
#include "shared/vector_class.hpp"

class AnimClass;

template class DynamicVectorClass<AnimClass *>;
