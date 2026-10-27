// VectorClass<LightSourceClass::PendingCellClass *>::Resize (0x00538040; VectorClass<LightSourceClass::PendingCellClass *> vtable 0x007a5514 slot 2).
// Layout and behaviour: shared/vector_class.hpp.
#define VECTOR_IMPLEMENT_VECTOR_RESIZE
#include "shared/vector_class.hpp"

class LightSourceClass {
public:
    class PendingCellClass;
};

template class VectorClass<LightSourceClass::PendingCellClass *>;
