// VectorClass<CommandClass *>::ID_pointer (0x0040BF20; VectorClass<CommandClass *> vtable 0x0079a83c slot 5).
// Layout and behaviour: shared/vector_class.hpp.
#define VECTOR_IMPLEMENT_VECTOR_ID_POINTER
#include "shared/vector_class.hpp"

class CommandClass;

template class VectorClass<CommandClass *>;
