// VectorClass<TerrainTypeClass *>::operator=(VectorClass<TerrainTypeClass *> const &) -- 0x00654320
// Replaces the contents with an owned copy (shared/vector_class.hpp); the
// copy kept out of line in the Rules unit. Element type from the callers:
// its one caller, the TypeList<TerrainTypeClass *> copy constructor expanded in 0x00654150, calls it on an object whose vptr was just set to VectorClass<TerrainTypeClass *> (0x007A9158).
#define VECTOR_IMPLEMENT_VECTOR_ASSIGN
#include "shared/vector_class.hpp"

class TerrainTypeClass;

template class VectorClass<TerrainTypeClass *>;
