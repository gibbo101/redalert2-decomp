// VectorClass<CommandClass *>::ID_object (0x0040BEE0; VectorClass<CommandClass *> vtable 0x0079a83c slot 4).
// Layout and behaviour: shared/vector_class.hpp.
#define VECTOR_IMPLEMENT_VECTOR_ID_OBJECT
#include "shared/vector_class.hpp"

class CommandClass;

template class VectorClass<CommandClass *>;
