// VectorClass<IsometricTileTypeClass::TileInsertType *>::Fetch (0x0052E780; VectorClass<IsometricTileTypeClass::TileInsertType *> vtable 0x007a515c slot 6).
// Layout and behaviour: shared/vector_class.hpp.
#define VECTOR_IMPLEMENT_VECTOR_FETCH
#include "shared/vector_class.hpp"

class IsometricTileTypeClass {
public:
    class TileInsertType;
};

template class VectorClass<IsometricTileTypeClass::TileInsertType *>;
