// VectorClass<WorldDominationTour::Map::AnimationPalette *>::ID_pointer (0x0072B5C0; VectorClass<WorldDominationTour::Map::AnimationPalette *> vtable 0x007af25c slot 5).
// Layout and behaviour: shared/vector_class.hpp.
#define VECTOR_IMPLEMENT_VECTOR_ID_POINTER
#include "shared/vector_class.hpp"

class WorldDominationTour {
public:
    class Map {
    public:
        class AnimationPalette;
    };
};

template class VectorClass<WorldDominationTour::Map::AnimationPalette *>;
