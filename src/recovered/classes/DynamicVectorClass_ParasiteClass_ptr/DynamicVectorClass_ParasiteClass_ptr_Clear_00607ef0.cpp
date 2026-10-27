// DynamicVectorClass<ParasiteClass *>::Clear (0x00607EF0; DynamicVectorClass<ParasiteClass *> vtable 0x007a7c2c slot 3).
// Layout and behaviour: shared/vector_class.hpp.
#define VECTOR_IMPLEMENT_DYNAMIC_CLEAR
#include "shared/vector_class.hpp"

class ParasiteClass;

template class DynamicVectorClass<ParasiteClass *>;
