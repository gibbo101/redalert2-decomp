// VectorClass<LightSourceClass::PendingCellClass *>::ID_object (0x00538120; VectorClass<LightSourceClass::PendingCellClass *> vtable 0x007a5514 slot 4).
// Layout and behaviour: shared/vector_class.hpp.
#define VECTOR_IMPLEMENT_VECTOR_ID_OBJECT
#include "shared/vector_class.hpp"

class LightSourceClass {
public:
    class PendingCellClass;
};

template class VectorClass<LightSourceClass::PendingCellClass *>;
