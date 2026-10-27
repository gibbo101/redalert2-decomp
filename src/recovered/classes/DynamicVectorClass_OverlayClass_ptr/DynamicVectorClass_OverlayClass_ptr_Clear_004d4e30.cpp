// DynamicVectorClass<OverlayClass *>::Clear (0x004D4E30; DynamicVectorClass<OverlayClass *> vtable 0x007a2264 slot 3).
// Layout and behaviour: shared/vector_class.hpp.
#define VECTOR_IMPLEMENT_DYNAMIC_CLEAR
#include "shared/vector_class.hpp"

class OverlayClass;

template class DynamicVectorClass<OverlayClass *>;
