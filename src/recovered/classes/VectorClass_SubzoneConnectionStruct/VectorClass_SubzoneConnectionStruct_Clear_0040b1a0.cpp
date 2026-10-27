// VectorClass<SubzoneConnectionStruct>::Clear (0x0040B1A0; VectorClass<SubzoneConnectionStruct> vtable 0x0079a76c slot 3).
// Layout and behaviour: shared/vector_class.hpp.
// The element type is left incomplete: Clear does not depend on it.
#define VECTOR_IMPLEMENT_VECTOR_CLEAR
#include "shared/vector_class.hpp"

struct SubzoneConnectionStruct;

template class VectorClass<SubzoneConnectionStruct>;
