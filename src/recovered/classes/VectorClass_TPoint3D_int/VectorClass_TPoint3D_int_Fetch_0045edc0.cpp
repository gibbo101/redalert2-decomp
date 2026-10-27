// VectorClass<TPoint3D<int>>::Fetch (0x0045EDC0; VectorClass<TPoint3D<int>> vtable 0x0079d2c0 slot 6).
// Layout and behaviour: shared/vector_class.hpp.
// TPoint3D<int> is a size-only stand-in (12 bytes, from the ID(T const *) divisor);
// its real fields are not recovered.
#define VECTOR_IMPLEMENT_VECTOR_FETCH
#include "shared/vector_class.hpp"

template <class A0>
struct TPoint3D {
    int unknown[3];
};

template class VectorClass<TPoint3D<int> >;
