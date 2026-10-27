// VectorClass<RGBClass>::ID_pointer (0x0046D900; VectorClass<RGBClass> vtable 0x0079da54 slot 5).
// Layout and behaviour: shared/vector_class.hpp.
// RGBClass is a size-only stand-in (3 bytes, from the ID(T const *) divisor);
// its real fields are not recovered.
#define VECTOR_IMPLEMENT_VECTOR_ID_POINTER
#include "shared/vector_class.hpp"

struct RGBClass {
    unsigned char unknown[3];
};

template class VectorClass<RGBClass>;
