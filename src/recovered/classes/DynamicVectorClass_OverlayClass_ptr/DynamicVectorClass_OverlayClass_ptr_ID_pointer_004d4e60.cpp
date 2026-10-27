// DynamicVectorClass<OverlayClass *>::ID_pointer (0x004D4E60; DynamicVectorClass<OverlayClass *> vtable 0x007a2264 slot 5).
// Layout and behaviour: shared/vector_class.hpp.
#define VECTOR_IMPLEMENT_DYNAMIC_ID_POINTER
#include "shared/vector_class.hpp"

class OverlayClass;

template class DynamicVectorClass<OverlayClass *>;
