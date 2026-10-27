// DynamicVectorClass<LightSourceClass::PendingCellClass *>::Resize (0x00538180; DynamicVectorClass<LightSourceClass::PendingCellClass *> vtable 0x007a54f4 slot 2).
// Layout and behaviour: shared/vector_class.hpp.
#define VECTOR_IMPLEMENT_DYNAMIC_RESIZE
#include "shared/vector_class.hpp"

class LightSourceClass {
public:
    class PendingCellClass;
};

template class DynamicVectorClass<LightSourceClass::PendingCellClass *>;
