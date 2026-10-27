// DynamicVectorClass<OverlayTypeClass *>::Resize (0x004D99D0; DynamicVectorClass<OverlayTypeClass *> vtable 0x007a26a4 slot 2).
// Layout and behaviour: shared/vector_class.hpp.
#define VECTOR_IMPLEMENT_DYNAMIC_RESIZE
#include "shared/vector_class.hpp"

class OverlayTypeClass;

template class DynamicVectorClass<OverlayTypeClass *>;
