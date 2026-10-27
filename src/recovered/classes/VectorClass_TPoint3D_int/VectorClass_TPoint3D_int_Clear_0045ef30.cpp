// VectorClass<TPoint3D<int>>::Clear (0x0045EF30; VectorClass<TPoint3D<int>> vtable 0x0079d2c0 slot 3).
// Layout and behaviour: shared/vector_class.hpp.
// The element type is left incomplete: Clear does not depend on it.
#define VECTOR_IMPLEMENT_VECTOR_CLEAR
#include "shared/vector_class.hpp"

template <class A0>
struct TPoint3D;

template class VectorClass<TPoint3D<int> >;
