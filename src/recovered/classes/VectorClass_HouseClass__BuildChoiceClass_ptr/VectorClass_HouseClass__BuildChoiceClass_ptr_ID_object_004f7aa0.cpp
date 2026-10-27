// VectorClass<HouseClass::BuildChoiceClass *>::ID_object (0x004F7AA0; VectorClass<HouseClass::BuildChoiceClass *> vtable 0x007a2d14 slot 4).
// Layout and behaviour: shared/vector_class.hpp.
#define VECTOR_IMPLEMENT_VECTOR_ID_OBJECT
#include "shared/vector_class.hpp"

class HouseClass {
public:
    class BuildChoiceClass;
};

template class VectorClass<HouseClass::BuildChoiceClass *>;
