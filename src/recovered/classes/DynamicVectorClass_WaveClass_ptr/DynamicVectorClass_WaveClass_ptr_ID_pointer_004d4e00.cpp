// DynamicVectorClass<WaveClass *>::ID_pointer (0x004D4E00; DynamicVectorClass<WaveClass *> vtable 0x007a2224 slot 5).
// Layout and behaviour: shared/vector_class.hpp.
#define VECTOR_IMPLEMENT_DYNAMIC_ID_POINTER
#include "shared/vector_class.hpp"

class WaveClass;

template class DynamicVectorClass<WaveClass *>;
