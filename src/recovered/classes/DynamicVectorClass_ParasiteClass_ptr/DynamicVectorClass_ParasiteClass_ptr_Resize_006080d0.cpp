// DynamicVectorClass<ParasiteClass *>::Resize (0x006080D0; DynamicVectorClass<ParasiteClass *> vtable 0x007a7c2c slot 2).
// Layout and behaviour: shared/vector_class.hpp.
#define VECTOR_IMPLEMENT_DYNAMIC_RESIZE
#include "shared/vector_class.hpp"

class ParasiteClass;

template class DynamicVectorClass<ParasiteClass *>;
