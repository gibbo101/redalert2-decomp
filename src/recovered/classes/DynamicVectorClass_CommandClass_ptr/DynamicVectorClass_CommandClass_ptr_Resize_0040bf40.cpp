// DynamicVectorClass<CommandClass *>::Resize (0x0040BF40; DynamicVectorClass<CommandClass *> vtable 0x0079a81c slot 2).
// Layout and behaviour: shared/vector_class.hpp.
#define VECTOR_IMPLEMENT_DYNAMIC_RESIZE
#include "shared/vector_class.hpp"

class CommandClass;

template class DynamicVectorClass<CommandClass *>;
