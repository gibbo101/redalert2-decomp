// VectorClass<HouseClass::BuildChoiceClass *>::Clear (0x004F7A70; VectorClass<HouseClass::BuildChoiceClass *> vtable 0x007a2d14 slot 3).
// Layout and behaviour: shared/vector_class.hpp.
#define VECTOR_IMPLEMENT_VECTOR_CLEAR
#include "shared/vector_class.hpp"

class HouseClass {
public:
    class BuildChoiceClass;
};

template class VectorClass<HouseClass::BuildChoiceClass *>;
