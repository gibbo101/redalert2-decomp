// VectorClass<BuildingTypeClass *>::operator=(VectorClass<BuildingTypeClass *> const &) -- 0x006530E0
// Replaces the contents with an owned copy (shared/vector_class.hpp); the
// copy kept out of line in the Rules unit. Element type from the callers:
// the source lists are TypeList<BuildingTypeClass *> copies (0x0058EED0, e.g. at 0x00643C6E).
#define VECTOR_IMPLEMENT_VECTOR_ASSIGN
#include "shared/vector_class.hpp"

class BuildingTypeClass;

template class VectorClass<BuildingTypeClass *>;
