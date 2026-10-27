// DynamicVectorClass<IsometricTileTypeClass::TileInsertType *>::Clear (0x0052E730; DynamicVectorClass<IsometricTileTypeClass::TileInsertType *> vtable 0x007a513c slot 3).
// Layout and behaviour: shared/vector_class.hpp.
#define VECTOR_IMPLEMENT_DYNAMIC_CLEAR
#include "shared/vector_class.hpp"

class IsometricTileTypeClass {
public:
    class TileInsertType;
};

template class DynamicVectorClass<IsometricTileTypeClass::TileInsertType *>;
