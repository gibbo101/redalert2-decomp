// VectorClass<LightSourceClass::PendingCellClass *>::Clear (0x005380F0; VectorClass<LightSourceClass::PendingCellClass *> vtable 0x007a5514 slot 3).
// Layout and behaviour: shared/vector_class.hpp.
#define VECTOR_IMPLEMENT_VECTOR_CLEAR
#include "shared/vector_class.hpp"

class LightSourceClass {
public:
    class PendingCellClass;
};

template class VectorClass<LightSourceClass::PendingCellClass *>;
