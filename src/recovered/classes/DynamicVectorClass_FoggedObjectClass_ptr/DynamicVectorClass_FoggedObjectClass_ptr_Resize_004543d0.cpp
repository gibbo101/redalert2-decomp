// DynamicVectorClass<FoggedObjectClass *>::Resize (0x004543D0; DynamicVectorClass<FoggedObjectClass *> vtable 0x0079d17c slot 2).
// Layout and behaviour: shared/vector_class.hpp.
#define VECTOR_IMPLEMENT_DYNAMIC_RESIZE
#include "shared/vector_class.hpp"

class FoggedObjectClass;

template class DynamicVectorClass<FoggedObjectClass *>;
