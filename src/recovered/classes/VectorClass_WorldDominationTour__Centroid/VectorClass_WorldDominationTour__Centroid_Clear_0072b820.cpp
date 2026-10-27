// VectorClass<WorldDominationTour::Centroid>::Clear (0x0072B820; VectorClass<WorldDominationTour::Centroid> vtable 0x007af298 slot 3).
// Layout and behaviour: shared/vector_class.hpp.
// The element type is left incomplete: Clear does not depend on it.
#define VECTOR_IMPLEMENT_VECTOR_CLEAR
#include "shared/vector_class.hpp"

class WorldDominationTour {
public:
    struct Centroid;
};

template class VectorClass<WorldDominationTour::Centroid>;
