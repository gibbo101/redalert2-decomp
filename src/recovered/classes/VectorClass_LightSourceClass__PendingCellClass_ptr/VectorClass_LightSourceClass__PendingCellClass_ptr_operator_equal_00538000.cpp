// VectorClass<LightSourceClass::PendingCellClass *>::operator equal (0x00538000; VectorClass<LightSourceClass::PendingCellClass *> vtable 0x007a5514 slot 1).
// Layout and behaviour: shared/vector_class.hpp.
#define VECTOR_IMPLEMENT_VECTOR_EQUAL
#include "shared/vector_class.hpp"

class LightSourceClass {
public:
    class PendingCellClass;
};

template class VectorClass<LightSourceClass::PendingCellClass *>;
