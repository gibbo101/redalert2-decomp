// VectorClass<CommandClass *>::operator equal (0x0040BDC0; VectorClass<CommandClass *> vtable 0x0079a83c slot 1).
// Layout and behaviour: shared/vector_class.hpp.
#define VECTOR_IMPLEMENT_VECTOR_EQUAL
#include "shared/vector_class.hpp"

class CommandClass;

template class VectorClass<CommandClass *>;
