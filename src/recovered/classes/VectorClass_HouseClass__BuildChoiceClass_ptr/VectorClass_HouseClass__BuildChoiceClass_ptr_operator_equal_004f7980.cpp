// VectorClass<HouseClass::BuildChoiceClass *>::operator equal (0x004F7980; VectorClass<HouseClass::BuildChoiceClass *> vtable 0x007a2d14 slot 1).
// Layout and behaviour: shared/vector_class.hpp.
#define VECTOR_IMPLEMENT_VECTOR_EQUAL
#include "shared/vector_class.hpp"

class HouseClass {
public:
    class BuildChoiceClass;
};

template class VectorClass<HouseClass::BuildChoiceClass *>;
