// DynamicVectorClass<WaypointClass>::ID_pointer (0x00725310; DynamicVectorClass<WaypointClass> vtable 0x007aef8c slot 5).
// Layout and behaviour: shared/vector_class.hpp.
// WaypointClass is a size-only stand-in (12 bytes, from the ID(T const *) divisor);
// its real fields are not recovered.
#define VECTOR_IMPLEMENT_DYNAMIC_ID_POINTER
#include "shared/vector_class.hpp"

struct WaypointClass {
    int unknown[3];
};

template class DynamicVectorClass<WaypointClass>;
