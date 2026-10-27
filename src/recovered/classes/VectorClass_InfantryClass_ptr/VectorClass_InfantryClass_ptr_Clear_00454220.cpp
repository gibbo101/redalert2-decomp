// VectorClass<InfantryClass *>::Clear (0x00454220; VectorClass<InfantryClass *> vtable 0x0079d074 slot 3).
// Layout and behaviour: shared/vector_class.hpp.
#define VECTOR_IMPLEMENT_VECTOR_CLEAR
#include "shared/vector_class.hpp"

class InfantryClass;

template class VectorClass<InfantryClass *>;
