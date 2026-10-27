// DynamicVectorClass<WaveClass *>::Clear (0x004D4DD0; DynamicVectorClass<WaveClass *> vtable 0x007a2224 slot 3).
// Layout and behaviour: shared/vector_class.hpp.
#define VECTOR_IMPLEMENT_DYNAMIC_CLEAR
#include "shared/vector_class.hpp"

class WaveClass;

template class DynamicVectorClass<WaveClass *>;
