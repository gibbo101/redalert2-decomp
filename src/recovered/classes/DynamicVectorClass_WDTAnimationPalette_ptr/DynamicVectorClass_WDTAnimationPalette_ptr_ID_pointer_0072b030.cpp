// DynamicVectorClass<WorldDominationTour::Map::AnimationPalette *>::ID_pointer (0x0072B030; DynamicVectorClass<WorldDominationTour::Map::AnimationPalette *> vtable 0x007af1fc slot 5).
// Layout and behaviour: shared/vector_class.hpp.
#define VECTOR_IMPLEMENT_DYNAMIC_ID_POINTER
#include "shared/vector_class.hpp"

class WorldDominationTour {
public:
    class Map {
    public:
        class AnimationPalette;
    };
};

template class DynamicVectorClass<WorldDominationTour::Map::AnimationPalette *>;
