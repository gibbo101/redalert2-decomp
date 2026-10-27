// DynamicVectorClass<MixFileClass *>::Clear (0x0040D410; DynamicVectorClass<MixFileClass *> vtable 0x0079aa34 slot 3).
// Layout and behaviour: shared/vector_class.hpp.
#define VECTOR_IMPLEMENT_DYNAMIC_CLEAR
#include "shared/vector_class.hpp"

class MixFileClass;

template class DynamicVectorClass<MixFileClass *>;
