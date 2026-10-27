// DynamicVectorClass<IsometricTileTypeClass::TileInsertType *>::ID_pointer (0x0052E760; DynamicVectorClass<IsometricTileTypeClass::TileInsertType *> vtable 0x007a513c slot 5).
// Layout and behaviour: shared/vector_class.hpp.
#define VECTOR_IMPLEMENT_DYNAMIC_ID_POINTER
#include "shared/vector_class.hpp"

class IsometricTileTypeClass {
public:
    class TileInsertType;
};

template class DynamicVectorClass<IsometricTileTypeClass::TileInsertType *>;
