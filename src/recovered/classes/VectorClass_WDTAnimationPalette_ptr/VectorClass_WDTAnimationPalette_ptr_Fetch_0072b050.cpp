// VectorClass<WorldDominationTour::Map::AnimationPalette *>::Fetch (0x0072B050; VectorClass<WorldDominationTour::Map::AnimationPalette *> vtable 0x007af25c slot 6).
// Layout and behaviour: shared/vector_class.hpp.
#define VECTOR_IMPLEMENT_VECTOR_FETCH
#include "shared/vector_class.hpp"

class WorldDominationTour {
public:
    class Map {
    public:
        class AnimationPalette;
    };
};

template class VectorClass<WorldDominationTour::Map::AnimationPalette *>;
