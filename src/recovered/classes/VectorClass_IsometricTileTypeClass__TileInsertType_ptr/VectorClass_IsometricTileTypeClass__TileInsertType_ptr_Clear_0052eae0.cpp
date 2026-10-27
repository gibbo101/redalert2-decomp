// VectorClass<IsometricTileTypeClass::TileInsertType *>::Clear (0x0052EAE0; VectorClass<IsometricTileTypeClass::TileInsertType *> vtable 0x007a515c slot 3).
// Layout and behaviour: shared/vector_class.hpp.
#define VECTOR_IMPLEMENT_VECTOR_CLEAR
#include "shared/vector_class.hpp"

class IsometricTileTypeClass {
public:
    class TileInsertType;
};

template class VectorClass<IsometricTileTypeClass::TileInsertType *>;
