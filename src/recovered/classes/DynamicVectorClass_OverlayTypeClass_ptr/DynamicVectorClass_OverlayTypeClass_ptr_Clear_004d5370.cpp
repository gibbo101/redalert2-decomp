// DynamicVectorClass<OverlayTypeClass *>::Clear (0x004D5370; DynamicVectorClass<OverlayTypeClass *> vtable 0x007a26a4 slot 3).
// Layout and behaviour: shared/vector_class.hpp.
#define VECTOR_IMPLEMENT_DYNAMIC_CLEAR
#include "shared/vector_class.hpp"

class OverlayTypeClass;

template class DynamicVectorClass<OverlayTypeClass *>;
