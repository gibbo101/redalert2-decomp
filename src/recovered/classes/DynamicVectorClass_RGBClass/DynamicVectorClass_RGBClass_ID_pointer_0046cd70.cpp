// DynamicVectorClass<RGBClass>::ID_pointer (0x0046CD70; TypeList<RGBClass> vtable 0x0079da74 slot 5).
// Layout and behaviour: shared/vector_class.hpp.
// RGBClass is a size-only stand-in (3 bytes, from the ID(T const *) divisor);
// its real fields are not recovered.
#define VECTOR_IMPLEMENT_DYNAMIC_ID_POINTER
#include "shared/vector_class.hpp"

struct RGBClass {
    unsigned char unknown[3];
};

template class DynamicVectorClass<RGBClass>;
