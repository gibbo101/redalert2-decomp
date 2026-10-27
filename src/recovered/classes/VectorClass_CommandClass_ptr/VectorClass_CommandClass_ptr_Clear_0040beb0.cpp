// VectorClass<CommandClass *>::Clear (0x0040BEB0; VectorClass<CommandClass *> vtable 0x0079a83c slot 3).
// Layout and behaviour: shared/vector_class.hpp.
#define VECTOR_IMPLEMENT_VECTOR_CLEAR
#include "shared/vector_class.hpp"

class CommandClass;

template class VectorClass<CommandClass *>;
