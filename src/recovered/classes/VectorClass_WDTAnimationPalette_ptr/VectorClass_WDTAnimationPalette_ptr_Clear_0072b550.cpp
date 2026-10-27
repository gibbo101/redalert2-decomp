// VectorClass<WorldDominationTour::Map::AnimationPalette *>::Clear (0x0072B550; VectorClass<WorldDominationTour::Map::AnimationPalette *> vtable 0x007af25c slot 3).
// Layout and behaviour: shared/vector_class.hpp.
#define VECTOR_IMPLEMENT_VECTOR_CLEAR
#include "shared/vector_class.hpp"

class WorldDominationTour {
public:
    class Map {
    public:
        class AnimationPalette;
    };
};

template class VectorClass<WorldDominationTour::Map::AnimationPalette *>;
