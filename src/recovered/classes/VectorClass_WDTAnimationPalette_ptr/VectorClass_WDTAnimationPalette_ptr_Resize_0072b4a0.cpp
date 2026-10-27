// VectorClass<WorldDominationTour::Map::AnimationPalette *>::Resize (0x0072B4A0; VectorClass<WorldDominationTour::Map::AnimationPalette *> vtable 0x007af25c slot 2).
// Layout and behaviour: shared/vector_class.hpp.
#define VECTOR_IMPLEMENT_VECTOR_RESIZE
#include "shared/vector_class.hpp"

class WorldDominationTour {
public:
    class Map {
    public:
        class AnimationPalette;
    };
};

template class VectorClass<WorldDominationTour::Map::AnimationPalette *>;
