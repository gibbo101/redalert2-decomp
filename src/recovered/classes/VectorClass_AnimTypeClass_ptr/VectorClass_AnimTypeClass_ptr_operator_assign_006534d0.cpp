// VectorClass<AnimTypeClass *>::operator=(VectorClass<AnimTypeClass *> const &) -- 0x006534D0
// Replaces the contents with an owned copy (shared/vector_class.hpp); the
// copy kept out of line in the Rules unit. Element type from the callers:
// the source lists are TypeList<AnimTypeClass *> copies (0x0050B7D0, e.g. at 0x006442FF).
#define VECTOR_IMPLEMENT_VECTOR_ASSIGN
#include "shared/vector_class.hpp"

class AnimTypeClass;

template class VectorClass<AnimTypeClass *>;
