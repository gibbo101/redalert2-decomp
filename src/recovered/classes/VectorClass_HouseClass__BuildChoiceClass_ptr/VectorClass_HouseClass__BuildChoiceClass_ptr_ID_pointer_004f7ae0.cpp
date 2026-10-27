// VectorClass<HouseClass::BuildChoiceClass *>::ID_pointer (0x004F7AE0; VectorClass<HouseClass::BuildChoiceClass *> vtable 0x007a2d14 slot 5).
// Layout and behaviour: shared/vector_class.hpp.
#define VECTOR_IMPLEMENT_VECTOR_ID_POINTER
#include "shared/vector_class.hpp"

class HouseClass {
public:
    class BuildChoiceClass;
};

template class VectorClass<HouseClass::BuildChoiceClass *>;
