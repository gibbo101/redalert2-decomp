// VectorClass<WorldDominationTour::Centroid>::Fetch (0x0072B060; VectorClass<WorldDominationTour::Centroid> vtable 0x007af298 slot 6).
// Layout and behaviour: shared/vector_class.hpp.
// WorldDominationTour::Centroid is a size-only stand-in (12 bytes, from the ID(T const *) divisor);
// its real fields are not recovered.
#define VECTOR_IMPLEMENT_VECTOR_FETCH
#include "shared/vector_class.hpp"

class WorldDominationTour {
public:
    struct Centroid {
        int unknown[3];
    };
};

template class VectorClass<WorldDominationTour::Centroid>;
