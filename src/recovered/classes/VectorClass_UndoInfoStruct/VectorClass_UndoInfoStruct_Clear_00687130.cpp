// VectorClass<UndoInfoStruct>::Clear (0x00687130; VectorClass<UndoInfoStruct> vtable 0x007ab52c slot 3).
// Layout and behaviour: shared/vector_class.hpp.
// The element type is left incomplete: Clear does not depend on it.
#define VECTOR_IMPLEMENT_VECTOR_CLEAR
#include "shared/vector_class.hpp"

struct UndoInfoStruct;

template class VectorClass<UndoInfoStruct>;
