// DynamicVectorClass<WorldDominationTour::Map::AnimationPalette *>::Clear (0x0072B000; DynamicVectorClass<WorldDominationTour::Map::AnimationPalette *> vtable 0x007af1fc slot 3).
// Layout and behaviour: shared/vector_class.hpp.
#define VECTOR_IMPLEMENT_DYNAMIC_CLEAR
#include "shared/vector_class.hpp"

class WorldDominationTour {
public:
    class Map {
    public:
        class AnimationPalette;
    };
};

template class DynamicVectorClass<WorldDominationTour::Map::AnimationPalette *>;
