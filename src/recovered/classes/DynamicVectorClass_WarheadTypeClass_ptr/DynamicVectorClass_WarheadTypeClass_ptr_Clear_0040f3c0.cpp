// DynamicVectorClass<WarheadTypeClass *>::Clear (0x0040F3C0; DynamicVectorClass<WarheadTypeClass *> vtable 0x0079ad0c slot 3).
// Layout and behaviour: shared/vector_class.hpp.
#define VECTOR_IMPLEMENT_DYNAMIC_CLEAR
#include "shared/vector_class.hpp"

class WarheadTypeClass;

template class DynamicVectorClass<WarheadTypeClass *>;
