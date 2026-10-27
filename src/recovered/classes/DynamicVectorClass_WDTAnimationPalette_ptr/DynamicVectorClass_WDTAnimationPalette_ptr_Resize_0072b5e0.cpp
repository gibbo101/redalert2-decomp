// DynamicVectorClass<WorldDominationTour::Map::AnimationPalette *>::Resize (0x0072B5E0; DynamicVectorClass<WorldDominationTour::Map::AnimationPalette *> vtable 0x007af1fc slot 2).
// Layout and behaviour: shared/vector_class.hpp.
#define VECTOR_IMPLEMENT_DYNAMIC_RESIZE
#include "shared/vector_class.hpp"

class WorldDominationTour {
public:
    class Map {
    public:
        class AnimationPalette;
    };
};

template class DynamicVectorClass<WorldDominationTour::Map::AnimationPalette *>;
