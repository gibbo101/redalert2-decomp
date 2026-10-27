// DynamicVectorClass<CommandClass *>::ID_pointer (0x0040BD90; DynamicVectorClass<CommandClass *> vtable 0x0079a81c slot 5).
// Layout and behaviour: shared/vector_class.hpp.
#define VECTOR_IMPLEMENT_DYNAMIC_ID_POINTER
#include "shared/vector_class.hpp"

class CommandClass;

template class DynamicVectorClass<CommandClass *>;
