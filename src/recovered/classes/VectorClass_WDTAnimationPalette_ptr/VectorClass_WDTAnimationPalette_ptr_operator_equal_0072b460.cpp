// VectorClass<WorldDominationTour::Map::AnimationPalette *>::operator equal (0x0072B460; VectorClass<WorldDominationTour::Map::AnimationPalette *> vtable 0x007af25c slot 1).
// Layout and behaviour: shared/vector_class.hpp.
#define VECTOR_IMPLEMENT_VECTOR_EQUAL
#include "shared/vector_class.hpp"

class WorldDominationTour {
public:
    class Map {
    public:
        class AnimationPalette;
    };
};

template class VectorClass<WorldDominationTour::Map::AnimationPalette *>;
