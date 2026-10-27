// DynamicVectorClass<AnimClass *>::Resize (0x00520E20; DynamicVectorClass<AnimClass *> vtable 0x007a4554 slot 2).
// Layout and behaviour: shared/vector_class.hpp.
#define VECTOR_IMPLEMENT_DYNAMIC_RESIZE
#include "shared/vector_class.hpp"

class AnimClass;

template class DynamicVectorClass<AnimClass *>;
