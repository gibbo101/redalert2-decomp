// DynamicVectorClass<OverlayClass *>::Resize (0x004D7890; DynamicVectorClass<OverlayClass *> vtable 0x007a2264 slot 2).
// Layout and behaviour: shared/vector_class.hpp.
#define VECTOR_IMPLEMENT_DYNAMIC_RESIZE
#include "shared/vector_class.hpp"

class OverlayClass;

template class DynamicVectorClass<OverlayClass *>;
