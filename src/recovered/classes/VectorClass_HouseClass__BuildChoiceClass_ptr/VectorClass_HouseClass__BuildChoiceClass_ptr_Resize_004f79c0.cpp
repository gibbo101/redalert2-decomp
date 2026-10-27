// VectorClass<HouseClass::BuildChoiceClass *>::Resize (0x004F79C0; VectorClass<HouseClass::BuildChoiceClass *> vtable 0x007a2d14 slot 2).
// Layout and behaviour: shared/vector_class.hpp.
#define VECTOR_IMPLEMENT_VECTOR_RESIZE
#include "shared/vector_class.hpp"

class HouseClass {
public:
    class BuildChoiceClass;
};

template class VectorClass<HouseClass::BuildChoiceClass *>;
