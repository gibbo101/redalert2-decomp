// DynamicVectorClass<VocClass *>::Clear (0x00714D30; DynamicVectorClass<VocClass *> vtable 0x007ae98c slot 3).
// Layout and behaviour: shared/vector_class.hpp.
#define VECTOR_IMPLEMENT_DYNAMIC_CLEAR
#include "shared/vector_class.hpp"

class VocClass;

template class DynamicVectorClass<VocClass *>;
