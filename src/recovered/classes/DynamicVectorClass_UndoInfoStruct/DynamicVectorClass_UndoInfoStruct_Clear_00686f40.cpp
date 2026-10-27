// DynamicVectorClass<UndoInfoStruct>::Clear (0x00686F40; DynamicVectorClass<UndoInfoStruct> vtable 0x007ab50c slot 3).
// Layout and behaviour: shared/vector_class.hpp.
// The element type is left incomplete: Clear does not depend on it.
#define VECTOR_IMPLEMENT_DYNAMIC_CLEAR
#include "shared/vector_class.hpp"

struct UndoInfoStruct;

template class DynamicVectorClass<UndoInfoStruct>;
