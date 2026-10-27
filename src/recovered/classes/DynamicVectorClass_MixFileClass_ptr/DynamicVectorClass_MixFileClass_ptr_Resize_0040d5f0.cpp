// DynamicVectorClass<MixFileClass *>::Resize (0x0040D5F0; DynamicVectorClass<MixFileClass *> vtable 0x0079aa34 slot 2).
// Layout and behaviour: shared/vector_class.hpp.
#define VECTOR_IMPLEMENT_DYNAMIC_RESIZE
#include "shared/vector_class.hpp"

class MixFileClass;

template class DynamicVectorClass<MixFileClass *>;
