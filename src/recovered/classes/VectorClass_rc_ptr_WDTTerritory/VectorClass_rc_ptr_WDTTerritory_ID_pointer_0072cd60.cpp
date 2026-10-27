// VectorClass<rc_ptr<WDTTerritory>>::ID_pointer (0x0072CD60; VectorClass<rc_ptr<WDTTerritory>> vtable 0x007af2e8 slot 5).
// Layout and behaviour: shared/vector_class.hpp.
// rc_ptr<WDTTerritory> is a size-only stand-in (8 bytes, from the ID(T const *) divisor);
// its real fields are not recovered.
#define VECTOR_IMPLEMENT_VECTOR_ID_POINTER
#include "shared/vector_class.hpp"

class WDTTerritory;

template <class A0>
struct rc_ptr {
    int unknown[2];
};

template class VectorClass<rc_ptr<WDTTerritory> >;
