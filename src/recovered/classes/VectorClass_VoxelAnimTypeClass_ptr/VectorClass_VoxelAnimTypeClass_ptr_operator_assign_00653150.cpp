// VectorClass<VoxelAnimTypeClass *>::operator=(VectorClass<VoxelAnimTypeClass *> const &) -- 0x00653150
// Replaces the contents with an owned copy (shared/vector_class.hpp); the
// copy kept out of line in the Rules unit. Element type from the callers:
// the source lists are TypeList<VoxelAnimTypeClass *> copies (0x00654570, e.g. at 0x00644024).
#define VECTOR_IMPLEMENT_VECTOR_ASSIGN
#include "shared/vector_class.hpp"

class VoxelAnimTypeClass;

template class VectorClass<VoxelAnimTypeClass *>;
