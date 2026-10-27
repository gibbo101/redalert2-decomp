// DynamicVectorClass<AnimClass *>::ID_object (0x00520ED0; DynamicVectorClass<AnimClass *> vtable 0x007a4554 slot 4).
// Layout and behaviour: shared/vector_class.hpp.
#define VECTOR_IMPLEMENT_DYNAMIC_ID_OBJECT
#include "shared/vector_class.hpp"

class AnimClass;

template class DynamicVectorClass<AnimClass *>;
