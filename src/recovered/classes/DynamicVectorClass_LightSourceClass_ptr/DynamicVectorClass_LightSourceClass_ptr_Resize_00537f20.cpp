// DynamicVectorClass<LightSourceClass *>::Resize (0x00537F20; DynamicVectorClass<LightSourceClass *> vtable 0x007a54b4 slot 2).
// Layout and behaviour: shared/vector_class.hpp.
#define VECTOR_IMPLEMENT_DYNAMIC_RESIZE
#include "shared/vector_class.hpp"

class LightSourceClass;

template class DynamicVectorClass<LightSourceClass *>;
