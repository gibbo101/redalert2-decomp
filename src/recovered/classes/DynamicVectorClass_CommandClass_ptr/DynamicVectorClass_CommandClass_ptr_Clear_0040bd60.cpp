// DynamicVectorClass<CommandClass *>::Clear (0x0040BD60; DynamicVectorClass<CommandClass *> vtable 0x0079a81c slot 3).
// Layout and behaviour: shared/vector_class.hpp.
#define VECTOR_IMPLEMENT_DYNAMIC_CLEAR
#include "shared/vector_class.hpp"

class CommandClass;

template class DynamicVectorClass<CommandClass *>;
