// DynamicVectorClass<FoggedObjectClass *>::Clear (0x00453D80; DynamicVectorClass<FoggedObjectClass *> vtable 0x0079d17c slot 3).
// Layout and behaviour: shared/vector_class.hpp.
#define VECTOR_IMPLEMENT_DYNAMIC_CLEAR
#include "shared/vector_class.hpp"

class FoggedObjectClass;

template class DynamicVectorClass<FoggedObjectClass *>;
