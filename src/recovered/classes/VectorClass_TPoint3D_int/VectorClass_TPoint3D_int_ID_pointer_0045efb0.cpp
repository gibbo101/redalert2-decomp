// VectorClass<TPoint3D<int>>::ID_pointer (0x0045EFB0; VectorClass<TPoint3D<int>> vtable 0x0079d2c0 slot 5).
// Layout and behaviour: shared/vector_class.hpp.
// TPoint3D<int> is a size-only stand-in (12 bytes, from the ID(T const *) divisor);
// its real fields are not recovered.
#define VECTOR_IMPLEMENT_VECTOR_ID_POINTER
#include "shared/vector_class.hpp"

template <class A0>
struct TPoint3D {
    int unknown[3];
};

template class VectorClass<TPoint3D<int> >;
