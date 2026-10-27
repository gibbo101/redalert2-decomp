// VectorClass<WorldDominationTour::Centroid>::ID_pointer (0x0072B8A0; VectorClass<WorldDominationTour::Centroid> vtable 0x007af298 slot 5).
// Layout and behaviour: shared/vector_class.hpp.
// WorldDominationTour::Centroid is a size-only stand-in (12 bytes, from the ID(T const *) divisor);
// its real fields are not recovered.
#define VECTOR_IMPLEMENT_VECTOR_ID_POINTER
#include "shared/vector_class.hpp"

class WorldDominationTour {
public:
    struct Centroid {
        int unknown[3];
    };
};

template class VectorClass<WorldDominationTour::Centroid>;
