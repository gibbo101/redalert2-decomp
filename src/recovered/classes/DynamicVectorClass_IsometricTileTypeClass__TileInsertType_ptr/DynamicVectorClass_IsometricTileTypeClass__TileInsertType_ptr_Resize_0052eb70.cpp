// DynamicVectorClass<IsometricTileTypeClass::TileInsertType *>::Resize (0x0052EB70; DynamicVectorClass<IsometricTileTypeClass::TileInsertType *> vtable 0x007a513c slot 2).
// Layout and behaviour: shared/vector_class.hpp.
#define VECTOR_IMPLEMENT_DYNAMIC_RESIZE
#include "shared/vector_class.hpp"

class IsometricTileTypeClass {
public:
    class TileInsertType;
};

template class DynamicVectorClass<IsometricTileTypeClass::TileInsertType *>;
