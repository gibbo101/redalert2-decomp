// DynamicVectorClass<WarheadTypeClass *>::Resize (0x0040F5A0; DynamicVectorClass<WarheadTypeClass *> vtable 0x0079ad0c slot 2).
// Layout and behaviour: shared/vector_class.hpp.
#define VECTOR_IMPLEMENT_DYNAMIC_RESIZE
#include "shared/vector_class.hpp"

class WarheadTypeClass;

template class DynamicVectorClass<WarheadTypeClass *>;
