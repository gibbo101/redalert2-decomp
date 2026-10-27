// VectorClass<LightSourceClass::PendingCellClass *>::ID_pointer (0x00538160; VectorClass<LightSourceClass::PendingCellClass *> vtable 0x007a5514 slot 5).
// Layout and behaviour: shared/vector_class.hpp.
#define VECTOR_IMPLEMENT_VECTOR_ID_POINTER
#include "shared/vector_class.hpp"

class LightSourceClass {
public:
    class PendingCellClass;
};

template class VectorClass<LightSourceClass::PendingCellClass *>;
