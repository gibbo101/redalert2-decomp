// VectorClass<SmudgeTypeClass *>::operator=(VectorClass<SmudgeTypeClass *> const &) -- 0x00653540
// Replaces the contents with an owned copy (shared/vector_class.hpp); the
// copy kept out of line in the Rules unit. Element type from the callers:
// the source lists are TypeList<SmudgeTypeClass *> copies (0x00654600, e.g. at 0x00646DEA).
#define VECTOR_IMPLEMENT_VECTOR_ASSIGN
#include "shared/vector_class.hpp"

class SmudgeTypeClass;

template class VectorClass<SmudgeTypeClass *>;
