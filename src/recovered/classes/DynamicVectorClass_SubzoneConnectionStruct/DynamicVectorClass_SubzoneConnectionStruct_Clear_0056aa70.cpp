// DynamicVectorClass<SubzoneConnectionStruct>::Clear (0x0056AA70; DynamicVectorClass<SubzoneConnectionStruct> vtable 0x007a5ad8 slot 3).
// Layout and behaviour: shared/vector_class.hpp.
// The element type is left incomplete: Clear does not depend on it.
#define VECTOR_IMPLEMENT_DYNAMIC_CLEAR
#include "shared/vector_class.hpp"

struct SubzoneConnectionStruct;

template class DynamicVectorClass<SubzoneConnectionStruct>;
