// DynamicVectorClass<IsometricTileTypeClass::TileInsertType *>::ID_object (0x0052EC20; DynamicVectorClass<IsometricTileTypeClass::TileInsertType *> vtable 0x007a513c slot 4).
// Layout and behaviour: shared/vector_class.hpp.
#define VECTOR_IMPLEMENT_DYNAMIC_ID_OBJECT
#include "shared/vector_class.hpp"

class IsometricTileTypeClass {
public:
    class TileInsertType;
};

template class DynamicVectorClass<IsometricTileTypeClass::TileInsertType *>;
