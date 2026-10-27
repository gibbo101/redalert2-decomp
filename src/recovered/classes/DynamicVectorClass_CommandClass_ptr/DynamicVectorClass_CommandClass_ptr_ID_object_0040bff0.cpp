// DynamicVectorClass<CommandClass *>::ID_object (0x0040BFF0; DynamicVectorClass<CommandClass *> vtable 0x0079a81c slot 4).
// Layout and behaviour: shared/vector_class.hpp.
#define VECTOR_IMPLEMENT_DYNAMIC_ID_OBJECT
#include "shared/vector_class.hpp"

class CommandClass;

template class DynamicVectorClass<CommandClass *>;
